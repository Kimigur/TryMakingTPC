# Класс: Unit
# Наследует: Resource < RefCounted < Object

Базовый класс тактического юнита. Содержит статы, сопротивления, экипировку, скорость и очки действия. Наследуйте в GDScript и переопределяйте `ready()` и `execute()` для кастомной логики.

## Свойства

String `unit_name` 
int `type` 
Vector2i `position` 
ArrayMesh `model` 
int `hp` / int `max_hp` 
int `base_ac`
int `ac` 
int `strength` 
int `dexterity` 
int `constitution` 
int `wisdom` 
int `intelligence` 
int `charisma` 
int `max_speed` 
int `current_speed` 
int `resistance_bludgeoning` / `piercing` / `slashing` / `fire` / `cold` / `lightning` / `acid` / `poison` / `force` / `radiant` / `necrotic` / `psychic` 
int `bonus_resistance_bludgeoning` / `piercing` / `slashing` / `fire` / `cold` / `lightning` / `acid` / `poison` / `force` / `radiant` / `necrotic` / `psychic`
[[Artifact]] `main_hand_slot` / `off_hand_slot` / `armor_slot` / `helm_slot` / `gloves_slot` / `boots_slot` / `accessory_1_slot` / `accessory_2_slot` / `accessory_3_slot` / `accessory_4_slot` 
Array `inventory` 
int `free_actions_max` / `free_actions_current` 
int `main_actions_max` / `main_actions_current` 
int `bonus_actions_max` / `bonus_actions_current` 
int `reaction_actions_max` / `reaction_actions_current` 
int `legendary_actions_max` / `legendary_actions_current` 
Array `max_actions`
Array `current_actions` 
[[Board]] `board` 
[[Core]] `core`

## Методы

void ready() 
virtual void execute() 
virtual void take_damage(`amount`: int, `damage_type`: int) 
bool is_alive() 
int get_total_resistance(`damage_type`: int) 
void reset_speed() 
void reset_actions() 
void reset_bonus() 
void lock_stats() 
void subscribe_event_bus(`event_name`: StringName, `callable`: Callable) 
int roll_dice(`count`: int, `sides`: int, `mod`: int) 
bool set_main_hand_slot(`artifact`: [[Artifact]]) 
bool set_off_hand_slot(`artifact`: [[Artifact]]) 
bool set_armor_slot(`artifact`: [[Artifact]]) 
bool set_helm_slot(`artifact`: [[Artifact]]) 
bool set_gloves_slot(`artifact`: [[Artifact]]) 
bool set_boots_slot(`artifact`: [[Artifact]]) 
bool set_accessory_1_slot(`artifact`: [[Artifact]]) 
bool set_accessory_2_slot(`artifact`: [[Artifact]]) 
bool set_accessory_3_slot(`artifact`: [[Artifact]]) 
bool set_accessory_4_slot(`artifact`: [[Artifact]]) 
Array get_inventory() Array get_max_actions() 
Array get_current_actions() [[Board]] get_board() 
[[Core]] get_core() 
int get_strength_mod()
get_dexterity_mod()
get_constitution_mod()
get_wisdom_mod()
get_intelligence_mod()
get_charisma_mod() 
void add_ac(`ac`: int) 
void add_bonus_strength(`value`: int)
void add_bonus_dexterity(`value`: int)
void add_bonus_constitution(`value`: int)
void add_bonus_wisdom(`value`: int)
void add_bonus_intelligence(`value`: int)
void add_bonus_charisma(`value`: int)

## Описания свойств

String `unit_name`
#### get_unit_name() getter / set_unit_name() setter

Отображаемое имя юнита.

int `type`
#### get_type() getter

Тип юнита. `0` — кукла ДМ-а, `1` — авантюрист (ии), `2` — нейтральный (деревья, камни). Задаётся в `_init()`, после `lock_stats()` не изменяется.

Vector2i `position`
#### get_position() getter
Координаты на доске. Устанавливаются автоматически через `Board.set_unit`.

ArrayMesh `model`
#### get_model() getter / set_model() setter

3D-модель для визуализации.

int `hp` / int `max_hp`
#### get_hp/set_hp / get_max_hp/set_max_hp
Текущее и максимальное здоровье. При `hp <= 0` юнит считается мёртвым.

int `ac` / int `base_ac`

#### get_ac() getter / set_ac() setter / add_ac() modifier

Класс защиты. Суммируется из базового значения и бонусов артефактов.
#### set_base_ac()
устанавливает базовый кд, если `base_ac`!= 0 то не меняется


int `strength` ... `charisma`
#### get__() getter / set__() setter / get_*_mod() modifier

Базовые характеристики и их модификаторы: `(значение - 10) / 2`. Базовые значения блокируются после `lock_stats()`, бонусы накапливаются через `add_bonus_*`.

