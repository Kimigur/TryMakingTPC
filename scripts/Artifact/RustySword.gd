extends Artifact
class_name RustySword

@export var durability: int = 3

func _init():
	set_artifact_name("Ржавый меч")
	set_artifact_type("weapon")
	set_artifact_slot_type("main_hand")
	set_icon(preload("res://assets/2D/artifact/rusty_sword.png"))

func get_actions():
	var action = RustySwordAttack.new()
	action.set_artifact(self)
	return [action]
