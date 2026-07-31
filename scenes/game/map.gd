extends MeshInstance3D

@onready var core_node: Core = $"../Core"
@onready var map_node: Node3D = $"../Map"
@export var cell_size: float = 0.028
@export var xoffset: float = 0.445
@export var yoffset: float = 0.445

var selected_cell: Vector2i = Vector2i(-1, -1)
var reachable_cells: Array = []

func _ready() -> void:
	if not core_node:
		print("DebugBoardDrawer: Узел Core не привязан!")
		return
		
	await get_tree().process_frame
	draw_debug_board()

# Обработка кликов мыши по 3D-сетке
func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		print("Click", event.position)
		var clicked_cell = _get_cell_from_mouse(event.position)
		print(clicked_cell)
		if clicked_cell != Vector2i(-1, -1):
			_on_cell_clicked(clicked_cell)

func _on_cell_clicked(cell_coord: Vector2i) -> void:
	# Если мы уже выбрали юнита и кликнули в подсвеченную зелёную клетку -> ХОДИМ
	if selected_cell != Vector2i(-1, -1) and cell_coord in reachable_cells:
		var moved = core_node.move_unit(selected_cell, cell_coord)
		print(moved, selected_cell, cell_coord)
		if moved:
			selected_cell = Vector2i(-1, -1)
			reachable_cells.clear()
			draw_debug_board()
			return

	# Иначе выделяем новую клетку
	var board = core_node.get_board()
	if board and board.get_unit(cell_coord.x, cell_coord.y) != null:
		selected_cell = cell_coord
		reachable_cells = core_node.get_reachable_cells(selected_cell)
	else:
		selected_cell = Vector2i(-1, -1)
		reachable_cells.clear()

	draw_debug_board()

func draw_debug_board() -> void:
	# Удаляем старый визуал перед перерисовкой
	for child in get_children():
		child.queue_free()

	var board = core_node.get_board()
	if not board:
		return
		
	var board_size = board.get_board_size()
	cell_size = 0.94 / board_size[0]

	for x in range(board_size[0]):
		for y in range(board_size[1]):
			var coord = Vector2i(x, y)
			var unit = board.get_unit(x, y)
			var pos = Vector3(x * cell_size - xoffset, 0, y * cell_size - yoffset)
			
			# Цвет клетки: Зелёная (доступна для хода), Жёлтая (выбран юнит), Серый (обычная)
			var cell_color = Color.DARK_GRAY
			if coord in reachable_cells:
				cell_color = Color.GREEN
			elif coord == selected_cell:
				cell_color = Color.YELLOW

			_spawn_debug_box(pos - Vector3(0, 0.035, 0), Vector3(cell_size * 0.9, 0.1, cell_size * 0.9), cell_color)
			
			if unit != null:
				_spawn_debug_box(pos, Vector3(cell_size - 0.01, 0.1, cell_size - 0.01), Color.RED)

# Простая математика перевода клика мыши на 3D плоскость доски
func _get_cell_from_mouse(mouse_pos: Vector2) -> Vector2i:
	var camera = get_viewport().get_camera_3d()
	if not camera or not map_node: 
		return Vector2i(-1, -1)

	var from = camera.project_ray_origin(mouse_pos)
	var dir = camera.project_ray_normal(mouse_pos)
	
	# Создаём плоскость карты: нормаль = локальная ось Y узла Map, точка = позиция Map
	var map_plane = Plane(map_node.global_transform.basis.y, map_node.global_position)
	
	# Находим точку пересечения луча камеры с плоскостью карты (возвращает Vector3 или null)
	var hit_pos = map_plane.intersects_ray(from, dir)
	if hit_pos == null:
		return Vector2i(-1, -1)

	# Переводим мировую точку пересечения в ЛОКАЛЬНЫЕ координаты узла Map
	var local_pos = map_node.to_local(hit_pos)

	# Пересчитываем локальные координаты X/Z в индекс клетки
	var x = int(round((local_pos.x + xoffset) / cell_size))
	var y = int(round((local_pos.z + yoffset) / cell_size))

	# Проверяем попадание в границы массива доски
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
