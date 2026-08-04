extends Action
class_name RustySwordAttack

func _init():
	impacts = {"damage": 5}

func get_valid_targets(source: Unit, board: Board) -> Array:
	var targets = []
	var pos = source.get_position()
	
	# 8 соседних клеток (ближний бой)
	for dx in [-1, 0, 1]:
		for dy in [-1, 0, 1]:
			if dx == 0 and dy == 0:
				continue
			var nx = pos.x + dx
			var ny = pos.y + dy
			if board.is_valid_coord(nx, ny):
				var u = board.get_unit(nx, ny)
				if u != null:  # авантюрист
					targets.append(Vector2i(nx, ny))
	return targets

func execute(source: Unit, board: Board, target: Variant) -> bool:
	var sword = get_artifact() as RustySword
	if sword == null:
		return false
	
	print("предмет использован")
	
	# Наносим урон
	var t = target as Vector2i
	var unit = board.get_unit(t.x, t.y)
	if unit != null:
		# Когда будет take_damage:
		# unit.take_damage(impacts["damage"])
		print("бьём ", unit.get_unit_name(), " на ", impacts["damage"])
	
	# Тратим прочность
	sword.durability -= 1
	print("прочность: ", sword.durability)
	
	if sword.durability <= 0:
		print("меч сломался")
		source.set_main_hand_slot(null)  # снимаем, Ref<> обнулится, меч удалится
	
	return true
