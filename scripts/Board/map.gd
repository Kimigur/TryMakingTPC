extends MeshInstance3D


@onready var core: Core = $"../../Core"
@onready var board_cels = $Board
@onready var board_node = $"."

@export var cell_size: float
@export var xoffset: float = 0.445
@export var yoffset: float = 0.445

@export var state_array: Array
@export var previous_select_pos: Vector2i = Vector2i(0,0)

var _unit_nodes: Dictionary = {} 

var visuals_node: Node3D

@export var current_action:Action

func test():
	var e = Enemy.new()
	var p = player.new()
	var t1 = tree.new()
	
	core.get_board().set_unit(3, 4, e)
	core.get_board().set_unit(13, 8, p)
	core.get_board().set_unit(5, 5, t1)
	
	e.set_main_hand_slot(RustySword.new())
	p.set_main_hand_slot(RustySword.new())
	p.set_off_hand_slot(RustySword.new())
	
	core.start_combat()

func _ready():
	visuals_node = Node3D.new()
	visuals_node.name = "Visuals"
	add_child(visuals_node)
	
	var board = core.get_board()
	cell_size = 0.94 / float(board.board_size[0])
	
	state_array.clear()
	for x in range(board.board_size[0]):
		var array:Array
		for y in range(board.board_size[1]):
			array.append(0)
		state_array.append(array)
		
	var event_bus = core.get_event_bus()
	
	test()
	
	
	event_bus.subscribe("turn_changed", turn_changed)
	event_bus.subscribe("unit_move", unit_move)
	event_bus.subscribe("action_executed", action_executed)
	
	draw_unit()

func draw_unit():
	var board = core.get_board()
	var alive: Array[Unit] = []
	
	for x in range(board.board_size[0]):
		for y in range(board.board_size[1]):
			var unit = board.get_unit(x, y)
			if unit == null:
				continue
			
			alive.append(unit)
			var pos = Vector3(x * cell_size - xoffset, 0, y * cell_size - yoffset)
			
			if not _unit_nodes.has(unit):
				# Создаём контейнер для юнита
				var node = Node3D.new()
				node.name = unit.unit_name if not unit.unit_name.is_empty() else "Unit"
				
				# Модель
				var mesh = MeshInstance3D.new()
				mesh.mesh = unit.get_model()
				mesh.scale = Vector3(1.6, 1.6, 1.6)
				mesh.position.y = 0.05
				node.add_child(mesh)
				
				# HP-бар
				var hp = HPBar3D.new()
				hp.position.y = 0.12
				node.add_child(hp)
				
				visuals_node.add_child(node)
				_unit_nodes[unit] = { node = node, mesh = mesh, hp = hp }
			
			var data = _unit_nodes[unit]
			data.node.position = pos
			data.node.visible = true
			data.hp.update(unit.get_hp(), unit.get_max_hp())
	
	# Скрываем юнитов, которых больше нет на доске (умерли/удалились)
	for unit in _unit_nodes.keys():
		if not unit in alive:
			_unit_nodes[unit].node.visible = false

func _unhandled_input(event: InputEvent) -> void:
	var board = core.get_board()
	if event is InputEventMouseMotion:
		var current_hover = _get_cell_from_mouse(event.position)
		if current_hover != previous_select_pos:
			if board.is_valid_coord(previous_select_pos.x,previous_select_pos.y):
				board_cels.set_cell_state(previous_select_pos.x, previous_select_pos.y, state_array[previous_select_pos.x][previous_select_pos.y])
			
			if current_action != null and current_action.name == "move":
				if state_array[current_hover.x][current_hover.y] == 2:
					var move_arr = state_array.duplicate(true)
					var unit_pos = core.get_current_unit().position
					var path = board.get_path(unit_pos, current_hover)
					for i in path:
						move_arr[i.x][i.y]=1
					
					board_cels.set_cell_state_array(move_arr)
				else:
					board_cels.set_cell_state_array(state_array)
					
			
			if board.is_valid_coord(current_hover.x, current_hover.y):
				board_cels.set_cell_state(current_hover.x, current_hover.y, 1)
			
			
			previous_select_pos = current_hover
	elif event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		var clicked_cell = _get_cell_from_mouse(event.position)
		if clicked_cell != Vector2i(-1, -1):
			pass
			_on_cell_clicked(clicked_cell)

func _get_cell_from_mouse(mouse_pos: Vector2) -> Vector2i:
	var camera = $"../../Camera3D"
	
	var from = camera.project_ray_origin(mouse_pos)
	var dir = camera.project_ray_normal(mouse_pos)
	
	var map_plane = Plane(board_node.global_transform.basis.y, board_node.global_position)
	var hit_pos = map_plane.intersects_ray(from, dir)
	if hit_pos == null:
		return Vector2i(-1, -1)
	
	var local_pos = board_node.to_local(hit_pos)
	
	var x = int(round((local_pos.x + xoffset) / cell_size))
	var y = int(round((local_pos.z + yoffset) / cell_size))
	
	var board = core.get_board()
	if board.is_valid_coord(x,y):
		return Vector2i(x, y)
	
	return Vector2i(-1, -1)

func reset_state_array():
	var board = core.get_board()
	for x in range(board.board_size[0]):
		for y in range(board.board_size[1]):
			state_array[x][y] = 0
	
func turn_changed(unit):
	draw_unit()

func unit_move(unit, from, to):
	draw_unit()
	
func action_executed(source, action):
	draw_unit()
	
func set_action(action: Action):
	if core.get_current_unit().type != 0:
		return
	var board = core.get_board()
	var valid_target:Array = action.get_valid_targets(core.get_current_unit(), core.get_board())
	reset_state_array()
	for i in valid_target:
		if board.get_unitv(i) != null:
			state_array[i.x][i.y] = 3
		else:
			state_array[i.x][i.y] = 2
	board_cels.set_cell_state_array(state_array)
	
	current_action = action
	
	$"../../CameraController"._move_to($"../../CameraController/AnchorBoard")

func _on_cell_clicked(cell:Vector2i):
	if current_action == null:
		return
	current_action.execute(core.get_current_unit(),core.board,cell)
	current_action = null
	reset_state_array()
	board_cels.set_cell_state_array(state_array)
