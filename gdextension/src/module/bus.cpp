#include "bus.h"

using namespace godot;

Bus::Bus() {
    listeners.clear();
    event_queue.clear();
}

void Bus::subscribe(const StringName &event_name, const Callable &callable)
{
    if (!callable.is_valid()) {
        return;
    }

    if (!listeners.has(event_name)) {
        listeners[event_name] = Vector<Callable>();
    }

    if (!listeners[event_name].has(callable)) {
        listeners[event_name].push_back(callable);
    }
}

void Bus::unsubscribe(const StringName &event_name, const Callable &callable)
{
    if (!listeners.has(event_name)) {
        return;
    }

    listeners[event_name].erase(callable);

    if (listeners[event_name].is_empty()) {
        listeners.erase(event_name);
    }
}

void Bus::queue_event(const StringName &event_name, const Array &args)
{
    event_queue.push_back({event_name, args});
}

void Bus::process_queue()
{
    if (event_queue.is_empty()) return;

    Vector<QueuedEvent> current_queue = event_queue;
    event_queue.clear();

    for (int i = 0; i < current_queue.size(); ++i) {
        bus_emit(current_queue[i].event_name, current_queue[i].args);
    }
}

void Bus::bus_emit(const StringName &event_name, const Array &args)
{
    if (!listeners.has(event_name)) {
        return;
    }

    Vector<Callable> &list = listeners[event_name];

    for (int i = list.size() - 1; i >= 0; --i) {
        if (list[i].is_valid()) {
            list[i].callv(args);
        } else {
            list.remove_at(i);
        }
    }

    if (list.is_empty()) {
        listeners.erase(event_name);
    }
}

void Bus::clear()
{
    listeners.clear();
    event_queue.clear();
}

void Bus::clear_event(const StringName &event_name)
{
    listeners.erase(event_name);
}

void Bus::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("subscribe", "event_name", "callable"), &Bus::subscribe);
    ClassDB::bind_method(D_METHOD("unsubscribe", "event_name", "callable"), &Bus::unsubscribe);
    ClassDB::bind_method(D_METHOD("emit", "event_name", "args"), &Bus::bus_emit, DEFVAL(Array()));
    ClassDB::bind_method(D_METHOD("queue_event", "event_name", "args"), &Bus::queue_event, DEFVAL(Array()));
    ClassDB::bind_method(D_METHOD("process_queue"), &Bus::process_queue);
}
