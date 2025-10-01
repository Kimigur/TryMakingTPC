extends Button

@onready
var this = $"."

func _on_mouse_entered() -> void:
	if(randi()%20 == 0):
		this.text = "Боря иди на..."
	else:
		this.text = "Alt + F4"

func _on_mouse_exited() -> void:
	this.text =  "Выход"

func _on_pressed() -> void:
	get_tree().quit()
