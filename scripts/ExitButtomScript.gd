extends Button

@onready
var this = $"."

func _on_mouse_entered() -> void:
	this.text = "Alt + F4"

func _on_mouse_exited() -> void:
	this.text =  "Выход"
