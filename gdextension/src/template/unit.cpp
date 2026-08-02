#include "unit.h"
#include "core.h"
#include "module/board.h"

using namespace godot;

Unit::Unit() {}

void Unit::ready()
{
    GDVIRTUAL_CALL(ready);
}

void Unit::execute_turn()
{
    GDVIRTUAL_CALL(execute);
}

void Unit::set_model(const Ref<ArrayMesh> &p_model)
{
    if(stats_locked){
        return;
    }
    model = p_model;
}

Ref<ArrayMesh> Unit::get_model() const
{
    return model;
}

Vector2i Unit::get_position() const
{
    return position;
}

void Unit::set_position(const Vector2i &pos)
{
    position = pos;
}

String Unit::get_unit_name(){
    return unit_name;
}

void Unit::set_unit_name(const String &p_name)
{
    if(stats_locked){
        return;
    }
    unit_name = p_name;
}

int Unit::get_max_speed(){
    return max_speed;
}

void Unit::set_max_speed(int p_speed) {
    if(stats_locked){
        return;
    }
    max_speed = p_speed;
}

int Unit::get_current_speed(){
    return current_speed;
}

void Unit::set_current_speed(int p_speed) {
    current_speed = p_speed;
}

void Unit::set_strength(int s)
{
    strength = s;
}

int Unit::get_strength() const
{
    return strength;
}

int Unit::get_strength_mod() const
{
    return (strength - 10) / 2;
}

void Unit::set_dexterity(int d)
{
    if(stats_locked){
        return;
    }
    dexterity = d;
}

int Unit::get_dexterity() const
{
    return dexterity;
}

int Unit::get_dexterity_mod() const
{
    return (dexterity - 10) / 2;
}

void Unit::set_constitution(int c)
{
    if(stats_locked){
        return;
    }
    constitution = c;
}

int Unit::get_constitution() const
{
    return constitution;
}

int Unit::get_constitution_mod() const
{
    return (constitution - 10) / 2;
}

void Unit::set_wisdom(int w)
{
    if(stats_locked){
        return;
    }
    wisdom = w;
}

int Unit::get_wisdom() const
{
    return wisdom;
}

int Unit::get_wisdom_mod() const
{
    return (wisdom - 10) / 2;
}

void Unit::set_intelligence(int i)
{
    if(stats_locked){
        return;
    }
    intelligence = i;
}

int Unit::get_intelligence() const
{
    return intelligence;
}

int Unit::get_intelligence_mod() const
{
    return (intelligence - 10) / 2;
}

void Unit::set_charisma(int c)
{
    if(stats_locked){
        return;
    }
    charisma = c;
}

int Unit::get_charisma() const
{
    return charisma;
}

int Unit::get_charisma_mod() const
{
    return (charisma - 10) / 2;
}

void Unit::set_type(int t)
{
    if(stats_locked){
        return;
    }
    type = t;
}

int Unit::get_type() const
{
    return type;
}

void Unit::lock_stats()
{
    stats_locked = true;
}

void Unit::reset_speed() {
    current_speed = max_speed;
}

void Unit::set_board(Ref<Board> *p_board)
{
    board = p_board;
}

Ref<Board> Unit::get_board()
{
    return *board;
}

void Unit::set_core(Core *p_core)
{
    core = p_core;
}

Core* Unit::get_core()
{
    return core;
}

void Unit::_bind_methods()
{
    GDVIRTUAL_BIND(ready);
    GDVIRTUAL_BIND(execute);

    ClassDB::bind_method(D_METHOD("set_model", "model"), &Unit::set_model);
    ClassDB::bind_method(D_METHOD("get_model"), &Unit::get_model);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "model", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_model", "get_model");

    ClassDB::bind_method(D_METHOD("get_position"), &Unit::get_position);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "position"), "", "get_position");

    ClassDB::bind_method(D_METHOD("get_unit_name"), &Unit::get_unit_name);
    ClassDB::bind_method(D_METHOD("set_unit_name", "name"), &Unit::set_unit_name);

    ClassDB::bind_method(D_METHOD("get_max_speed"), &Unit::get_max_speed);
    ClassDB::bind_method(D_METHOD("set_max_speed", "max_speed"), &Unit::set_max_speed);

    ClassDB::bind_method(D_METHOD("get_current_speed"), &Unit::get_current_speed);
    ClassDB::bind_method(D_METHOD("set_current_speed", "current_speed"), &Unit::set_current_speed);

    ClassDB::bind_method(D_METHOD("set_strength"), &Unit::set_strength);
    ClassDB::bind_method(D_METHOD("get_strength"), &Unit::get_strength);
    ClassDB::bind_method(D_METHOD("get_strength_mod"), &Unit::get_strength_mod);
    ClassDB::bind_method(D_METHOD("set_dexterity"), &Unit::set_dexterity);
    ClassDB::bind_method(D_METHOD("get_dexterity"), &Unit::get_dexterity);
    ClassDB::bind_method(D_METHOD("get_dexterity_mod"), &Unit::get_dexterity_mod);
    ClassDB::bind_method(D_METHOD("set_constitution"), &Unit::set_constitution);
    ClassDB::bind_method(D_METHOD("get_constitution"), &Unit::get_constitution);
    ClassDB::bind_method(D_METHOD("get_constitution_mod"), &Unit::get_constitution_mod);
    ClassDB::bind_method(D_METHOD("set_wisdom"), &Unit::set_wisdom);
    ClassDB::bind_method(D_METHOD("get_wisdom"), &Unit::get_wisdom);
    ClassDB::bind_method(D_METHOD("get_wisdom_mod"), &Unit::get_wisdom_mod);
    ClassDB::bind_method(D_METHOD("set_intelligence"), &Unit::set_intelligence);
    ClassDB::bind_method(D_METHOD("get_intelligence"), &Unit::get_intelligence);
    ClassDB::bind_method(D_METHOD("get_intelligence_mod"), &Unit::get_intelligence_mod);
    ClassDB::bind_method(D_METHOD("set_charisma"), &Unit::set_charisma);
    ClassDB::bind_method(D_METHOD("get_charisma"), &Unit::get_charisma);
    ClassDB::bind_method(D_METHOD("get_charisma_mod"), &Unit::get_charisma_mod);

    ClassDB::bind_method(D_METHOD("set_type"), &Unit::set_type);
    ClassDB::bind_method(D_METHOD("get_type"), &Unit::get_type);

    ClassDB::bind_method(D_METHOD("lock_stats"), &Unit::lock_stats);

    ClassDB::bind_method(D_METHOD("reset_speed"), &Unit::reset_speed);

    ClassDB::bind_method(D_METHOD("get_board"), &Unit::get_board);
    ClassDB::bind_method(D_METHOD("get_core"), &Unit::get_core);
}
