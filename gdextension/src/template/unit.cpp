#include "unit.h"
#include "core.h"
#include "module/board.h"

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

void Unit::reset_bonus()
{
    bonus_max_speed = 0;

    bonus_strength = 0;      // Сила
    bonus_dexterity = 0;     // Ловкость
    bonus_constitution = 0;  // Телосложение
    bonus_wisdom = 0;        // Мудрость
    bonus_intelligence = 0;  // Интелект
    bonus_charisma = 0;      // Харизма
}

void Unit::set_board(Ref<Board> &p_board)
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
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "unit_name"), "", "get_unit_name");

    ClassDB::bind_method(D_METHOD("get_max_speed"), &Unit::get_max_speed);
    ClassDB::bind_method(D_METHOD("set_max_speed", "max_speed"), &Unit::set_max_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_speed"), "", "get_max_speed");

    ClassDB::bind_method(D_METHOD("get_current_speed"), &Unit::get_current_speed);
    ClassDB::bind_method(D_METHOD("set_current_speed", "current_speed"), &Unit::set_current_speed);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_speed"), "set_current_speed", "get_current_speed");

    ClassDB::bind_method(D_METHOD("set_strength"), &Unit::set_strength);
    ClassDB::bind_method(D_METHOD("add_bonus_strength"), &Unit::add_bonus_strength);
    ClassDB::bind_method(D_METHOD("get_strength"), &Unit::get_strength);
    ClassDB::bind_method(D_METHOD("get_strength_mod"), &Unit::get_strength_mod);

    ClassDB::bind_method(D_METHOD("set_dexterity"), &Unit::set_dexterity);
    ClassDB::bind_method(D_METHOD("add_bonus_dexterity"), &Unit::add_bonus_dexterity);
    ClassDB::bind_method(D_METHOD("get_dexterity"), &Unit::get_dexterity);
    ClassDB::bind_method(D_METHOD("get_dexterity_mod"), &Unit::get_dexterity_mod);

    ClassDB::bind_method(D_METHOD("set_constitution"), &Unit::set_constitution);
    ClassDB::bind_method(D_METHOD("add_bonus_constitution"), &Unit::add_bonus_constitution);
    ClassDB::bind_method(D_METHOD("get_constitution"), &Unit::get_constitution);
    ClassDB::bind_method(D_METHOD("get_constitution_mod"), &Unit::get_constitution_mod);

    ClassDB::bind_method(D_METHOD("set_wisdom"), &Unit::set_wisdom);
    ClassDB::bind_method(D_METHOD("add_bonus_wisdom"), &Unit::add_bonus_wisdom);
    ClassDB::bind_method(D_METHOD("get_wisdom"), &Unit::get_wisdom);
    ClassDB::bind_method(D_METHOD("get_wisdom_mod"), &Unit::get_wisdom_mod);

    ClassDB::bind_method(D_METHOD("set_intelligence"), &Unit::set_intelligence);
    ClassDB::bind_method(D_METHOD("add_bonus_intelligence"), &Unit::add_bonus_intelligence);
    ClassDB::bind_method(D_METHOD("get_intelligence"), &Unit::get_intelligence);
    ClassDB::bind_method(D_METHOD("get_intelligence_mod"), &Unit::get_intelligence_mod);

    ClassDB::bind_method(D_METHOD("set_charisma"), &Unit::set_charisma);
    ClassDB::bind_method(D_METHOD("add_bonus_charisma"), &Unit::add_bonus_charisma);
    ClassDB::bind_method(D_METHOD("get_charisma"), &Unit::get_charisma);
    ClassDB::bind_method(D_METHOD("get_charisma_mod"), &Unit::get_charisma_mod);

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

    ClassDB::bind_method(D_METHOD("set_type"), &Unit::set_type);
    ClassDB::bind_method(D_METHOD("get_type"), &Unit::get_type);

    ClassDB::bind_method(D_METHOD("lock_stats"), &Unit::lock_stats);

    ClassDB::bind_method(D_METHOD("reset_speed"), &Unit::reset_speed);
    ClassDB::bind_method(D_METHOD("reset_bonus"), &Unit::reset_bonus);

    ClassDB::bind_method(D_METHOD("get_board"), &Unit::get_board);
    ClassDB::bind_method(D_METHOD("get_core"), &Unit::get_core);
}
