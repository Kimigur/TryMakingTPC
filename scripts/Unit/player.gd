extends Unit
class_name player

func _init():
	set_model(preload("res://assets/3D models/OBJ/Фигуры/Фигуры игрока/player.obj")) # Загрузка модели
	set_type(0) # Тип юнита
	
	set_dexterity(14)
	set_max_speed(5)
	
	lock_stats() # Блакируем статы 

func ready():
	pass

func execute():
	pass
