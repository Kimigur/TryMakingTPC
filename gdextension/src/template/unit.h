#ifndef UNIT_H
#define UNIT_H

#include <godot_cpp/classes/resource.hpp>

namespace godot{

class Unit : public Resource
{
    GDCLASS(Unit, Resource);
public:
    Unit();

    String get_unit_name();
    void set_unit_name(const String& p_name);

    int get_max_speed();
    void set_max_speed(int p_speed);

    int get_current_speed();
    void set_current_speed(int p_speed);

    void reset_speed();

protected:
    static void _bind_methods();

private:
    String unit_name = "";

    int max_speed = 5;
    int current_speed = 5;

};

}

#endif // UNIT_H
