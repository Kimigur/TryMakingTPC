#ifndef BUS_H
#define BUS_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/templates/hash_map.hpp>

namespace godot {

class Unit;

class Bus : public RefCounted
{
    GDCLASS(Bus, RefCounted);
public:
    Bus();

    void subscribe(const StringName &event_name, const Callable &callable);
    void unit_subscribe(const StringName &event_name, const Callable &callable, Ref<Unit> owner);
    void unsubscribe(const StringName &event_name, const Callable &callable);

    void queue_event(const StringName &event_name, const Array &args = Array());
    void process_queue();

    void bus_emit(const StringName &event_name, const Array &args);

    void clear();
    void clear_event(const StringName &event_name);

protected:
    static void _bind_methods();

private:
    struct Listener {
        Callable callback;
        Ref<Unit> owner;
    };
    struct QueuedEvent {
        StringName event_name;
        Array args;
    };
    HashMap<StringName, Vector<Listener>> listeners;
    Vector<QueuedEvent> event_queue;

};

}



#endif // BUS_H
