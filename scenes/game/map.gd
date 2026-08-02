extends MeshInstance3D

@onready var core_node: Core = $"../Core"
@onready var map_node: Node3D = $"../Map"

@export var cell_size: float = 0.028
@export var xoffset: float = 0.445
@export var yoffset: float = 0.445

var selected_cell: Vector2i = Vector2i(-1, -1)
var hovered_cell: Vector2i = Vector2i(-1, -1)

var reachable_cells: Array = []
var path_cells: Array = []

func test():
	var e = Enemy.new()
	var p = player.new()
	var t1 = tree.new()
	
	core_node.get_board().set_unit(3, 4, e)
	core_node.get_board().set_unit(13, 8, p)
	core_node.get_board().set_unit(5, 5, t1)
	
	core_node.start_combat()

func _ready() -> void:
	if not core_node:
		return
	await get_tree().process_frame
	
	var event_bus = core_node.get_event_bus()
	if event_bus:
		event_bus.subscribe("turn_changed", _on_turn_changed)
	test()
	draw_debug_board()
	
func _on_turn_changed(unit) -> void:
	if unit.get_type() == 0:
		# Если наступил ход игрока, находим его позицию на доске и подсвечиваем зоны хода
		selected_cell = unit.position
		reachable_cells = core_node.get_reachable_cells(selected_cell)
		draw_debug_board()
		return
	else:
		selected_cell = Vector2i(-1, -1)
		reachable_cells.clear()
		path_cells.clear()
		draw_debug_board()

func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventMouseMotion:
		var current_hover = _get_cell_from_mouse(event.position)
		if current_hover != hovered_cell:
			hovered_cell = current_hover
			_update_current_path()
			draw_debug_board()

	# 2. Обработка клика
	elif event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		var clicked_cell = _get_cell_from_mouse(event.position)
		if clicked_cell != Vector2i(-1, -1):
			_on_cell_clicked(clicked_cell)

func _update_current_path() -> void:
	# Запрашиваем путь только если юнит выбран и мышь наведена на клетку из зоны хода
	if selected_cell != Vector2i(-1, -1) and hovered_cell in reachable_cells:
		path_cells = core_node.get_path(selected_cell, hovered_cell)
	else:
		path_cells.clear()

func _on_cell_clicked(cell_coord: Vector2i) -> void:
	if cell_coord == Vector2i(0, 0):
		selected_cell = Vector2i(-1, -1)
		reachable_cells.clear()
		path_cells.clear()
		core_node.next_turn()
		draw_debug_board()
		return
		
	# Клик по клетке доступного хода -> ходим
	if selected_cell != Vector2i(-1, -1) and cell_coord in reachable_cells:
		var moved = core_node.move_unit(selected_cell, cell_coord)
		if moved:
			selected_cell = Vector2i(-1, -1)
			reachable_cells.clear()
			path_cells.clear()
			draw_debug_board()
			return

	# Выбор новой клетки
	var board = core_node.get_board()
	if board and board.get_unit(cell_coord.x, cell_coord.y) != null:
		selected_cell = cell_coord
		reachable_cells = core_node.get_reachable_cells(selected_cell)
		_update_current_path()
	else:
		selected_cell = Vector2i(-1, -1)
		reachable_cells.clear()
		path_cells.clear()

	draw_debug_board()

func draw_debug_board() -> void:
	for child in get_children():
		child.queue_free()

	var board = core_node.get_board()
	if not board: return
		
	var board_size = board.get_board_size()
	cell_size = 0.94 / board_size[0]

	for x in range(board_size[0]):
		for y in range(board_size[1]):
			var coord = Vector2i(x, y)
			var unit = board.get_unit(x, y)
			var pos = Vector3(x * cell_size - xoffset, 0, y * cell_size - yoffset)
			
			# Приоритет цвета: 
			# 1. Точка старта (Жёлтый)
			# 2. Путь траектории (Голубой)
			# 3. Зона хода (Зелёный)
			# 4. Обычная клетка (Тёмно-серый)
			var cell_color = Color.DARK_GRAY

			if coord == selected_cell:
				cell_color = Color.YELLOW
			elif coord in path_cells:
				cell_color = Color.CYAN
			elif coord in reachable_cells:
				cell_color = Color.GREEN

			_spawn_debug_box(pos - Vector3(0, 0.035, 0), Vector3(cell_size * 0.9, 0.1, cell_size * 0.9), cell_color)
			
			if unit != null:
				var unit_mesh = unit.get_model()
				var mesh_inst = MeshInstance3D.new()
				mesh_inst.mesh = unit_mesh
				mesh_inst.position = pos + Vector3(0, 0.05, 0)
				mesh_inst.scale = Vector3(1.6, 1.6, 1.6) 
				add_child(mesh_inst)

func _get_cell_from_mouse(mouse_pos: Vector2) -> Vector2i:
	var camera = get_viewport().get_camera_3d()
	if not camera or not map_node: 
		return Vector2i(-1, -1)

	var from = camera.project_ray_origin(mouse_pos)
	var dir = camera.project_ray_normal(mouse_pos)
	
	var map_plane = Plane(map_node.global_transform.basis.y, map_node.global_position)
	var hit_pos = map_plane.intersects_ray(from, dir)
	if hit_pos == null:
		return Vector2i(-1, -1)

	var local_pos = map_node.to_local(hit_pos)

	var x = int(round((local_pos.x + xoffset) / cell_size))
	var y = int(round((local_pos.z + yoffset) / cell_size))

	var board = core_node.get_board()
	if board:
		var board_size = board.get_board_size()
		if x >= 0 and x < board_size[0] and y >= 0 and y < board_size[1]:
			return Vector2i(x, y)

	return Vector2i(-1, -1)

func _spawn_debug_box(pos: Vector3, size: Vector3, color: Color) -> void:
	var mesh_inst = MeshInstance3D.new()
	var box = BoxMesh.new()
	box.size = size
	
	var mat = StandardMaterial3D.new()
	mat.albedo_color = color
	box.material = mat
	
	mesh_inst.mesh = box
	mesh_inst.position = pos
	add_child(mesh_inst)
