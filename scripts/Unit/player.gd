extends Unit
class_name player

func _init():
	set_model(preload("res://assets/3D models/OBJ/Фигуры/Фигуры игрока/player.obj")) # Загрузка модели
	set_type(0) # Тип юнита
	
	set_max_hp(20)
	set_hp(20)
	set_strength(10)
	set_dexterity(14)
	set_max_speed(5)
		
	lock_stats() # Блакируем статы 

func ready():
	set_base_ac(10)
	
func get_actions() -> Array:
	return [move_action.new()]

func execute():
	pass
