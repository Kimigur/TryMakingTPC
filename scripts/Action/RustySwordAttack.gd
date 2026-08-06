extends Action
class_name RustySwordAttack

func _init():
	impacts = {"damage": 5}
	cost_type = COST_MAIN
	set_icon(preload("res://assets/2D/artifact/rusty_sword.png"))

func get_valid_targets(source: Unit, board: Board) -> Array:
	var helper = Helper.new()
	
	return helper.get_all_target(board, source.position, 1, Helper.TARGET_ANY)

func _execute(source: Unit, board: Board, target: Variant) -> bool:
	var sword = get_artifact() as RustySword
	if sword == null:
		return false
	
	print("предмет использован")
	
	# Наносим урон
	var t = target as Vector2i
	var unit = board.get_unit(t.x, t.y)
	attack(source, unit, 15, _on_hit)
	
	# Тратим прочность
	sword.durability -= 1
	print("прочность: ", sword.durability)
	
	if sword.durability <= 0:
		print("меч сломался")
		source.set_main_hand_slot(null)  # снимаем, Ref<> обнулится, меч удалится
	
	return true

func _on_hit(attacker :Unit, defender:Unit, is_crit:bool):
	var damage = attacker.roll_dice(1,10,attacker.get_strength_mod())
	if is_crit:
		damage *= 2
	defender.take_damage(damage, SLASHING)
		
