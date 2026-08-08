extends Area3D


signal pressed

@export var hover_scale: Vector3 = Vector3(1.1, 1.1, 1.1)
var default_scale: Vector3

func _ready() -> void:	
	input_event.connect(_on_input_event)
	mouse_entered.connect(_on_mouse_entered)
	mouse_exited.connect(_on_mouse_exited)

func _on_input_event(_camera: Node, event: InputEvent, _position: Vector3, _normal: Vector3, _shape_idx: int) -> void:
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT and event.pressed:
		_on_pressed()

func _on_pressed() -> void:
	pressed.emit()
	

# Эффект при наведении курсора
func _on_mouse_entered() -> void:
	pass

# Возврат в исходный вид при уходе курсора
func _on_mouse_exited() -> void:
	pass
