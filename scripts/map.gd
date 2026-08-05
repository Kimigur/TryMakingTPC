extends MeshInstance3D

@onready var core_node: Core = $"../Core"
@onready var map_node: Node3D = $"../Map"

@export var cell_size: float = 0.028
@export var xoffset: float = 0.445
@export var yoffset: float = 0.445

# --- UI ---
var canvas_layer: CanvasLayer
var item_container: HBoxContainer
var next_turn_button: Button

# --- 3D ---
var visuals_node: Node3D
var turn_arrow: Node3D

# --- State ---
var selected_cell: Vector2i = Vector2i(-1, -1)
var hovered_cell: Vector2i = Vector2i(-1, -1)
var reachable_cells: Array = []
var path_cells: Array = []
var selected_action: Action = null
var action_targets: Array = []


func test():
	var e = Enemy.new()
	var p = player.new()
	var t1 = tree.new()
	var sword = RustySword.new()
	var sword2 = RustySword.new()
	
	core_node.get_board().set_unit(3, 4, e)
	core_node.get_board().set_unit(13, 8, p)
	core_node.get_board().set_unit(5, 5, t1)
	
	e.set_main_hand_slot(sword)
	p.set_main_hand_slot(sword2)
	
	core_node.start_combat()


func _ready() -> void:
	visuals_node = Node3D.new()
	visuals_node.name = "Visuals"
	add_child(visuals_node)
	
	_setup_ui()
	_setup_turn_arrow()
	
	if not core_node:
		return
	await get_tree().process_frame
	
	var event_bus = core_node.get_event_bus()
	if event_bus:
		event_bus.subscribe("turn_changed", _on_turn_changed)
		event_bus.subscribe("unit_damaged", _on_unit_damaged)
		event_bus.subscribe("unit_move", _on_unit_moved)
	test()
	draw_debug_board()


func _setup_ui():
	canvas_layer = CanvasLayer.new()
	canvas_layer.layer = 10
	add_child(canvas_layer)
	
	# --- Панель предметов ---
	var panel = PanelContainer.new()
	panel.set_anchors_preset(Control.PRESET_BOTTOM_WIDE)
	panel.offset_top = -90
	panel.offset_bottom = 0
	
	var panel_style = StyleBoxFlat.new()
	panel_style.bg_color = Color(0.1, 0.1, 0.12, 0.95)
	panel_style.border_width_top = 2
	panel_style.border_width_bottom = 2
	panel_style.border_width_left = 2
	panel_style.border_width_right = 2
	panel_style.border_color = Color(0.4, 0.4, 0.4)
	panel.add_theme_stylebox_override("panel", panel_style)
	
	canvas_layer.add_child(panel)
	
	var margin = MarginContainer.new()
	margin.add_theme_constant_override("margin_left", 15)
	margin.add_theme_constant_override("margin_right", 15)
	margin.add_theme_constant_override("margin_top", 10)
	margin.add_theme_constant_override("margin_bottom", 10)
	panel.add_child(margin)
	
	item_container = HBoxContainer.new()
	item_container.alignment = BoxContainer.ALIGNMENT_CENTER
	item_container.add_theme_constant_override("separation", 12)
	margin.add_child(item_container)
	
	# --- Кнопка хода ---
	next_turn_button = Button.new()
	next_turn_button.text = "Следующий ход"
	next_turn_button.size = Vector2(140, 40)
	next_turn_button.position = Vector2(
		get_viewport().get_visible_rect().size.x - 160,
		20
	)
	canvas_layer.add_child(next_turn_button)
	next_turn_button.pressed.connect(_on_next_turn_pressed)


func _setup_turn_arrow():
	turn_arrow = Node3D.new()
	turn_arrow.name = "TurnArrow"
	add_child(turn_arrow)
	
	var shaft = MeshInstance3D.new()
	var cyl = CylinderMesh.new()
	cyl.top_radius = 0.010      # основание внизу
	cyl.bottom_radius = 0.0     # остриё вверху
	cyl.height = 0.08
	shaft.mesh = cyl
	shaft.position.y = 0.0
	turn_arrow.add_child(shaft)
	
	var mat = StandardMaterial3D.new()
	mat.albedo_color = Color.YELLOW
	mat.emission_enabled = true
	mat.emission = Color.YELLOW
	mat.emission_energy = 3.0
	shaft.material_override = mat
	
	turn_arrow.visible = false


