extends Area3D


signal pressed(actions: Array)

@export var hover_scale: Vector3 = Vector3(1.1, 1.1, 1.1)
var default_scale: Vector3

@onready var core = $"../../../../Core"

enum SlotType {
	UNIT,
	MAIN_HAND,
	OFF_HAND,
	ARMOR,
	HELM,
	GLOVES,
	BOOTS,
	ACC_1,
	ACC_2,
	ACC_3,
	ACC_4
}

@export var slot_type: SlotType = SlotType.UNIT

func _ready() -> void:	
	input_event.connect(_on_input_event)
	mouse_entered.connect(_on_mouse_entered)
	mouse_exited.connect(_on_mouse_exited)

func _on_input_event(_camera: Node, event: InputEvent, _position: Vector3, _normal: Vector3, _shape_idx: int) -> void:
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT and event.pressed:
		_on_pressed()

func _on_pressed() -> void:
	pressed.emit(_get_actions_for_selected_slot())
	
# Эффект при наведении курсора
func _on_mouse_entered() -> void:
	pass

# Возврат в исходный вид при уходе курсора
func _on_mouse_exited() -> void:
	pass


func _get_actions_for_selected_slot() -> Array:
	var unit = core.get_current_unit()
	if not unit:
		return []

	# Если кнопка привязана к самому юниту
	if slot_type == SlotType.UNIT:
		return unit.get_actions()

	# Ищем нужный слот у юнита
	var slot_obj = null
	match slot_type:
		SlotType.MAIN_HAND: slot_obj = unit.main_hand_slot
		SlotType.OFF_HAND:  slot_obj = unit.off_hand_slot
		SlotType.ARMOR:     slot_obj = unit.armor_slot
		SlotType.HELM:      slot_obj = unit.helm_slot
		SlotType.GLOVES:    slot_obj = unit.gloves_slot
		SlotType.BOOTS:     slot_obj = unit.boots_slot
		SlotType.ACC_1:     slot_obj = unit.accessory_1_slot
		SlotType.ACC_2:     slot_obj = unit.accessory_2_slot
		SlotType.ACC_3:     slot_obj = unit.accessory_3_slot
		SlotType.ACC_4:     slot_obj = unit.accessory_4_slot

	# Проверяем, экипирован ли предмет в этот слот
	if slot_obj != null and slot_obj.has_method("get_actions"):
		return slot_obj.get_actions()

	return [] # Если слот пустой (например, нет шлема), возвращаем пустой массив
