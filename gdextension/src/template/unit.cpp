#include "unit.h"
#include "core.h"
#include "module/board.h"
#include "constants.h"

using namespace godot;

Unit::Unit() {}

Unit::~Unit()
{

}

void Unit::ready()
{
    reset_bonus();
    GDVIRTUAL_CALL(ready);
    for (int i = 0; i < SLOT_COUNT; ++i) {
        if(inventory[i]!=nullptr){
            inventory[i]->ready();
        }
    }
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

void Unit::set_max_hp(int p_hp)
{
    if(stats_locked){
        return;
    }
    max_hp = p_hp;
}

int Unit::get_max_hp() const
{
    return max_hp;
}

void Unit::set_hp(int p_hp)
{
    hp = p_hp;
}

int Unit::get_hp() const
{
    return hp;
}

void Unit::set_resistance_bludgeoning(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[BLUDGEONING] = p;
}
int Unit::get_resistance_bludgeoning() const
{
    return resistance[BLUDGEONING];
}

void Unit::set_bonus_resistance_bludgeoning(int p)
{
    bonus_resistance[BLUDGEONING] = p;
}

int Unit::get_bonus_resistance_bludgeoning() const
{
    return bonus_resistance[BLUDGEONING];
}

void Unit::set_resistance_piercing(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[PIERCING] = p;
}

int Unit::get_resistance_piercing() const
{
    return resistance[PIERCING];
}

void Unit::set_bonus_resistance_piercing(int p)
{
    bonus_resistance[PIERCING] = p;
}

int Unit::get_bonus_resistance_piercing() const
{
    return bonus_resistance[PIERCING];
}

void Unit::set_resistance_slashing(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[SLASHING] = p;
}

int Unit::get_resistance_slashing() const
{
    return resistance[SLASHING];
}

void Unit::set_bonus_resistance_slashing(int p)
{
    bonus_resistance[SLASHING] = p;
}

int Unit::get_bonus_resistance_slashing() const
{
    return bonus_resistance[SLASHING];
}

void Unit::set_resistance_fire(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[FIRE] = p;
}
int Unit::get_resistance_fire() const
{
    return resistance[FIRE];
}

void Unit::set_bonus_resistance_fire(int p)
{
    bonus_resistance[FIRE] = p;
}

int Unit::get_bonus_resistance_fire() const
{
    return bonus_resistance[FIRE];
}

void Unit::set_resistance_cold(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[COLD] = p;
}

int Unit::get_resistance_cold() const
{
    return resistance[COLD];
}

void Unit::set_bonus_resistance_cold(int p)
{
    bonus_resistance[COLD] = p;
}

int Unit::get_bonus_resistance_cold() const
{
    return bonus_resistance[COLD];
}

void Unit::set_resistance_lightning(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[LIGHTHING] = p;
}

int Unit::get_resistance_lightning() const
{
    return resistance[LIGHTHING];
}

void Unit::set_bonus_resistance_lightning(int p)
{
    bonus_resistance[LIGHTHING] = p;
}

int Unit::get_bonus_resistance_lightning() const
{
    return bonus_resistance[LIGHTHING];
}

void Unit::set_resistance_acid(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[ACID] = p;
}

int Unit::get_resistance_acid() const
{
    return resistance[ACID];
}
void Unit::set_bonus_resistance_acid(int p)
{
    bonus_resistance[ACID] = p;
}
int Unit::get_bonus_resistance_acid() const
{
    return bonus_resistance[ACID];
}

void Unit::set_resistance_poison(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[POISON] = p;
}
int Unit::get_resistance_poison() const
{
    return resistance[POISON];
}
void Unit::set_bonus_resistance_poison(int p)
{
    bonus_resistance[POISON] = p;
}

int Unit::get_bonus_resistance_poison() const
{
    return bonus_resistance[POISON];
}

void Unit::set_resistance_force(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[FORCE] = p;
}

int Unit::get_resistance_force() const
{
    return resistance[FORCE];
}

void Unit::set_bonus_resistance_force(int p)
{
    bonus_resistance[FORCE] = p;
}

int Unit::get_bonus_resistance_force() const
{
    return bonus_resistance[FORCE];
}

void Unit::set_resistance_radiant(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[RADIANT] = p;
}

int Unit::get_resistance_radiant() const
{
    return resistance[RADIANT];
}
void Unit::set_bonus_resistance_radiant(int p)
{
    bonus_resistance[RADIANT] = p;
}

int Unit::get_bonus_resistance_radiant() const
{
    return bonus_resistance[RADIANT];
}

void Unit::set_resistance_necrotic(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[NECROTIC] = p;
}

int Unit::get_resistance_necrotic() const
{
    return resistance[NECROTIC];
}

void Unit::set_bonus_resistance_necrotic(int p)
{
    bonus_resistance[NECROTIC] = p;
}

int Unit::get_bonus_resistance_necrotic() const
{
    return bonus_resistance[NECROTIC];
}

void Unit::set_resistance_psychic(int p)
{
    if (stats_locked) {
        return;
    }
    resistance[PSYCHIC] = p;
}

int Unit::get_resistance_psychic() const
{
    return resistance[PSYCHIC];
}

void Unit::set_bonus_resistance_psychic(int p)
{
    bonus_resistance[PSYCHIC] = p;
}

int Unit::get_bonus_resistance_psychic() const
{
    return bonus_resistance[PSYCHIC];
}

void Unit::set_base_ac(int p_ac)
{
    if(base_ac == 0){
        base_ac = p_ac;
    }
}

int Unit::get_base_ac() const
{
    return base_ac;
}

void Unit::set_ac(int p_ac)
{
    ac = p_ac;
}

void Unit::add_ac(int p_ac)
{
    ac+=p_ac;
}

int Unit::get_ac() const
{
    return base_ac + ac;
}

int Unit::get_max_speed(){
    return max_speed+bonus_max_speed;
}

void Unit::set_max_speed(int p_speed) {
    if(stats_locked){
        return;
    }
    max_speed = p_speed;
}

void Unit::add_bonus_max_speed(int p_speed)
{
    bonus_max_speed = p_speed;
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

void Unit::add_bonus_strength(int s)
{
    bonus_strength+=s;
}

int Unit::get_strength() const
{
    return strength+bonus_strength;
}

int Unit::get_strength_mod() const
{
    return (strength+bonus_strength - 10) / 2;
}

void Unit::set_dexterity(int d)
{
    if(stats_locked){
        return;
    }
    dexterity = d;
}

void Unit::add_bonus_dexterity(int d)
{
    bonus_dexterity+=d;
}

int Unit::get_dexterity() const
{
    return dexterity+bonus_dexterity;
}

int Unit::get_dexterity_mod() const
{
    return (dexterity+bonus_dexterity - 10) / 2;
}

void Unit::set_constitution(int c)
{
    if(stats_locked){
        return;
    }
    constitution = c;
}

void Unit::add_bonus_constitution(int c)
{
    bonus_constitution+= c;
}

int Unit::get_constitution() const
{
    return constitution+bonus_constitution;
}

int Unit::get_constitution_mod() const
{
    return (constitution+bonus_constitution - 10) / 2;
}

void Unit::set_wisdom(int w)
{
    if(stats_locked){
        return;
    }
    wisdom = w;
}

void Unit::add_bonus_wisdom(int w)
{
    bonus_wisdom+=w;
}

int Unit::get_wisdom() const
{
    return wisdom+bonus_wisdom;
}

int Unit::get_wisdom_mod() const
{
    return (wisdom+bonus_wisdom - 10) / 2;
}

void Unit::set_intelligence(int i)
{
    if(stats_locked){
        return;
    }
    intelligence = i;
}

void Unit::add_bonus_intelligence(int i)
{
    bonus_intelligence+=i;
}

int Unit::get_intelligence() const
{
    return intelligence+bonus_intelligence;
}

int Unit::get_intelligence_mod() const
{
    return (intelligence+bonus_intelligence - 10) / 2;
}

void Unit::set_charisma(int c)
{
    if(stats_locked){
        return;
    }
    charisma = c;
}

void Unit::add_bonus_charisma(int c)
{
    bonus_charisma+=c;
}

int Unit::get_charisma() const
{
    return charisma+bonus_charisma;
}

int Unit::get_charisma_mod() const
{
    return (charisma+bonus_charisma - 10) / 2;
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

bool Unit::set_main_hand_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_MAIN_HAND].is_valid()) {
        inventory[SLOT_MAIN_HAND]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_MAIN_HAND] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "main_hand" || p_artifact->get_artifact_slot_type() == "hand"){
        inventory[SLOT_MAIN_HAND] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_main_hand_slot()
{
    return inventory[SLOT_MAIN_HAND].ptr();
}

bool Unit::set_off_hand_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_OFF_HAND].is_valid()) {
        inventory[SLOT_OFF_HAND]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_OFF_HAND] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "off_hand" || p_artifact->get_artifact_slot_type() == "hand"){
        inventory[SLOT_OFF_HAND] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_off_hand_slot()
{
    return inventory[SLOT_OFF_HAND].ptr();
}

bool Unit::set_armor_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_ARMOR].is_valid()) {
        inventory[SLOT_ARMOR]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_ARMOR] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "armor"){
        inventory[SLOT_ARMOR] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_armor_slot()
{
    return inventory[SLOT_ARMOR].ptr();
}

bool Unit::set_helm_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_HELM].is_valid()) {
        inventory[SLOT_HELM]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_HELM] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "helm"){
        inventory[SLOT_HELM] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_helm_slot()
{
    return inventory[SLOT_HELM].ptr();
}

bool Unit::set_gloves_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_GLOVES].is_valid()) {
        inventory[SLOT_GLOVES]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_GLOVES] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "gloves"){
        inventory[SLOT_GLOVES] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_gloves_slot()
{
    return inventory[SLOT_GLOVES].ptr();
}

bool Unit::set_boots_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_BOOTS].is_valid()) {
        inventory[SLOT_BOOTS]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_BOOTS] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "boots"){
        inventory[SLOT_BOOTS] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_boots_slot()
{
    return inventory[SLOT_BOOTS].ptr();
}

bool Unit::set_accessory_1_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_ACC_1].is_valid()) {
        inventory[SLOT_ACC_1]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_ACC_1] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "accessory"){
        inventory[SLOT_ACC_1] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_accessory_1_slot()
{
    return inventory[SLOT_ACC_1].ptr();
}

bool Unit::set_accessory_2_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_ACC_2].is_valid()) {
        inventory[SLOT_ACC_2]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_ACC_2] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "accessory"){
        inventory[SLOT_ACC_2] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_accessory_2_slot()
{
    return inventory[SLOT_ACC_2].ptr();
}

bool Unit::set_accessory_3_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_ACC_3].is_valid()) {
        inventory[SLOT_ACC_3]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_ACC_3] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "accessory"){
        inventory[SLOT_ACC_3] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_accessory_3_slot()
{
    return inventory[SLOT_ACC_3].ptr();
}

bool Unit::set_accessory_4_slot(Artifact *p_artifact)
{
    if (inventory[SLOT_ACC_4].is_valid()) {
        inventory[SLOT_ACC_4]->set_unit(nullptr);
    }

    if (p_artifact == nullptr) {
        inventory[SLOT_ACC_4] = Ref<Artifact>();
        return true;
    }
    if(p_artifact->get_artifact_slot_type() == "accessory"){
        inventory[SLOT_ACC_4] = Ref<Artifact>(p_artifact);
        p_artifact->set_unit(this);
        return true;
    }
    return false;
}

Artifact *Unit::get_accessory_4_slot()
{
    return inventory[SLOT_ACC_4].ptr();
}

void Unit::set_free_actions_max(int p)
{
    if(stats_locked){
        return;
    }
    max_action[FREE] = p;
}

int Unit::get_free_actions_max()
{
    return max_action[FREE];
}

void Unit::set_free_actions_current(int p)
{
    current_action[FREE] = p;
}

int Unit::get_free_actions_current()
{
    return current_action[FREE];
}

void Unit::set_main_actions_max(int p)
{
    if(stats_locked){
        return;
    }
    max_action[MAIN] = p;
}

int Unit::get_main_actions_max()
{
    return max_action[MAIN];
}

void Unit::set_main_actions_current(int p)
{
    current_action[MAIN] = p;
}

int Unit::get_main_actions_current()
{
    return current_action[MAIN];
}

void Unit::set_bonus_actions_max(int p)
{
    if(stats_locked){
        return;
    }
    max_action[BONUS] = p;
}

int Unit::get_bonus_actions_max()
{
    return max_action[BONUS];
}

void Unit::set_bonus_actions_current(int p)
{
    current_action[BONUS] = p;
}

int Unit::get_bonus_actions_current()
{
    return current_action[BONUS];
}

void Unit::set_reaction_actions_max(int p)
{
    if(stats_locked){
        return;
    }
    max_action[REACTION] = p;
}

int Unit::get_reaction_actions_max()
{
    return max_action[REACTION];
}

void Unit::set_reaction_actions_current(int p)
{
    current_action[REACTION] = p;
}

int Unit::get_reaction_actions_current()
{
    return current_action[REACTION];
}

void Unit::set_legendary_actions_max(int p)
{
    if(stats_locked){
        return;
    }
    max_action[LEGENDARY] = p;
}

int Unit::get_legendary_actions_max()
{
    return max_action[LEGENDARY];
}

void Unit::set_legendary_actions_current(int p)
{
    current_action[LEGENDARY] = p;
}

int Unit::get_legendary_actions_current()
{
    return current_action[LEGENDARY];
}

Array Unit::get_max_actions()
{
    Array ret;
    for (int i = 0; i < 5; ++i) {
        ret.push_back(max_action[i]);
    }
    return ret;
}

Array Unit::get_current_actions()
{
    Array ret;
    for (int i = 0; i < 5; ++i) {
        ret.push_back(current_action[i]);
    }
    return ret;
}



Array Unit::get_inventory()
{
    Array ret;
    for (int i = 0; i < SLOT_COUNT; ++i) {
        ret.push_back(inventory[i].ptr());
    }
    return ret;
}

void Unit::lock_stats()
{
    stats_locked = true;
}

void Unit::reset_speed() {
    current_speed = max_speed+bonus_max_speed;
}

void Unit::reset_actions()
{
    for (int i = 0; i < 5; ++i) {
        current_action[i] = max_action[i];
    }
}

void Unit::reset_bonus()
{
    bonus_max_speed = 0;

    bonus_strength = 0;      // Сила
    bonus_dexterity = 0;     // Ловкость
    bonus_constitution = 0;  // Телосложение
    bonus_wisdom = 0;        // Мудрость
    bonus_intelligence = 0;  // Интелект
    bonus_charisma = 0;      // Харизма
    ac = 0;
    for (int i = 0; i < 13; ++i) {
        bonus_resistance[i] = resistance[i];
    }
    for (int i = 0; i < SLOT_COUNT; ++i) {
        if(inventory[i]!=nullptr){
            inventory[i]->add_bonus();
        }
    }
}

void Unit::set_board(Ref<Board> &p_board)
{
    board = p_board;
}

Ref<Board> Unit::get_board()
{
    return board;
}

void Unit::set_core(Core *p_core)
{
    core = p_core;
}

Core* Unit::get_core()
{
    return core;
}

void Unit::take_damage(int amount, int damage_type)
{
    int resistance = bonus_resistance[damage_type];

    int final_damage = amount;

    if (resistance == 0) {
        final_damage = amount * 2;        // уязвимость
    } else if (resistance == 1) {
        final_damage = amount;             // норма
    } else if (resistance == 2) {
        final_damage = amount / 2;         // сопротивление (округление вниз)
    } else {
        final_damage = 0;                  // иммунитет
    }

    hp -= final_damage;

    core->get_event_bus()->bus_emit("unit_damaged", Array::make(this, final_damage, damage_type));
    if (!is_alive()) {
        core->get_event_bus()->bus_emit("unit_died", Array::make(this));
    }
}

bool Unit::is_alive()
{
    return hp>0;
}

int Unit::get_total_resistance(int damage_type)
{
    return bonus_resistance[damage_type];
}

int Unit::roll_dice(int dice_count, int dice_sides, int modifier)
{
    return this->get_core()->roll_dice(dice_count, dice_sides, modifier);
}

void Unit::subscribe_event_bus(const StringName &event_name, const Callable &callable)
{
    this->get_core()->get_event_bus()->unit_subscribe(event_name, callable, this);
}

void Unit::unsubscribe_event_bus(const StringName &event_name, const Callable &callable)
{
    core->get_event_bus()->unsubscribe(event_name, callable);
}

Array Unit::get_actions()
{
    Array ret;
    GDVIRTUAL_CALL(get_actions, ret);
    return ret;
}

void Unit::_bind_methods()
{
    GDVIRTUAL_BIND(ready);
    GDVIRTUAL_BIND(execute);
    GDVIRTUAL_BIND(get_actions);

    String damage_hint = "None,Bludgeoning,Piercing,Slashing,Fire,Cold,Lightning,Acid,Poison,Force,Radiant,Necrotic,Psychic";

    ClassDB::bind_method(D_METHOD("set_model", "model"), &Unit::set_model);
    ClassDB::bind_method(D_METHOD("get_model"), &Unit::get_model);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "model", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_model", "get_model");

    ClassDB::bind_method(D_METHOD("get_position"), &Unit::get_position);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "position"), "", "get_position");

    ClassDB::bind_method(D_METHOD("get_unit_name"), &Unit::get_unit_name);
    ClassDB::bind_method(D_METHOD("set_unit_name", "name"), &Unit::set_unit_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "unit_name"), "", "get_unit_name");

    ClassDB::bind_method(D_METHOD("get_max_hp"), &Unit::get_max_hp);
    ClassDB::bind_method(D_METHOD("set_max_hp", "max_hp"), &Unit::set_max_hp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_speed"), "", "get_max_speed");

    ClassDB::bind_method(D_METHOD("get_hp"), &Unit::get_hp);
    ClassDB::bind_method(D_METHOD("set_hp", "hp"), &Unit::set_hp);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "hp"), "set_hp", "get_hp");

    ClassDB::bind_method(D_METHOD("set_resistance_bludgeoning", "value"), &Unit::set_resistance_bludgeoning);
    ClassDB::bind_method(D_METHOD("get_resistance_bludgeoning"), &Unit::get_resistance_bludgeoning);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_bludgeoning", "value"), &Unit::set_bonus_resistance_bludgeoning);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_bludgeoning"), &Unit::get_bonus_resistance_bludgeoning);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_bludgeoning"), "", "get_resistance_bludgeoning");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_bludgeoning"), "set_bonus_resistance_bludgeoning", "get_bonus_resistance_bludgeoning");

    ClassDB::bind_method(D_METHOD("set_resistance_piercing", "value"), &Unit::set_resistance_piercing);
    ClassDB::bind_method(D_METHOD("get_resistance_piercing"), &Unit::get_resistance_piercing);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_piercing", "value"), &Unit::set_bonus_resistance_piercing);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_piercing"), &Unit::get_bonus_resistance_piercing);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_piercing"), "", "get_resistance_piercing");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_piercing"), "set_bonus_resistance_piercing", "get_bonus_resistance_piercing");

    ClassDB::bind_method(D_METHOD("set_resistance_slashing", "value"), &Unit::set_resistance_slashing);
    ClassDB::bind_method(D_METHOD("get_resistance_slashing"), &Unit::get_resistance_slashing);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_slashing", "value"), &Unit::set_bonus_resistance_slashing);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_slashing"), &Unit::get_bonus_resistance_slashing);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_slashing"), "", "get_resistance_slashing");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_slashing"), "set_bonus_resistance_slashing", "get_bonus_resistance_slashing");

    ClassDB::bind_method(D_METHOD("set_resistance_fire", "value"), &Unit::set_resistance_fire);
    ClassDB::bind_method(D_METHOD("get_resistance_fire"), &Unit::get_resistance_fire);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_fire", "value"), &Unit::set_bonus_resistance_fire);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_fire"), &Unit::get_bonus_resistance_fire);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_fire"), "", "get_resistance_fire");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_fire"), "set_bonus_resistance_fire", "get_bonus_resistance_fire");

    ClassDB::bind_method(D_METHOD("set_resistance_cold", "value"), &Unit::set_resistance_cold);
    ClassDB::bind_method(D_METHOD("get_resistance_cold"), &Unit::get_resistance_cold);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_cold", "value"), &Unit::set_bonus_resistance_cold);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_cold"), &Unit::get_bonus_resistance_cold);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_cold"), "", "get_resistance_cold");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_cold"), "set_bonus_resistance_cold", "get_bonus_resistance_cold");

    ClassDB::bind_method(D_METHOD("set_resistance_lightning", "value"), &Unit::set_resistance_lightning);
    ClassDB::bind_method(D_METHOD("get_resistance_lightning"), &Unit::get_resistance_lightning);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_lightning", "value"), &Unit::set_bonus_resistance_lightning);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_lightning"), &Unit::get_bonus_resistance_lightning);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_lightning"), "", "get_resistance_lightning");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_lightning"), "set_bonus_resistance_lightning", "get_bonus_resistance_lightning");

    ClassDB::bind_method(D_METHOD("set_resistance_acid", "value"), &Unit::set_resistance_acid);
    ClassDB::bind_method(D_METHOD("get_resistance_acid"), &Unit::get_resistance_acid);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_acid", "value"), &Unit::set_bonus_resistance_acid);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_acid"), &Unit::get_bonus_resistance_acid);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_acid"), "", "get_resistance_acid");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_acid"), "set_bonus_resistance_acid", "get_bonus_resistance_acid");

    ClassDB::bind_method(D_METHOD("set_resistance_poison", "value"), &Unit::set_resistance_poison);
    ClassDB::bind_method(D_METHOD("get_resistance_poison"), &Unit::get_resistance_poison);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_poison", "value"), &Unit::set_bonus_resistance_poison);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_poison"), &Unit::get_bonus_resistance_poison);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_poison"), "", "get_resistance_poison");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_poison"), "set_bonus_resistance_poison", "get_bonus_resistance_poison");

    ClassDB::bind_method(D_METHOD("set_resistance_force", "value"), &Unit::set_resistance_force);
    ClassDB::bind_method(D_METHOD("get_resistance_force"), &Unit::get_resistance_force);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_force", "value"), &Unit::set_bonus_resistance_force);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_force"), &Unit::get_bonus_resistance_force);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_force"), "", "get_resistance_force");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_force"), "set_bonus_resistance_force", "get_bonus_resistance_force");

    ClassDB::bind_method(D_METHOD("set_resistance_radiant", "value"), &Unit::set_resistance_radiant);
    ClassDB::bind_method(D_METHOD("get_resistance_radiant"), &Unit::get_resistance_radiant);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_radiant", "value"), &Unit::set_bonus_resistance_radiant);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_radiant"), &Unit::get_bonus_resistance_radiant);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_radiant"), "", "get_resistance_radiant");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_radiant"), "set_bonus_resistance_radiant", "get_bonus_resistance_radiant");

    ClassDB::bind_method(D_METHOD("set_resistance_necrotic", "value"), &Unit::set_resistance_necrotic);
    ClassDB::bind_method(D_METHOD("get_resistance_necrotic"), &Unit::get_resistance_necrotic);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_necrotic", "value"), &Unit::set_bonus_resistance_necrotic);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_necrotic"), &Unit::get_bonus_resistance_necrotic);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_necrotic"), "", "get_resistance_necrotic");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_necrotic"), "set_bonus_resistance_necrotic", "get_bonus_resistance_necrotic");

    ClassDB::bind_method(D_METHOD("set_resistance_psychic", "value"), &Unit::set_resistance_psychic);
    ClassDB::bind_method(D_METHOD("get_resistance_psychic"), &Unit::get_resistance_psychic);
    ClassDB::bind_method(D_METHOD("set_bonus_resistance_psychic", "value"), &Unit::set_bonus_resistance_psychic);
    ClassDB::bind_method(D_METHOD("get_bonus_resistance_psychic"), &Unit::get_bonus_resistance_psychic);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "resistance_psychic"), "", "get_resistance_psychic");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_resistance_psychic"), "set_bonus_resistance_psychic", "get_bonus_resistance_psychic");

    ClassDB::bind_method(D_METHOD("get_ac"), &Unit::get_ac);
    ClassDB::bind_method(D_METHOD("set_ac", "ac"), &Unit::set_ac);
    ClassDB::bind_method(D_METHOD("add_ac", "ac"), &Unit::add_ac);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "ac"), "set_ac", "get_ac");

    ClassDB::bind_method(D_METHOD("get_base_ac"), &Unit::get_base_ac);
    ClassDB::bind_method(D_METHOD("set_base_ac", "ac"), &Unit::set_base_ac);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "base_ac"), "get_base_ac", "set_base_ac");

    ClassDB::bind_method(D_METHOD("get_max_speed"), &Unit::get_max_speed);
    ClassDB::bind_method(D_METHOD("set_max_speed", "max_speed"), &Unit::set_max_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_speed"), "", "get_max_speed");

    ClassDB::bind_method(D_METHOD("get_current_speed"), &Unit::get_current_speed);
    ClassDB::bind_method(D_METHOD("set_current_speed", "current_speed"), &Unit::set_current_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_speed"), "set_current_speed", "get_current_speed");

    ClassDB::bind_method(D_METHOD("set_strength", "strength"), &Unit::set_strength);
    ClassDB::bind_method(D_METHOD("add_bonus_strength"), &Unit::add_bonus_strength);
    ClassDB::bind_method(D_METHOD("get_strength"), &Unit::get_strength);
    ClassDB::bind_method(D_METHOD("get_strength_mod"), &Unit::get_strength_mod);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "strength"), "", "get_strength");

    ClassDB::bind_method(D_METHOD("set_dexterity", "dexterity"), &Unit::set_dexterity);
    ClassDB::bind_method(D_METHOD("add_bonus_dexterity"), &Unit::add_bonus_dexterity);
    ClassDB::bind_method(D_METHOD("get_dexterity"), &Unit::get_dexterity);
    ClassDB::bind_method(D_METHOD("get_dexterity_mod"), &Unit::get_dexterity_mod);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "dexterity"), "", "get_dexterity");

    ClassDB::bind_method(D_METHOD("set_constitution", "constitution"), &Unit::set_constitution);
    ClassDB::bind_method(D_METHOD("add_bonus_constitution"), &Unit::add_bonus_constitution);
    ClassDB::bind_method(D_METHOD("get_constitution"), &Unit::get_constitution);
    ClassDB::bind_method(D_METHOD("get_constitution_mod"), &Unit::get_constitution_mod);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "constitution"), "", "get_constitution");

    ClassDB::bind_method(D_METHOD("set_wisdom", "wisdom"), &Unit::set_wisdom);
    ClassDB::bind_method(D_METHOD("add_bonus_wisdom"), &Unit::add_bonus_wisdom);
    ClassDB::bind_method(D_METHOD("get_wisdom"), &Unit::get_wisdom);
    ClassDB::bind_method(D_METHOD("get_wisdom_mod"), &Unit::get_wisdom_mod);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "wisdom"), "", "get_wisdom");

    ClassDB::bind_method(D_METHOD("set_intelligence", "intelligence"), &Unit::set_intelligence);
    ClassDB::bind_method(D_METHOD("add_bonus_intelligence"), &Unit::add_bonus_intelligence);
    ClassDB::bind_method(D_METHOD("get_intelligence"), &Unit::get_intelligence);
    ClassDB::bind_method(D_METHOD("get_intelligence_mod"), &Unit::get_intelligence_mod);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "intelligence"), "", "get_intelligence");

    ClassDB::bind_method(D_METHOD("set_charisma", "charisma"), &Unit::set_charisma);
    ClassDB::bind_method(D_METHOD("add_bonus_charisma"), &Unit::add_bonus_charisma);
    ClassDB::bind_method(D_METHOD("get_charisma"), &Unit::get_charisma);
    ClassDB::bind_method(D_METHOD("get_charisma_mod"), &Unit::get_charisma_mod);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "charisma"), "", "get_charisma");

    ClassDB::bind_method(D_METHOD("set_main_hand_slot", "artifact"), &Unit::set_main_hand_slot);
    ClassDB::bind_method(D_METHOD("get_main_hand_slot"), &Unit::get_main_hand_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "main_hand_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_main_hand_slot", "get_main_hand_slot");

    ClassDB::bind_method(D_METHOD("set_off_hand_slot", "artifact"), &Unit::set_off_hand_slot);
    ClassDB::bind_method(D_METHOD("get_off_hand_slot"), &Unit::get_off_hand_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "off_hand_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_off_hand_slot", "get_off_hand_slot");

    ClassDB::bind_method(D_METHOD("set_armor_slot", "artifact"), &Unit::set_armor_slot);
    ClassDB::bind_method(D_METHOD("get_armor_slot"), &Unit::get_armor_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "armor_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_armor_slot", "get_armor_slot");

    ClassDB::bind_method(D_METHOD("set_helm_slot", "artifact"), &Unit::set_helm_slot);
    ClassDB::bind_method(D_METHOD("get_helm_slot"), &Unit::get_helm_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "helm_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_helm_slot", "get_helm_slot");

    ClassDB::bind_method(D_METHOD("set_gloves_slot", "artifact"), &Unit::set_gloves_slot);
    ClassDB::bind_method(D_METHOD("get_gloves_slot"), &Unit::get_gloves_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gloves_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_gloves_slot", "get_gloves_slot");

    ClassDB::bind_method(D_METHOD("set_boots_slot", "artifact"), &Unit::set_boots_slot);
    ClassDB::bind_method(D_METHOD("get_boots_slot"), &Unit::get_boots_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "boots_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_boots_slot", "get_boots_slot");

    ClassDB::bind_method(D_METHOD("set_accessory_1_slot", "artifact"), &Unit::set_accessory_1_slot);
    ClassDB::bind_method(D_METHOD("get_accessory_1_slot"), &Unit::get_accessory_1_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "accessory_1_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_accessory_1_slot", "get_accessory_1_slot");

    ClassDB::bind_method(D_METHOD("set_accessory_2_slot", "artifact"), &Unit::set_accessory_2_slot);
    ClassDB::bind_method(D_METHOD("get_accessory_2_slot"), &Unit::get_accessory_2_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "accessory_2_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_accessory_2_slot", "get_accessory_2_slot");

    ClassDB::bind_method(D_METHOD("set_accessory_3_slot", "artifact"), &Unit::set_accessory_3_slot);
    ClassDB::bind_method(D_METHOD("get_accessory_3_slot"), &Unit::get_accessory_3_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "accessory_3_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_accessory_3_slot", "get_accessory_3_slot");

    ClassDB::bind_method(D_METHOD("set_accessory_4_slot", "artifact"), &Unit::set_accessory_4_slot);
    ClassDB::bind_method(D_METHOD("get_accessory_4_slot"), &Unit::get_accessory_4_slot);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "accessory_4_slot", PROPERTY_HINT_RESOURCE_TYPE, "Artifact"), "set_accessory_4_slot", "get_accessory_4_slot");

    ClassDB::bind_method(D_METHOD("get_inventory"), &Unit::get_inventory);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "inventory"), "", "get_inventory");

    ClassDB::bind_method(D_METHOD("set_free_actions_max", "value"), &Unit::set_free_actions_max);
    ClassDB::bind_method(D_METHOD("get_free_actions_max"), &Unit::get_free_actions_max);
    ClassDB::bind_method(D_METHOD("set_free_actions_current", "value"), &Unit::set_free_actions_current);
    ClassDB::bind_method(D_METHOD("get_free_actions_current"), &Unit::get_free_actions_current);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "free_actions_max"), "", "get_free_actions_max");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "free_actions_current"), "set_free_actions_current", "get_free_actions_current");

    ClassDB::bind_method(D_METHOD("set_main_actions_max", "value"), &Unit::set_main_actions_max);
    ClassDB::bind_method(D_METHOD("get_main_actions_max"), &Unit::get_main_actions_max);
    ClassDB::bind_method(D_METHOD("set_main_actions_current", "value"), &Unit::set_main_actions_current);
    ClassDB::bind_method(D_METHOD("get_main_actions_current"), &Unit::get_main_actions_current);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "main_actions_max"), "", "get_main_actions_max");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "main_actions_current"), "set_main_actions_current", "get_main_actions_current");

    ClassDB::bind_method(D_METHOD("set_bonus_actions_max", "value"), &Unit::set_bonus_actions_max);
    ClassDB::bind_method(D_METHOD("get_bonus_actions_max"), &Unit::get_bonus_actions_max);
    ClassDB::bind_method(D_METHOD("set_bonus_actions_current", "value"), &Unit::set_bonus_actions_current);
    ClassDB::bind_method(D_METHOD("get_bonus_actions_current"), &Unit::get_bonus_actions_current);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_actions_max"), "", "get_bonus_actions_max");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "bonus_actions_current"), "set_bonus_actions_current", "get_bonus_actions_current");

    ClassDB::bind_method(D_METHOD("set_reaction_actions_max", "value"), &Unit::set_reaction_actions_max);
    ClassDB::bind_method(D_METHOD("get_reaction_actions_max"), &Unit::get_reaction_actions_max);
    ClassDB::bind_method(D_METHOD("set_reaction_actions_current", "value"), &Unit::set_reaction_actions_current);
    ClassDB::bind_method(D_METHOD("get_reaction_actions_current"), &Unit::get_reaction_actions_current);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "reaction_actions_max"), "", "get_reaction_actions_max");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "reaction_actions_current"), "set_reaction_actions_current", "get_reaction_actions_current");

    ClassDB::bind_method(D_METHOD("set_legendary_actions_max", "value"), &Unit::set_legendary_actions_max);
    ClassDB::bind_method(D_METHOD("get_legendary_actions_max"), &Unit::get_legendary_actions_max);
    ClassDB::bind_method(D_METHOD("set_legendary_actions_current", "value"), &Unit::set_legendary_actions_current);
    ClassDB::bind_method(D_METHOD("get_legendary_actions_current"), &Unit::get_legendary_actions_current);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "legendary_actions_max"), "", "get_legendary_actions_max");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "legendary_actions_current"), "set_legendary_actions_current", "get_legendary_actions_current");

    ClassDB::bind_method(D_METHOD("get_max_actions"), &Unit::get_max_actions);
    ClassDB::bind_method(D_METHOD("get_current_actions"), &Unit::get_current_actions);


    ClassDB::bind_method(D_METHOD("set_type"), &Unit::set_type);
    ClassDB::bind_method(D_METHOD("get_type"), &Unit::get_type);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "type"), "", "get_type");

    ClassDB::bind_method(D_METHOD("lock_stats"), &Unit::lock_stats);

    ClassDB::bind_method(D_METHOD("reset_speed"), &Unit::reset_speed);
    ClassDB::bind_method(D_METHOD("reset_bonus"), &Unit::reset_bonus);

    ClassDB::bind_method(D_METHOD("get_board"), &Unit::get_board);
    ClassDB::bind_method(D_METHOD("get_core"), &Unit::get_core);

    ClassDB::bind_method(D_METHOD("take_damage", "amount", "damage_type"), &Unit::take_damage);
    ClassDB::bind_method(D_METHOD("is_alive"), &Unit::is_alive);
    ClassDB::bind_method(D_METHOD("get_total_resistance", "damage_type"), &Unit::get_total_resistance);

    ClassDB::bind_method(D_METHOD("roll_dice", "count", "sides", "mod"), &Unit::roll_dice);
    ClassDB::bind_method(D_METHOD("subscribe_event_bus", "event_name", "callable"), &Unit::subscribe_event_bus);
}