func _on_unit_moved(unit, from, to):
	var current = core_node.get_current_unit()
	if current != null and current == unit and unit.get_type() == 0:
		_update_turn_arrow(unit)

func _on_next_turn_pressed():
	core_node.next_turn()


func _on_turn_changed(unit) -> void:
	if unit != null and unit.get_type() == 0:
		selected_cell = unit.get_position()
		reachable_cells = core_node.get_reachable_cells(selected_cell)
		_update_turn_arrow(unit)
		_update_item_panel(unit)
	else:
		selected_cell = Vector2i(-1, -1)
		reachable_cells.clear()
		path_cells.clear()
		action_targets.clear()
		selected_action = null
		_hide_turn_arrow()
		_update_item_panel(null)
	
	draw_debug_board()


func _update_turn_arrow(unit: Unit):
	if unit == null:
		_hide_turn_arrow()
		return
	var pos = _get_world_pos(unit.get_position())
	turn_arrow.position = pos + Vector3(0, 0.18, 0)
	turn_arrow.visible = true


func _hide_turn_arrow():
	turn_arrow.visible = false


func _update_item_panel(unit: Unit):
	for child in item_container.get_children():
		child.queue_free()
	
	if unit == null or unit.get_type() != 0:
		return
	
	var inventory = unit.get_inventory()
	var has_items = false
	
	for art_ref in inventory:
		var art = art_ref as Artifact
		if art == null:
			continue
		var actions = art.get_actions()
		if actions.is_empty():
			continue
		
		has_items = true
		var btn = TextureButton.new()
		btn.custom_minimum_size = Vector2(64, 64)
		btn.stretch_mode = TextureButton.STRETCH_KEEP_ASPECT_CENTERED
		
		var icon = art.get_icon()
		if icon != null:
			btn.texture_normal = icon
		else:
			# Fallback — цветная кнопка
			var tex = GradientTexture2D.new()
			tex.width = 64
			tex.height = 64
			var grad = Gradient.new()
			grad.set_color(0, Color.DARK_RED)
			grad.set_color(1, Color.ORANGE_RED)
			tex.gradient = grad
			btn.texture_normal = tex
		
		btn.pressed.connect(_on_item_button_pressed.bind(art, unit))
		item_container.add_child(btn)
	
	# Если пусто — покажи заглушку
	if not has_items:
		var label = Label.new()
		label.text = "Нет предметов"
		label.modulate = Color.GRAY
		item_container.add_child(label)


func _on_item_button_pressed(artifact: Artifact, unit: Unit):
	var actions = artifact.get_actions()
	if actions.is_empty():
		return
	
	selected_action = actions[0]
	action_targets = selected_action.get_valid_targets(unit, core_node.get_board())
	reachable_cells.clear()
	path_cells.clear()
	selected_cell = Vector2i(-1, -1)
	draw_debug_board()


func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventMouseMotion:
		var current_hover = _get_cell_from_mouse(event.position)
		if current_hover != hovered_cell:
			hovered_cell = current_hover
			_update_current_path()
			draw_debug_board()
	
	elif event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		var clicked_cell = _get_cell_from_mouse(event.position)
		if clicked_cell != Vector2i(-1, -1):
			_on_cell_clicked(clicked_cell)


func _update_current_path() -> void:
	if selected_cell != Vector2i(-1, -1) and hovered_cell in reachable_cells:
		path_cells = core_node.get_path(selected_cell, hovered_cell)
	else:
		path_cells.clear()


