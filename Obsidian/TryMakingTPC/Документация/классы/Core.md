# Класс:   Core
# Наследует:   Node

Главный класс игры, который отвечает за всю внутреннюю кухню.

## Свойства

[[Board]] board
[[Bus]] event_bus

## Методы

void add_to_queue(`unit`: [[Unit]]) 
void attack(`attacker`: [[Unit]], `defender`: [[Unit]], `attack_bonus`: int, `func_on_hit`: Callable)
[[Unit]] get_current_unit() 
const Array get_path(`from`: Vector2i, `to`: Vector2i)
Array get_reachable_cells(`from`: Vector2i)
bool move_unit(`from`: Vector2i, `to`: Vector2i)
void next_turn()
int roll_dice(`count`: int, `sides`: int, `mod`: int)
void start_combat()

## Описания свойств


[[Board]] board
#### get_board() getter
Получение игровой доски

[[Bus]] [[event_bus]]
#### get_event_bus() getter
Получение шины ивентов


## Описания методов

#### void add_to_queue(`unit`: [[Unit]])

Добавляет `unit` в конец очереди
Автоматически привязывает к `unit` `core` и `board`, вызывает `ready()`.
Работает только во время боя

#### void attack(`attacker`: [[Unit]], `defender`: [[Unit]], `attack_bonus`: int, `func_on_hit`: Callable)

Проверка на то, пробил ли `attacker` кд `defender`. 
- При попадании вызывает `func_on_hit` и сигнал [[event_bus#attack_hit]]
- При промахе вызывает сигнал [[event_bus#attack_miss]]
- При критическом промахе вызывает сигнал [[event_bus#attack_fumble]]

#### [[Unit]] get_current_unit() const

  Возвращает [[Unit]] у которого сейчас очередь хода
  Работает только во время боя

#### bool move_unit(`from`: Vector2i, `to`: Vector2i)

  Если [[Unit]] может переместится из `from` в `to` то возвращает true, перемещает [[Unit]] по доске, вычитая потраченную скорость и отправляет  [[event_bus#unit_move]] 
Иначе возвращает false

#### void next_turn()

  Передаёт очередь хода ботам или следующему [[Unit]] игрока в очереди
  Работает только во время боя

#### int roll_dice(`count`: int, `sides`: int, `mod`: int)

  Возвращает результат броска `count` D `sides` + *mod*

#### void start_combat()

  Начинает бой, считает инициативу и формирует очередь на основании выпавших значений, и вызывает для всех `ready`. [[Unit]] типа 2 всегда в конце очереди.


