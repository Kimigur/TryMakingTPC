extends Unit
class_name Enemy

func _init():
	set_model(preload("res://assets/3D models/OBJ/Фигуры/enemy.obj")) # Загрузка модели
	set_type(1) # Тип юнита
	
	set_dexterity(14)
	set_max_speed(5)
	
	lock_stats() # Блакируем статы 

func ready():
	pass

func execute():
	var movecarr = get_board().get_reachable_cells(position)
	if movecarr.size() > 0:
			var movec = movecarr[randi() % movecarr.size()]
			get_board().move_unit(position, movec)
