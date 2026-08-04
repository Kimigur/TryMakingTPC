extends Artifact
class_name RustySword

@export var durability: int = 3

func _init():
	set_artifact_name("Ржавый меч")
	set_artifact_type("weapon")
	set_artifact_slot_type("main_hand")

func get_actions():
	var action = RustySwordAttack.new()
	action.set_artifact(self)
	return [action]
