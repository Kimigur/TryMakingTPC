extends Node3D

@onready var core: Core = $"../../../Core"

var multimesh: MultiMesh
var tex_map: Dictionary = {} # Соответствие: Texture2D -> индекс слоя в Texture2DArray
var board_width: int = 0
var board_height: int = 0

func _ready() -> void:
	var board = core.get_board()
	var board_size: Vector2 = board.get_board_size()
	board_width = int(board_size.x)
	board_height = int(board_size.y)
	
	var total_cells: int = board_width * board_height
	var cell_size: float = 0.94 / float(board_width)

	# --- ШАГ 1: Собираем Texture2DArray из cell.icon всех клеток ---
	var icon_array = _build_texture_array(board)

	# --- ШАГ 2: Создаем меш и шейдерный материал ---
	var box_mesh = BoxMesh.new()
	box_mesh.size = Vector3(cell_size * 0.95, 0.05, cell_size * 0.95)

	var mat = ShaderMaterial.new()
	mat.shader = load("res://shaders/Board/cell_board.gdshader")
	mat.set_shader_parameter("icon_array", icon_array)
	box_mesh.material = mat

	# --- ШАГ 3: Инициализируем MultiMesh ---
	multimesh = MultiMesh.new()
	multimesh.transform_format = MultiMesh.TRANSFORM_3D
	multimesh.use_custom_data = true
	multimesh.mesh = box_mesh
	multimesh.instance_count = total_cells

	# --- ШАГ 4: Заполняем координаты и привязываем текстуры ---
	for x in range(board_width):
		for z in range(board_height):
			var index: int = x + z * board_width # Индекс в 1D массиве MultiMesh
			var cell = board.get_cell(x, z)
			
			# Позиционируем клетку с учетом размера cell_size
			var pos = Vector3(x * cell_size, 0.0, z * cell_size)
			multimesh.set_instance_transform(index, Transform3D(Basis(), pos))
			
			# Получаем индекс текстуры из карты
			var tex_idx: int = tex_map.get(cell.icon, 0)
			
			# Записываем данные: R = ID текстуры, G = ID состояния (0 = без подсветки)
			multimesh.set_instance_custom_data(index, Color(float(tex_idx), 0.0, 0.0, 0.0))

	var mm_instance = MultiMeshInstance3D.new()
	mm_instance.multimesh = multimesh
	add_child(mm_instance)


# Динамическая сборка Texture2DArray из всех уникальных иконок доски
func _build_texture_array(board) -> Texture2DArray:
	var images: Array[Image] = []
	tex_map.clear()

	for x in range(board_width):
		for z in range(board_height):
			var cell = board.get_cell(x, z)
			if cell and cell.icon and not tex_map.has(cell.icon):
				tex_map[cell.icon] = images.size()
				
				var img: Image = cell.icon.get_image()
				img.convert(Image.FORMAT_RGBA8) # Единый формат обязателен для Texture2DArray
				images.append(img)

	# Защита от пустой доски (создаем 1x1 пиксель-заглушку, если иконок нет)
	if images.is_empty():
		var dummy = Image.create(16, 16, false, Image.FORMAT_RGBA8)
		dummy.fill(Color.WHITE)
		images.append(dummy)

	var tex_array = Texture2DArray.new()
	tex_array.create_from_images(images)
	return tex_array


# Изменение подсветки клетки (x, y) без потери ее иконки
func set_cell_state(x: int, y: int, state_id: int) -> void:
	var index: int = x + y * board_width
	
	# Считываем текущие данные, чтобы не затереть R (индекс текстуры)
	var current_data = multimesh.get_instance_custom_data(index)
	current_data.g = float(state_id)
	
	multimesh.set_instance_custom_data(index, current_data)
	
func set_cell_state_array(arr:Array):
	for x in range(arr.size()):
		for y in range(arr[0].size()):
			set_cell_state(x,y,arr[x][y])