func _on_cell_clicked(cell_coord: Vector2i) -> void:
	# 1. Выполнение выбранного действия
	if selected_action != null:
		if cell_coord in action_targets:
			var current = core_node.get_current_unit()
			if current != null:
				selected_action.execute(current, core_node.get_board(), cell_coord)
		
		selected_action = null
		action_targets.clear()
		path_cells.clear()
		selected_cell = Vector2i(-1, -1)
		draw_debug_board()
		return
	
	# 2. Старый костыль (0,0) — убран, теперь кнопка. Но оставим на всякий случай
	if cell_coord == Vector2i(0, 0):
		selected_cell = Vector2i(-1, -1)
		reachable_cells.clear()
		path_cells.clear()
		core_node.next_turn()
		draw_debug_board()
		return
	
	# 3. Ходьба
	if selected_cell != Vector2i(-1, -1) and cell_coord in reachable_cells:
		var moved = core_node.move_unit(selected_cell, cell_coord)
		if moved:
			selected_cell = Vector2i(-1, -1)
			reachable_cells.clear()
			path_cells.clear()
			draw_debug_board()
			return
	
	# 4. Выбор юнита
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
	for child in visuals_node.get_children():
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
			var pos = _get_world_pos(coord)
			
			var cell_color = Color.DARK_GRAY
			
			if coord == selected_cell:
				cell_color = Color.YELLOW
			elif coord in path_cells:
				cell_color = Color.CYAN
			elif coord in action_targets:
				cell_color = Color.ORANGE
			elif coord in reachable_cells:
				cell_color = Color.GREEN
			
			_spawn_debug_box(pos - Vector3(0, 0.035, 0), Vector3(cell_size * 0.9, 0.1, cell_size * 0.9), cell_color)
			
			if unit != null:
				var unit_mesh = unit.get_model()
				var mesh_inst = MeshInstance3D.new()
				mesh_inst.mesh = unit_mesh
				mesh_inst.position = pos + Vector3(0, 0.05, 0)
				mesh_inst.scale = Vector3(1.6, 1.6, 1.6)
				visuals_node.add_child(mesh_inst)
				
				if unit.get_hp() < unit.get_max_hp():
					_spawn_hp_bar(pos + Vector3(0, 0.12, 0), unit)


func _get_world_pos(coord: Vector2i) -> Vector3:
	return Vector3(coord.x * cell_size - xoffset, 0, coord.y * cell_size - yoffset)


func _spawn_debug_box(pos: Vector3, size: Vector3, color: Color) -> void:
	var mesh_inst = MeshInstance3D.new()
	var box = BoxMesh.new()
	box.size = size
	
	var mat = StandardMaterial3D.new()
	mat.albedo_color = color
	box.material = mat
	
	mesh_inst.mesh = box
	mesh_inst.position = pos
	visuals_node.add_child(mesh_inst)


func _spawn_hp_bar(pos: Vector3, unit: Unit) -> void:
	var max_hp = unit.get_max_hp()
	var hp = unit.get_hp()
	if max_hp <= 0:
		return
	
	var ratio = float(hp) / max_hp
	var bar_width = cell_size * 0.8
	var bar_height = 0.02
	
	# Красный фон
	var bg = MeshInstance3D.new()
	var bg_box = BoxMesh.new()
	bg_box.size = Vector3(bar_width, bar_height, 0.005)
	bg.mesh = bg_box
	bg.position = pos
	visuals_node.add_child(bg)
	
	var bg_mat = StandardMaterial3D.new()
	bg_mat.albedo_color = Color.RED
	bg_box.material = bg_mat
	
	# Зелёная часть
	var fg = MeshInstance3D.new()
	var fg_box = BoxMesh.new()
	fg_box.size = Vector3(bar_width * ratio, bar_height+0.005, 0.007)
	fg.mesh = fg_box
	fg.position = pos - Vector3(bar_width * (1.0 - ratio) * 0.5, 0, 0)
	if hp>0:
		visuals_node.add_child(fg)
	
	var fg_mat = StandardMaterial3D.new()
	fg_mat.albedo_color = Color.GREEN
	fg_box.material = fg_mat


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


func _on_unit_damaged(unit, damage, damage_type):
	draw_debug_board()
