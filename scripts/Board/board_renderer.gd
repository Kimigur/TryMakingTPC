extends Node3D
class_name BoardRenderer

@export var core: Core

var _cells: Array[MeshInstance3D] = []
var _units: Dictionary = {}  # Unit -> {node: Node3D, mesh: MeshInstance3D, hp: HPBar3D}

func _ready():
	_build_cells()

func _build_cells():
	var board = core.get_board()
	var size = board.get_board_size()
	var cell_size = 0.94 / size[0]
	
	for x in range(size[0]):
		for y in range(size[1]):
			var m = MeshInstance3D.new()
			var box = BoxMesh.new()
			box.size = Vector3(cell_size * 0.9, 0.02, cell_size * 0.9)
			m.mesh = box
			m.position = _world_pos(Vector2i(x, y)) - Vector3(0, 0.01, 0)
			add_child(m)
			_cells.append(m)

func refresh(selected: Vector2i, reachable: Array, paths: Array, targets: Array):
	var board = core.get_board()
	var size = board.get_board_size()
	var idx = 0
	
	# --- клетки ---
	for x in range(size[0]):
		for y in range(size[1]):
			var c = Vector2i(x, y)
			var mat = _cells[idx].get_active_material(0)
			if mat == null:
				mat = StandardMaterial3D.new()
				_cells[idx].material_override = mat
			
			var color = Color.DARK_GRAY
			if c == selected:       color = Color.YELLOW
			elif c in paths:        color = Color.CYAN
			elif c in targets:      color = Color.ORANGE
			elif c in reachable:    color = Color.GREEN
			mat.albedo_color = color
			idx += 1
	
	# --- юниты ---
	var alive: Array[Unit] = []
	for x in range(size[0]):
		for y in range(size[1]):
			var u = board.get_unit(x, y)
			if u == null: continue
			alive.append(u)
			var pos = _world_pos(Vector2i(x, y))
			
			if not _units.has(u):
				var node = Node3D.new()
				var mesh = MeshInstance3D.new()
				mesh.mesh = u.get_model()
				mesh.scale = Vector3(1.6, 1.6, 1.6)
				mesh.position.y = 0.05
				node.add_child(mesh)
				
				var hp = HPBar3D.new()
				hp.position.y = 0.12
				node.add_child(hp)
				
				add_child(node)
				_units[u] = {node = node, hp = hp}
			
			var d = _units[u]
			d.node.position = pos
			d.node.visible = true
			d.hp.update(u.get_hp(), u.get_max_hp())
	
	# скрыть ушедших/умерших
	for u in _units.keys():
		if not u in alive:
			_units[u].node.visible = false

func _world_pos(c: Vector2i) -> Vector3:
	return Vector3(c.x * 0.028 - 0.445, 0, c.y * 0.028 - 0.445)
