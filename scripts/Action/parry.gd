extends Action
class_name parry

func _init():
	impacts = {"damage": 5}
	cost_type = COST_BONUS
	set_icon(preload("res://assets/2D/artifact/rusty_sword.png"))

func get_valid_targets(source: Unit, board: Board) -> Array:
	var ret :Array;
	ret.push_back(source.position)
	return ret
	
func _execute(source: Unit, board: Board, target: Variant) -> bool:
	source.add_ac(2)
	return true
