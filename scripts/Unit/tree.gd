extends Unit
class_name tree

func _init():
	set_model(preload("res://assets/3D models/OBJ/Фигуры/Дерево/tree.obj")) # Загрузка модели
	set_type(2) # Тип юнита
	
	set_max_speed(3)
	set_current_speed(3)
	
	lock_stats() # Блакируем статы 

func ready():
	pass

func execute():
	print("Вы слышите шелист листьев")
	
	if randi()%8 == 0:
		var t = tree.new()
		var sarr = get_board().get_reachable_cells(position)
		if !sarr.is_empty():
			var sc = sarr[randi() % sarr.size()]
			get_board().set_unit(sc.x,sc.y,t)
			get_core().add_to_queue(t)
			set_current_speed(get_current_speed()-1)
	
	
