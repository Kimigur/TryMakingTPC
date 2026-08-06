# Класс: Action
# Наследует: Resource < RefCounted < Object

Базовый класс боевого действия. Наследуйте в GDScript, переопределяйте `get_valid_targets` и `_execute`. Сам `execute` проверяет очки действия и валидность цели.

## Свойства

[[Artifact]] `artifact` 
int `cost_type` 
Texture2D `icon` 
Dictionary `impacts`

## Методы

Array get_valid_targets(`source`: [[Unit]], `board`: [[Board]]) 
virtual bool \_execute(`source`: [[Unit]], `board`: [[Board]], `target`: Variant) 
virtual void attack(`attacker`: [[Unit]], `defender`: [[Unit]], `attack_bonus`: int, `func_on_hit`: Callable) 
bool execute(`source`: [[Unit]], `board`: [[Board]], `target`: Variant)

## Константы

**Типы стоимости:**
- `COST_FREE = 0`
- `COST_MAIN = 1`
- `COST_BONUS = 2`
- `COST_REACTION = 3`
- `COST_LEGENDARY = 4`

**Типы урона:**
- `NONE = 0`
- `BLUDGEONING = 1`
- `PIERCING = 2`
- `SLASHING = 3`
- `FIRE = 4`
- `COLD = 5`
- `LIGHTNING = 6`
- `ACID = 7`
- `POISON = 8`
- `FORCE = 9`
- `RADIANT = 10`
- `NECROTIC = 11`
- `PSYCHIC = 12`

## Описания свойств

[[Artifact]] `artifact`

#### get_artifact() getter / set_artifact() setter

Предмет, к которому привязано действие.

int `cost_type`

#### get_cost_type() getter / set_cost_type() setter

Какой тип действия тратится при использовании (`COST_MAIN`, `COST_BONUS`...).

Texture2D `icon`

#### get_icon() getter / set_icon() setter

Иконка кнопки в панели действий.

Dictionary `impacts`

#### get_impacts() getter / set_impacts() setter

Словарь эффектов, например `{"damage": 5}`. Используется на усмотрение скрипта действия.

## Описания методов

#### Array get_valid_targets(`source`: [[Unit]], `board`: [[Board]]) virtual

Возвращает `Array` допустимых целей (обычно `Vector2i` или ссылки на [[Unit]]). Используется UI для подсветки клеток.

#### bool \_execute(`source`: [[Unit]], `board`: [[Board]], `target`: Variant) virtual

Собственная логика действия. Вызывается только после успешных проверок в `execute`. Верните `true`, если действие выполнено.

#### void attack(`attacker`: [[Unit]], `defender`: [[Unit]], `attack_bonus`: int, `func_on_hit`: Callable)

Удобная обёртка над `Core.attack`. Бросает d20 + `attack_bonus`, проверяет КД, при попадании вызывает `func_on_hit`.

#### bool execute(`source`: [[Unit]], `board`: [[Board]], `target`: Variant)

Проверяет:
1. Есть ли у `source` неизрасходованные очки действия нужного типа.
2. Находится ли `target` в списке `get_valid_targets`.
3. Вызывает `_execute`.

При успехе уменьшает очки действия и шлёт сигнал [[event_bus#action_executed]] в шину. Возвращает `true`/`false`.