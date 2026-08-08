extends MeshInstance3D


@onready var next_turn_button: Area3D = $NextTurn
@onready var core: Core = $"../../../Core"

@onready var unit_action = $UnitAction
@onready var helm_action = $HelmAction
@onready var armor_action = $ArmorAction
@onready var boots_action = $BootsAction
@onready var gloves_action = $GlovesAction
@onready var gloves_action2 = $GlovesAction2
@onready var main_hand_action = $MainHandAction
@onready var off_hand_action = $OffHandAction
@onready var acc1_action = $AccAction1
@onready var acc2_action = $AccAction2
@onready var acc3_action = $AccAction3
@onready var acc4_action = $AccAction4

@onready var unit_action_model = $UnitAction/MeshInstance3D
@onready var helm_action_sprite = $HelmAction/Sprite3D
@onready var armor_action_sprite = $ArmorAction/Sprite3D
@onready var boots_action_sprite = $BootsAction/Sprite3D
@onready var gloves_action_sprite = $GlovesAction/Sprite3D
@onready var gloves_action2_sprite = $GlovesAction2/Sprite3D
@onready var main_hand_action_sprite = $MainHandAction/Sprite3D
@onready var off_hand_action_sprite = $OffHandAction/Sprite3D
@onready var acc1_action_sprite = $AccAction1/Sprite3D
@onready var acc2_action_sprite = $AccAction2/Sprite3D
@onready var acc3_action_sprite = $AccAction3/Sprite3D
@onready var acc4_action_sprite = $AccAction4/Sprite3D
@export var empty_icon:Texture2D = preload("res://icon.svg")

@export var actions_container: Control

@onready var actions_anchor: Node3D = $AnchorActionButtons
@export var action_button_template: PackedScene = preload("res://scenes/Board/action_button.tscn")
@export var button_spacing: float = 0.025


func _ready() -> void:
	next_turn_button.pressed.connect(ask_next_turn)
	unit_action.pressed.connect(_on_actions_received)
	helm_action.pressed.connect(_on_actions_received)
	armor_action.pressed.connect(_on_actions_received)
	boots_action.pressed.connect(_on_actions_received)
	gloves_action.pressed.connect(_on_actions_received)
	gloves_action2.pressed.connect(_on_actions_received)
	main_hand_action.pressed.connect(_on_actions_received)
	off_hand_action.pressed.connect(_on_actions_received)
	acc1_action.pressed.connect(_on_actions_received)
	acc2_action.pressed.connect(_on_actions_received)
	acc3_action.pressed.connect(_on_actions_received)
	acc4_action.pressed.connect(_on_actions_received)
	core.event_bus.subscribe("turn_changed", icon_update)
	
func icon_update(unit:Unit):
	icon_clear()
	if unit.model != null:
		unit_action_model.mesh = unit.model
	if unit.helm_slot != null:
		helm_action_sprite.texture = unit.helm_slot.icon if unit.helm_slot.icon else empty_icon
	if unit.armor_slot != null:
		armor_action_sprite.texture = unit.armor_slot.icon if unit.armor_slot.icon else empty_icon
	if unit.boots_slot != null:
		boots_action_sprite.texture = unit.boots_slot.icon if unit.boots_slot.icon else empty_icon
	if unit.gloves_slot != null:
		gloves_action_sprite.texture = unit.gloves_slot.icon if unit.gloves_slot.icon else empty_icon
		gloves_action2_sprite.texture = unit.gloves_slot.icon if unit.gloves_slot.icon else empty_icon
	if unit.main_hand_slot != null:
		main_hand_action_sprite.texture = unit.main_hand_slot.icon if unit.main_hand_slot.icon else empty_icon
	if unit.off_hand_slot != null:
		off_hand_action_sprite.texture = unit.off_hand_slot.icon if unit.off_hand_slot.icon else empty_icon
	if unit.accessory_1_slot != null:
		acc1_action_sprite.texture = unit.accessory_1_slot.icon if unit.accessory_1_slot.icon else empty_icon
	if unit.accessory_2_slot != null:
		acc2_action_sprite.texture = unit.accessory_2_slot.icon if unit.accessory_2_slot.icon else empty_icon
	if unit.accessory_3_slot != null:
		acc3_action_sprite.texture = unit.accessory_3_slot.icon if unit.accessory_3_slot.icon else empty_icon
	if unit.accessory_4_slot != null:
		acc4_action_sprite.texture = unit.accessory_4_slot.icon if unit.accessory_4_slot.icon else empty_icon
	
func icon_clear():
	unit_action_model.mesh = null
	helm_action_sprite.texture = null
	armor_action_sprite.texture = null
	boots_action_sprite.texture = null
	gloves_action_sprite.texture = null
	gloves_action2_sprite.texture = null
	main_hand_action_sprite.texture = null
	off_hand_action_sprite.texture = null
	acc1_action_sprite.texture = null
	acc2_action_sprite.texture = null
	acc3_action_sprite.texture = null
	acc4_action_sprite.texture = null

func ask_next_turn():
	$"../../../CameraController"._move_to($"../../../CameraController/AnchorBoard")
	_clear_action_buttons()
	core.next_turn()
	
func _on_actions_received(actions: Array) -> void:
	_clear_action_buttons()
	
	if actions.is_empty():
		return

	# Спавним 3D-кнопки списком
	for i in range(actions.size()):
		var action = actions[i]
		_spawn_3d_action_button(action, i)

# Очистка старых 3D-кнопок с якоря
func _clear_action_buttons() -> void:
	if not actions_anchor:
		return
	for child in actions_anchor.get_children():
		child.queue_free()

# Создание и позиционирование 3D-кнопки
func _spawn_3d_action_button(action: Object, index: int) -> void:
	if not actions_anchor or not action_button_template:
		return

	var btn = action_button_template.instantiate() as Area3D
	
	# Смещение каждой следующей кнопки вниз по оси Y (или Z, если нужно подправить)
	btn.position = Vector3(0, 0, index * button_spacing)
	
	# Заполнение данных в дочерние 3D-ноды шаблона (Sprite3D / Label3D)
	_setup_button_visuals(btn, action)
	
	# Подключение клика по 3D коллизии
	btn.input_event.connect(func(_cam, event, _pos, _norm, _shape):
		if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT and event.pressed:
			_on_action_clicked(action)
	)

	actions_anchor.add_child(btn)

# Заполнение визуалов шаблона
func _setup_button_visuals(btn: Area3D, action: Object) -> void:
	# Если у шаблона есть свой скрипт с методом setup:
	if btn.has_method("setup"):
		btn.setup(action.name, action.icon, _get_cost_name(action.cost_type))
		return

	# Иначе ищем стандартные 3D-ноды внутри шаблона по именам
	var icon_node = btn.get_node_or_null("Icon") as Sprite3D
	var name_node = btn.get_node_or_null("Name") as Label3D
	var cost_node = btn.get_node_or_null("Cost") as Label3D

	if icon_node and action.icon:
		icon_node.texture = action.icon
	if name_node:
		name_node.text = action.name
	if cost_node:
		cost_node.text = "[" + _get_cost_name(action.cost_type) + "]"

# ЗАГЛУШКА: Вызывается при клике на 3D-кнопку действия
func _on_action_clicked(action: Object) -> void:
	_clear_action_buttons()
	$"..".set_action(action)

# Конвертер констант стоимость в текст
func _get_cost_name(cost_type: int) -> String:
	match cost_type:
		0: return "FREE"
		1: return "MAIN"
		2: return "BONUS"
		3: return "REACTION"
		4: return "LEGENDARY"
		_: return "UNKNOWN"
