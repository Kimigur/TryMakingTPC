#ifndef UNIT_H
#define UNIT_H

#include "template/artifact.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/array_mesh.hpp>

namespace godot{

enum EquipSlot {
    SLOT_MAIN_HAND = 0,
    SLOT_OFF_HAND,
    SLOT_ARMOR,
    SLOT_HELM,
    SLOT_GLOVES,
    SLOT_BOOTS,
    SLOT_ACC_1,
    SLOT_ACC_2,
    SLOT_ACC_3,
    SLOT_ACC_4,
    SLOT_COUNT
};

class Board;
class Core;

class Unit : public Resource
{
    GDCLASS(Unit, Resource);
public:
    Unit();

    void ready();
    void execute_turn();

    void set_model(const Ref<ArrayMesh> &p_model);
    Ref<ArrayMesh> get_model() const;

    Vector2i get_position() const;
    void set_position(const Vector2i &pos);

    String get_unit_name();
    void set_unit_name(const String& p_name);

    int get_max_speed();
    void set_max_speed(int p_speed);
    void add_bonus_max_speed(int p_speed);

    int get_current_speed();
    void set_current_speed(int p_speed);

    void set_strength(int s);
    void add_bonus_strength(int s);
    int get_strength() const;
    int get_strength_mod() const;
    void set_dexterity(int d);
    void add_bonus_dexterity(int d);
    int get_dexterity() const;
    int get_dexterity_mod() const;
    void set_constitution(int c);
    void add_bonus_constitution(int c);
    int get_constitution() const;
    int get_constitution_mod() const;
    void set_wisdom(int w);
    void add_bonus_wisdom(int w);
    int get_wisdom() const;
    int get_wisdom_mod() const;
    void set_intelligence(int i);
    void add_bonus_intelligence(int i);
    int get_intelligence() const;
    int get_intelligence_mod() const;
    void set_charisma(int c);
    void add_bonus_charisma(int c);
    int get_charisma() const;
    int get_charisma_mod() const;

    void set_type(int t);
    int get_type() const;

    bool set_main_hand_slot(Artifact *p_artifact);
    Artifact* get_main_hand_slot();

    bool set_off_hand_slot(Artifact *p_artifact);
    Artifact* get_off_hand_slot();

    bool set_armor_slot(Artifact *p_artifact);
    Artifact* get_armor_slot();

    bool set_helm_slot(Artifact *p_artifact);
    Artifact* get_helm_slot();

    bool set_gloves_slot(Artifact *p_artifact);
    Artifact* get_gloves_slot();

    bool set_boots_slot(Artifact *p_artifact);
    Artifact* get_boots_slot();

    bool set_accessory_1_slot(Artifact *p_artifact);
    Artifact* get_accessory_1_slot();

    bool set_accessory_2_slot(Artifact *p_artifact);
    Artifact* get_accessory_2_slot();

    bool set_accessory_3_slot(Artifact *p_artifact);
    Artifact* get_accessory_3_slot();

    bool set_accessory_4_slot(Artifact *p_artifact);
    Artifact* get_accessory_4_slot();

    Array get_inventory();

    void lock_stats();

    void reset_speed();
    void reset_bonus();

    void set_board(Ref<Board> *p_board);
    Ref<Board> get_board();

    void set_core(Core *p_core);
    Core *get_core();

protected:
    static void _bind_methods();

    GDVIRTUAL0(ready);
    GDVIRTUAL0(execute);

private:
    Core *core;
    Ref<Board>* board;
    Ref<ArrayMesh> model;

    Vector2i position = Vector2i(-1, -1);

    String unit_name = "";

    int max_speed = 0;
    int current_speed = 0;

    int strength = 0;      // Сила
    int dexterity = 0;     // Ловкость
    int constitution = 0;  // Телосложение
    int wisdom = 0;        // Мудрость
    int intelligence = 0;  // Интелект
    int charisma = 0;      // Харизма

    int bonus_max_speed = 0;

    int bonus_strength = 0;      // Сила
    int bonus_dexterity = 0;     // Ловкость
    int bonus_constitution = 0;  // Телосложение
    int bonus_wisdom = 0;        // Мудрость
    int bonus_intelligence = 0;  // Интелект
    int bonus_charisma = 0;      // Харизма

    bool stats_locked = false;

    int type = 2;         // Тип 0-Кукла дм-а, 1-Авантюрист, 2-нейтральный

    Ref<Artifact> inventory[SLOT_COUNT];
};

}

#endif // UNIT_H
