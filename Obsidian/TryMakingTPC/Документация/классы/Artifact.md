# Класс: Artifact
# Наследует: Resource < RefCounted < Object

Базовый класс предмета. Наследуйте в GDScript для создания оружия, брони, аксессуаров. Каждый артефакт может давать бонусы и предоставлять боевые действия.

## Свойства

String `artifact_name` 
String `artifact_slot_type` 
String `artifact_type` 
Texture2D `icon` 
[[Unit]] `unit`

## Методы

virtual void add_bonus() 
virtual Array get_actions() 
virtual void ready() 
[[Unit]] get_unit() 
void set_unit(`unit`: [[Unit]])

## Описания свойств

String `artifact_name`

#### get_artifact_name() getter / set_artifact_name() setter

Отображаемое имя предмета.

String `artifact_type`

#### get_artifact_type() getter / set_artifact_type() setter

Категория: `"weapon"`, `"armor"` и т.п.

String `artifact_slot_type`

#### get_artifact_slot_type() getter / set_artifact_slot_type() setter

Слот экипировки: `"main_hand"`, `"off_hand"`, `"hand"`, `"armor"`, `"helm"`, `"gloves"`, `"boots"`, `"accessory"`.

Texture2D `icon`

#### get_icon() getter / set_icon() setter

Иконка для UI.

[[Unit]] `unit`

#### get_unit() getter / set_unit() setter

Владелец предмета. Устанавливается автоматически при экипировке.

## Описания методов

#### void add_bonus() virtual

Вызывается из `[[Unit#ready]]` для каждого надетого артефакта. Здесь стоит модифицировать `bonus_*` статы владельца (силу, скорость, КД, сопротивления).

#### Array get_actions() virtual

Возвращает `Array[[Action]]` — список боевых действий, которые предоставляет этот предмет. Например, меч даёт «Удар».

#### void ready() virtual

Вызывается при старте боя для каждого экипированного артефакта. Подходит для инициализации внутреннего состояния (прочность, заряды).

#### [[Unit]] get_unit()

Возвращает текущего владельца.

#### void set_unit(`unit`: [[Unit]])

Устанавливает владельца. `null` — снятие предмета.