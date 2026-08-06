# Класс: Board
# Наследует: RefCounted < Object

Игровая доска — сетка 20×20, на которой размещаются [[Cell]] и [[Unit]]. Содержит весь ландшафт боевого поля и отвечает за поиск пути, проверку досягаемости и перемещение.

## Свойства

Vector2 `board_size` 
Array `cells` 
Array `units`

## Методы

[[Cell]] get_cell(`x`: int, `y`: int) 
[[Cell]] get_cellv(`pos`: Vector2i) 
Array get_reachable_cells(`from`: Vector2i) 
[[Unit]] get_unit(`x`: int, `y`: int) 
[[Unit]] get_unitv(`pos`: Vector2i) 
bool is_valid_coord(`x`: int, `y`: int) 
bool move_unit(`from`: Vector2i, `to`: Vector2i) 
void set_cell(`x`: int, `y`: int, `cell`: [[Cell]]) 
void set_unit(`x`: int, `y`: int, `unit`: [[Unit]])

## Описания свойств

Vector2 `board_size`

#### get_board_size() getter

Размер доски. Всегда `Vector2(20, 20)`.

Array `cells`

#### get_cells_arrey() getter

Двумерный массив [[Cell]], индексируемый `[x][y]`.

Array `units`
#### get_units_arrey() getter

Двумерный массив [[Unit]], индексируемый `[x][y]`. `null` означает пустую клетку.

## Описания методов

#### [[Cell]] get_cell(`x`: int, `y`: int)

Возвращает [[Cell]] по координатам.

#### [[Cell]] get_cellv(`pos`: Vector2i)

Векторная версия `get_cell`.

#### Array get_reachable_cells(`from`: Vector2i)

BFS в 8 направлениях от `from`. Возвращает `Array[Vector2i]` всех пустых клеток, достижимых за текущую `current_speed` юнита, стоящего в `from`. Юниты и границы доски блокируют проход.

#### [[Unit]] get_unit(`x`: int, `y`: int)

Возвращает [[Unit]] в клетке или `null`.

#### [[Unit]] get_unitv(`pos`: Vector2i)

Векторная версия `get_unit`.

#### bool is_valid_coord(`x`: int, `y`: int)

Проверяет, лежит ли точка внутри доски 20×20.

#### bool move_unit(`from`: Vector2i, `to`: Vector2i)

Если путь от `from` до `to` существует, не длиннее `current_speed` юнита, и клетка `to` пуста — перемещает юнита, вычитает затраченную скорость из `current_speed` и возвращает `true`. Иначе `false`.

#### void set_cell(`x`: int, `y`: int, `cell`: [[Cell]])

Устанавливает [[Cell]] в клетку.

#### void set_unit(`x`: int, `y`: int, `unit`: [[Unit]])

Устанавливает [[Unit]] в клетку и обновляет его внутреннюю `position`.