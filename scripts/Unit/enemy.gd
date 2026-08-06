extends Unit
class_name Enemy

func _init():
	set_model(preload("res://assets/3D models/OBJ/Фигуры/enemy.obj")) # Загрузка модели
	set_type(1) # Тип юнита
	
	set_max_hp(20)
	set_hp(20)
	
	set_strength(10)
	set_dexterity(14)
	set_max_speed(5)
	
	set_ac(10)
	
	lock_stats() # Блакируем статы 

func ready():
	set_base_ac(10)

func execute():
	if main_hand_slot != null:
		var actions = main_hand_slot.get_actions()
		if !actions.is_empty():
			var arr = actions[0].get_valid_targets(self, get_board())
			if !arr.is_empty():
				actions[0].execute(self,get_board(),arr[0])
	else:
		var movecarr = get_board().get_reachable_cells(get_position())
		if movecarr.size() > 0:
			var movec = movecarr[randi() % movecarr.size()]
			get_board().move_unit(get_position(), movec)
