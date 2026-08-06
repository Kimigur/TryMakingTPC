# Класс: Cell
# Наследует: Resource < RefCounted < Object

Базовая клетка доски. Сейчас используется как заглушка/маркер, но может расширяться для ландшафта (вода, ловушки).

## Свойства

String `cell_name`

## Методы

String get_cell_name() 
void set_cell_name(`name`: String)

## Описания свойств

String `cell_name`

#### get_cell_name() getter / set_cell_name() setter

Имя клетки. По умолчанию `"EmptyCell"`.

## Описания методов

#### String get_cell_name()

Возвращает имя клетки.

#### void set_cell_name(`name`: String)

Устанавливает имя клетки.