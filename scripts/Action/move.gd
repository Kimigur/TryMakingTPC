extends Action
class_name move_action

func _init():
	cost_type = COST_FREE
	name = "move"
	
func get_valid_targets(source: Unit, board: Board) -> Array:
	return board.get_reachable_cells(source.position)
	
func _execute(source: Unit, board: Board, target: Variant) -> bool:
	return board.move_unit(source.position, target)
