#pragma once
#include "constants.h"
#ifndef UNIT_H
#define UNIT_H

#include "template/artifact.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/array_mesh.hpp>

namespace godot{

class Core;
class Board;

class Unit : public Resource
{
    GDCLASS(Unit, Resource);
public:
    Unit();
    ~Unit();

    void ready();
    void execute_turn();

    void set_model(const Ref<ArrayMesh> &p_model);
    Ref<ArrayMesh> get_model() const;

    Vector2i get_position() const;
    void set_position(const Vector2i &pos);

    String get_unit_name();
    void set_unit_name(const String& p_name);

    void set_max_hp(int p_hp);
    int get_max_hp() const;

    void set_hp(int p_hp);
    int get_hp() const;

    void set_resistance_bludgeoning(int p);
    int get_resistance_bludgeoning() const;
    void set_bonus_resistance_bludgeoning(int p);
    int get_bonus_resistance_bludgeoning() const;

    void set_resistance_piercing(int p);
    int get_resistance_piercing() const;
    void set_bonus_resistance_piercing(int p);
    int get_bonus_resistance_piercing() const;

    void set_resistance_slashing(int p);
    int get_resistance_slashing() const;
    void set_bonus_resistance_slashing(int p);
    int get_bonus_resistance_slashing() const;

    void set_resistance_fire(int p);
    int get_resistance_fire() const;
    void set_bonus_resistance_fire(int p);
    int get_bonus_resistance_fire() const;

    void set_resistance_cold(int p);
    int get_resistance_cold() const;
    void set_bonus_resistance_cold(int p);
    int get_bonus_resistance_cold() const;

    void set_resistance_lightning(int p);
    int get_resistance_lightning() const;
    void set_bonus_resistance_lightning(int p);
    int get_bonus_resistance_lightning() const;

    void set_resistance_acid(int p);
    int get_resistance_acid() const;
    void set_bonus_resistance_acid(int p);
    int get_bonus_resistance_acid() const;

    void set_resistance_poison(int p);
    int get_resistance_poison() const;
    void set_bonus_resistance_poison(int p);
    int get_bonus_resistance_poison() const;

    void set_resistance_force(int p);
    int get_resistance_force() const;
    void set_bonus_resistance_force(int p);
    int get_bonus_resistance_force() const;

    void set_resistance_radiant(int p);
    int get_resistance_radiant() const;
    void set_bonus_resistance_radiant(int p);
    int get_bonus_resistance_radiant() const;

    void set_resistance_necrotic(int p);
    int get_resistance_necrotic() const;
    void set_bonus_resistance_necrotic(int p);
    int get_bonus_resistance_necrotic() const;

    void set_resistance_psychic(int p);
    int get_resistance_psychic() const;
    void set_bonus_resistance_psychic(int p);
    int get_bonus_resistance_psychic() const;

    void set_base_ac(int p_ac);
    int get_base_ac() const;

    void set_ac(int p_ac);
    void add_ac(int p_ac);
    int get_ac() const;

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

    void set_free_actions_max(int p);
    int get_free_actions_max();

    void set_free_actions_current(int p);
    int get_free_actions_current();

    void set_main_actions_max(int p);
    int get_main_actions_max();

    void set_main_actions_current(int p);
    int get_main_actions_current();

    void set_bonus_actions_max(int p);
    int get_bonus_actions_max();

    void set_bonus_actions_current(int p);
    int get_bonus_actions_current();

    void set_reaction_actions_max(int p);
    int get_reaction_actions_max();

    void set_reaction_actions_current(int p);
    int get_reaction_actions_current();

    void set_legendary_actions_max(int p);
    int get_legendary_actions_max();

    void set_legendary_actions_current(int p);
    int get_legendary_actions_current();

    Array get_max_actions();
    Array get_current_actions();

    Array get_inventory();

    void lock_stats();

    void reset_speed();
    void reset_actions();
    void reset_bonus();

    void set_board(Ref<Board> &p_board);
    Ref<Board> get_board();

    void set_core(Core *p_core);
    Core *get_core();

    void take_damage(int amount, int damage_type);
    bool is_alive();
    int get_total_resistance(int damage_type);

    int roll_dice(int dice_count, int dice_sides, int modifier = 0);
    void subscribe_event_bus(const StringName &event_name, const Callable &callable);
    void unsubscribe_event_bus(const StringName &event_name, const Callable &callable);

protected:
    static void _bind_methods();

    GDVIRTUAL0(ready);
    GDVIRTUAL0(execute);

private:
    Core *core = nullptr;;
    Ref<Board> board;
    Ref<ArrayMesh> model;

    Vector2i position = Vector2i(-1, -1);

    String unit_name = "";

    int max_hp = 0;
    int hp = 0;

    int resistance[13] = {1,1,1,1,1,1,1,1,1,1,1,1,1};
    int bonus_resistance[13] = {1,1,1,1,1,1,1,1,1,1,1,1,1};

    int base_ac = 0;
    int ac = 0;

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

    Ref<Artifact> inventory[EquipSlot::SLOT_COUNT];
    int max_action[5] = {1, 1, 1, 1, 0};
    int current_action[5] = {1, 1, 1, 1, 0};
};

}

#endif // UNIT_H
