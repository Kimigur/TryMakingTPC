extends Artifact
class_name RustySword

@export var durability: int = 10

func _init():
	set_artifact_name("Ржавый меч")
	set_artifact_type("sword")
	set_artifact_slot_type("hand")
	set_icon(preload("res://assets/2D/artifact/rusty_sword.png"))

func get_actions():
	var action = RustySwordAttack.new()
	action.set_artifact(self)
	var parryaction = parry.new()
	return [action,parryaction]
