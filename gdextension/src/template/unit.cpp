#include "unit.h"

using namespace godot;

Unit::Unit() {

}

String Unit::get_unit_name(){
    return unit_name;
}

void Unit::set_unit_name(const String &p_name)
{
    unit_name = p_name;
}

int Unit::get_max_speed(){
    return max_speed;
}

void Unit::set_max_speed(int p_speed) {
    max_speed = p_speed;
}

int Unit::get_current_speed(){
    return current_speed;
}

void Unit::set_current_speed(int p_speed) {
    current_speed = p_speed;
}

void Unit::reset_speed() {
    current_speed = max_speed;
}

void Unit::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_unit_name"), &Unit::get_unit_name);
    ClassDB::bind_method(D_METHOD("set_unit_name", "name"), &Unit::set_unit_name);

    ClassDB::bind_method(D_METHOD("get_max_speed"), &Unit::get_max_speed);
    ClassDB::bind_method(D_METHOD("set_max_speed", "max_speed"), &Unit::set_max_speed);

    ClassDB::bind_method(D_METHOD("get_current_speed"), &Unit::get_current_speed);
    ClassDB::bind_method(D_METHOD("set_current_speed", "current_speed"), &Unit::set_current_speed);

    ClassDB::bind_method(D_METHOD("reset_speed"), &Unit::reset_speed);
}