int `max_speed` / int `current_speed`

#### get_max_speed() getter / set_max_speed() setter / get_current_speed() getter / set_current_speed() setter

`max_speed` — базовая скорость за ход. `current_speed` — остаток в текущем ходе. `reset_speed()` восстанавливает `current_speed` с учётом бонусов.

int `resistance_*`

#### get_resistance_\*() getter

Базовое сопротивление к типам урона: `0` — уязвимость (×2), `1` — норма, `2` — сопротивление (÷2), `3` — иммунитет (`0` урона). Задаётся в `_init()`, не меняется после `lock_stats()`.

int `bonus_resistance_*`

#### get_bonus_resistance\_\*() getter / set_bonus_resistance_\*() setter

Итоговое сопротивление, используемое в бою. `reset_bonus()` сбрасывает к базовым значениям.

[[Artifact]] слоты экипировки

#### get\_\*\_slot() getter / set\_\*\_slot() setter

Слоты: `main_hand`, `off_hand`, `armor`, `helm`, `gloves`, `boots`, `accessory_1`..`4`. Сеттер проверяет `artifact_slot_type` артефакта. При снятии (`null`) отвязывает владельца.

Array `inventory`

#### get_inventory() getter

Массив из 10 слотов (включая `null` для пустых).

int `*_actions_max` / `*_actions_current`

#### get\_\*\_actions_max() getter / get\_\*\_actions_current() getter / set\_\*\_actions_current() setter

Очки действий: `free`, `main`, `bonus`, `reaction`, `legendary`. `max` — на ход, `current` — остаток. `reset_actions()` сбрасывает `current` к `max`.

Array `max_actions` / `current_actions`

#### get_max_actions() / get_current_actions()

Возвращают массив из 5 int: `[free, main, bonus, reaction, legendary]`.

[[Board]] `board`

#### get_board() getter

Доска, на которой стоит юнит. Устанавливается автоматически при добавлении в бой.

[[Core]] `core`

#### get_core() getter

Ссылка на ядро игры. Устанавливается автоматически при добавлении в бой.

## Описания методов

#### void ready() virtual

Вызывается при старте боя для каждого юнита на доске. Сбрасывает бонусы (`reset_bonus()`), затем вызывает `ready()` и `add_bonus()` у всех экипированных [[Artifact]].

#### void execute() virtual

Вызывается, когда наступает очередь этого юнита. Переопределяйте в GDScript для AI или ввода игрока.

#### void take_damage(`amount`: int, `damage_type`: int)

Наносит урон с учётом `bonus_resistance[damage_type]`:

- `0` — уязвимость: урон ×2
- `1` — норма: урон как есть
- `2` — сопротивление: урон ÷2 (округление вниз)
- `3+` — иммунитет: `0` урона

Уменьшает `hp`, эмитит [[event_bus#unit_damaged]]. Если `hp <= 0`, эмитит [[event_bus#unit_died]].

#### bool is_alive()

Возвращает `true`, если `hp > 0`.

#### int get_total_resistance(`damage_type`: int)

Возвращает текущее `bonus_resistance[damage_type]`.

#### void reset_speed()

Восстанавливает `current_speed = max_speed + bonus_max_speed`.

#### void reset_actions()

Сбрасывает все `current_action[i] = max_action[i]`.

#### void reset_bonus()

Обнуляет все `bonus_*` характеристики, `bonus_max_speed`, `ac`. Сбрасывает `bonus_resistance` к базовым `resistance`.
И в конце вызывает `add_bonus` для всех экипированных [[Artifact]]

#### void lock_stats()

Блокирует изменение базовых статов через сеттеры (`strength`, `dexterity`, `max_hp`, `max_speed`, `type` и т.д.). Вызывайте в `_init()` после настройки юнита.

#### void subscribe_event_bus(`event_name`: StringName, `callable`: Callable)

Подписывает `callable` на событие шины с привязкой к этому юниту. Если юнит мёртв (`hp <= 0`), вызов автоматически замораживается до воскрешения.

#### int roll_dice(`count`: int, `sides`: int, `mod`: int)

Обёртка над `Core.roll_dice`. Возвращает сумму бросков `count`d`sides` + `mod`.

#### bool set\_\*\_slot(`artifact`: [[Artifact]])

Экипирует артефакт в соответствующий слот. Проверяет `artifact_slot_type`. При замене старого артефакта отвязывает его (`set_unit(null)`). Возвращает `false`, если слот не подходит.

#### void add_bonus_\*(`value`: int)

Добавляет бонус к характеристике. Используется в `Artifact.add_bonus`.

#### void add_ac(`ac`: int)

Добавляет значение к текущему `ac`.