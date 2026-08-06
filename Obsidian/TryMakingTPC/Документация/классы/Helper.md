# Класс: Helper
# Наследует: RefCounted < Object

Утилитарный класс для поиска целей на доске. Все методы возвращают `Array[Vector2i]`.

## Методы

Array get_all_target(`board`: [[Board]], `start_pos`: Vector2i, `radius`: int, `target_type`: int) 
Array get_bfs_target(`board`: [[Board]], `start_pos`: Vector2i, `radius`: int, `target_type`: int) 
Array get_bfs_target_path(`board`: [[Board]], `start_pos`: Vector2i, `radius`: int, `end_pos`: Vector2i) 
Array get_line_target(`board`: [[Board]], `start_pos`: Vector2i, `radius`: int, `target_type`: int)

## Константы

Таблица

| Константа            | Значение | Описание                                                      |
| :------------------- | :------- | :------------------------------------------------------------ |
| `TARGET_EMPTY`       | `-2`     | Пустые клетки. Луч/BFS проходит, клетка попадает в результат. |
| `TARGET_ANY`         | `-1`     | Любой юнит.                                                   |
| `TARGET_DM_DUMMY`    | `0`      | Кукла ДМ-а (type == 0).                                       |
| `TARGET_ADVENTURER`  | `1`      | Авантюрист или враг (type == 1).                              |
| `TARGET_ENVIRONMENT` | `2`      | Нейтральный объект (type == 2).                               |

## Описания методов

#### Array get_line_target(`board`: [[Board]], `start_pos`: Vector2i, `radius`: int, `target_type`: int)

Бросает лучи от `start_pos` ко всем клеткам периметра квадрата `radius`. Любой юнит блокирует луч. Если `target_type == TARGET_EMPTY`, возвращает достижимые пустые клетки. Иначе — первого подходящего юнита на каждом луче.

#### Array get_bfs_target(`board`: [[Board]], `start_pos`: Vector2i, `radius`: int, `target_type`: int)

BFS в 8 направлениях от `start_pos` в пределах `radius`. Юниты блокируют проход (являются стенами), но возвращаются как цели, если совпадают с `target_type`.

#### Array get_bfs_target_path(`board`: [[Board]], `start_pos`: Vector2i, `radius`: int, `end_pos`: Vector2i)

Кратчайший путь (BFS, 8 направлений) от `start_pos` к `end_pos`, ограниченный `radius`. Возвращает `Array[Vector2i]` без стартовой точки. Проходимы только пустые клетки.

#### Array get_all_target(`board`: [[Board]], `start_pos`: Vector2i, `radius`: int, `target_type`: int)

Простой перебор квадрата `radius` вокруг `start_pos`. Без проверки линии видимости или препятствий.