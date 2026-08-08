extends Node3D
class_name CameraController

@onready var camera: Camera3D = $"../Camera3D"
@export var move_duration: float = 0.2
@export var rot_duration: float = 0.2
@onready var CurentAnchor: Node3D = $AnchorMainTabel
@export var camera_rotation: int = 0
@export var _is_moving: bool = false

var _dir_map: Dictionary = {
	0:   {"W": "north", "S": "south", "A": "west",  "D": "east"},
	90: {"W": "west",  "S": "east",  "A": "south", "D": "north"},
	180: {"W": "south", "S": "north", "A": "east",  "D": "west"},
	270:  {"W": "east",  "S": "west",  "A": "north", "D": "south"},
}

func _ready():
	camera.global_position = CurentAnchor.global_position
	camera.rotation = CurentAnchor.get_meta("rotation")


func _get_dir_from_facing(key: String) -> String:
	var effective_facing := camera_rotation
	if CurentAnchor.get_meta("lock_rotation") != null:
		# Для якорей стола используем их собственный поворот как facing
		effective_facing = CurentAnchor.get_meta("lock_rotation")
	return _dir_map[effective_facing][key]
	
func _unhandled_input(event: InputEvent):
	if _is_moving:
		return
	if event is InputEventKey and event.pressed:
		if CurentAnchor.get_meta("lock_rotation") != null:
			match event.keycode:
				KEY_W: _try_move(_get_dir_from_facing("W"))
				KEY_S: _try_move(_get_dir_from_facing("S"))
		else:
			match event.keycode:
				KEY_W: _try_move(_get_dir_from_facing("W"))
				KEY_S: _try_move(_get_dir_from_facing("S"))
				KEY_A: _try_move(_get_dir_from_facing("A"))
				KEY_D: _try_move(_get_dir_from_facing("D"))
				KEY_Q: _rotate(90)
				KEY_E: _rotate(-90)
				
func _try_move(dir_name: String):
	var target = CurentAnchor.get_meta(dir_name)
	if target == null:
		return
	_move_to(CurentAnchor.get_node_or_null(target) as Node3D)

## Поворот на месте (только в комнате)
func _rotate(delta: int):
	if CurentAnchor.get_meta("lock_rotation") != null:
		return
	_is_moving = true
	var new_facing := (camera_rotation + delta) % 360
	if new_facing < 0:
		new_facing += 360
	camera_rotation = new_facing
	var tween := create_tween()
	tween.set_ease(Tween.EASE_IN_OUT)
	tween.set_trans(Tween.TRANS_CUBIC)
	tween.tween_property(camera, "global_rotation", Vector3(0, _shortest_angle(camera.rotation.y, deg_to_rad(camera_rotation)), 0), rot_duration)
	tween.chain().tween_callback(func():
		_is_moving = false
	)

func _move_to(anchor: Node3D):
	_is_moving = true
	CurentAnchor = anchor
	
	# Определяем конечный поворот камеры
	var target_facing := Vector3(0, _shortest_angle(camera.rotation.y, deg_to_rad(camera_rotation)), 0)
	if anchor.get_meta("lock_rotation") != null:
		camera_rotation = anchor.get_meta("lock_rotation")
		target_facing = anchor.get_meta("rotation")
	
	var tween := create_tween()
	tween.set_ease(Tween.EASE_IN_OUT)
	tween.set_trans(Tween.TRANS_CUBIC)
	tween.set_parallel(true)
	tween.tween_property(camera, "global_position", anchor.global_position, move_duration)
	tween.tween_property(camera, "global_rotation", target_facing, move_duration)
	tween.chain().tween_callback(func():
		_is_moving = false
	)
	
func _shortest_angle(from: float, to: float) -> float:
	var diff := fmod(to - from, TAU)
	if diff < -PI:
		diff += TAU
	elif diff > PI:
		diff -= TAU
	return from + diff
