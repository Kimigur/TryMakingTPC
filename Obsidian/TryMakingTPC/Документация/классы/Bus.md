# Класс: Bus
# Наследует: RefCounted < Object

Шина событий. Все игровые модули подписываются на сигналы здесь, а не напрямую друг на друга. Поддерживает обычные и «замораживаемые» подписки.

## Методы

void emit(`event_name`: StringName, `args`: Array = []) 
void process_queue() 
void queue_event(`event_name`: StringName, `args`: Array = []) 
void subscribe(`event_name`: StringName, `callable`: Callable) 
void unit_subscribe(`event_name`: StringName, `callable`: Callable, `owner`: [[Unit]]) 
void unsubscribe(`event_name`: StringName, `callable`: Callable)

## Описания методов

#### void emit(`event_name`: StringName, `args`: Array = [])

Немедленно вызывает все подписки на `event_name`, передавая `args`. Если подписка создана через `unit_subscribe`, а `owner` мёртв (`hp <= 0`), вызов пропускается.

#### void process_queue()

Обрабатывает очередь, накопленную через `queue_event`. Полезно, если нужно отложить сигналы до конца текущего кадра.

#### void queue_event(`event_name`: StringName, `args`: Array = [])

Добавляет событие в очередь. Не вызывает подписчиков сразу — только при следующем `process_queue()`.

#### void subscribe(`event_name`: StringName, `callable`: Callable)

Обычная подписка. `callable` будет вызван при каждом `emit` независимо от состояния юнитов.

#### void unit_subscribe(`event_name`: StringName, `callable`: Callable, `owner`: [[Unit]])

Подписка с привязкой к юниту. Если hp `owner` падает до `0`, `callable` автоматически «замораживается» (не вызывается). При воскрешении (`hp > 0`) размораживается без дополнительных действий.

#### void unsubscribe(`event_name`: StringName, `callable`: Callable)

Удаляет `callable` из подписчиков `event_name`.