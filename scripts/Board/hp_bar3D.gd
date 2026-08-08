class_name HPBar3D
extends Sprite3D

const TEX_W: int = 250
const TEX_H: int = 100

func _init():
	billboard = BaseMaterial3D.BILLBOARD_ENABLED
	pixel_size = 0.00015
	centered = true
	double_sided = false
	transparent = true
	texture = _tex(1.0)

func update(hp: int, max_hp: int):
	if max_hp <= 0 or hp == max_hp:
		visible = false
		return
	visible = true
	var ratio: float = clamp(float(hp) / max_hp, 0.0, 1.0)
	texture = _tex(ratio)

func _tex(ratio: float) -> ImageTexture:
	var img = Image.create(TEX_W, TEX_H, false, Image.FORMAT_RGBA8)
	
	# Красный фон
	img.fill(Color(0.25, 0.0, 0.0, 0.9))
	
	# Зелёная полоска слева, шириной ratio
	var gw: int = int(TEX_W * ratio)
	if gw > 0:
		for x in range(gw):
			for y in range(TEX_H):
				img.set_pixel(x, y, Color(0.15, 0.85, 0.15))
	
	return ImageTexture.create_from_image(img)
