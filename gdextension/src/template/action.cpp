#include "action.h"
#include "template/artifact.h"
#include "core.h"

using namespace godot;

Action::Action() { }

Dictionary Action::get_impacts() const {
    return impacts;
}

void Action::set_impacts(const Dictionary &p_impacts) {
    impacts = p_impacts;
}

void Action::set_artifact(Ref<Artifact> p_artifact)
{
    artifact = p_artifact;
}

Ref<Artifact> Action::get_artifact()
{
    return *artifact;
}

void Action::set_cost_type(int p_type)
{
    cost_type = p_type;
}

int Action::get_cost_type() const
{
    return cost_type;
}

void Action::set_icon(const Ref<Texture2D> &p_icon)
{
    icon = p_icon;
}

Ref<Texture2D> Action::get_icon() const
{
    return icon;
}

Array Action::get_valid_targets(Unit *source, Board *board)
{
    Array ret;
    GDVIRTUAL_CALL(get_valid_targets, source, board, ret);
    return ret;
}

bool Action::execute(Unit *source, Board *board, const Variant &target)
{
    int act = source->get_current_ations()[cost_type];
    if(act <= 0){
        return false;
    }
    Array valid = get_valid_targets(source, board);
    bool f = false;
    for (int i = 0; i < valid.size(); ++i) {
        if(target == valid[i]){
            f = true;
            break;
        }
    }
    if(!f){
        return false;
    }
    bool ret = false;
    GDVIRTUAL_CALL(_execute, source, board, target, ret);
    if(ret){
        if (cost_type == FREE) {
            source->set_free_ations_current(act - 1);
        } else if(cost_type == MAIN) {
            source->set_main_ations_current(act - 1);
        } else if(cost_type == BONUS) {
            source->set_bonus_ations_current(act - 1);
        } else if(cost_type == REACTION) {
            source->set_reaction_ations_current(act - 1);
        } else if(cost_type == LEGENDARY) {
            source->set_legendary_ations_current(act - 1);
        }
        source->get_core()->get_event_bus()->bus_emit("action_executed", Array::make(source, this));
    }
    return ret;
}

void Action::attack(Unit *attacker, Unit *defender, int attack_bonus, const Callable &on_hit)
{
    attacker->get_core()->attack(attacker, defender, attack_bonus, on_hit);
}

void Action::_bind_methods()
{
    String damage_hint = "NONE,BLUDGEONING,PIERCING,SLASHING,FIRE,COLD,LIGHTNING,ACID,POISON,FORCE,RADIANT,NECROTIC,PSYCHIC";

    GDVIRTUAL_BIND(get_valid_targets, "source", "board");
    GDVIRTUAL_BIND(_execute, "source", "board", "target");

    ClassDB::bind_method(D_METHOD("execute", "source", "board", "target"), &Action::execute);

    ClassDB::bind_method(D_METHOD("set_impacts", "impacts"), &Action::set_impacts);
    ClassDB::bind_method(D_METHOD("get_impacts"), &Action::get_impacts);
    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "impacts"), "set_impacts", "get_impacts");

    ClassDB::bind_method(D_METHOD("set_artifact", "artifact"), &Action::set_artifact);
    ClassDB::bind_method(D_METHOD("get_artifact"), &Action::get_artifact);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "artifact"), "set_artifact", "get_artifact");

    ClassDB::bind_integer_constant(get_class_static(), "", "COST_FREE",     ActionCostType::FREE);
    ClassDB::bind_integer_constant(get_class_static(), "", "COST_MAIN",     ActionCostType::MAIN);
    ClassDB::bind_integer_constant(get_class_static(), "", "COST_BONUS",    ActionCostType::BONUS);
    ClassDB::bind_integer_constant(get_class_static(), "", "COST_REACTION", ActionCostType::REACTION);
    ClassDB::bind_integer_constant(get_class_static(), "", "COST_LEGENDARY",ActionCostType::LEGENDARY);

    ClassDB::bind_integer_constant(get_class_static(), "", "NONE",          DamageType::NONE);
    ClassDB::bind_integer_constant(get_class_static(), "", "BLUDGEONING",   DamageType::BLUDGEONING);
    ClassDB::bind_integer_constant(get_class_static(), "", "PIERCING",      DamageType::PIERCING);
    ClassDB::bind_integer_constant(get_class_static(), "", "SLASHING",      DamageType::SLASHING);
    ClassDB::bind_integer_constant(get_class_static(), "", "FIRE",          DamageType::FIRE);
    ClassDB::bind_integer_constant(get_class_static(), "", "COLD",          DamageType::COLD);
    ClassDB::bind_integer_constant(get_class_static(), "", "LIGHTNING",     DamageType::LIGHTHING);
    ClassDB::bind_integer_constant(get_class_static(), "", "ACID",          DamageType::ACID);
    ClassDB::bind_integer_constant(get_class_static(), "", "POISON",        DamageType::POISON);
    ClassDB::bind_integer_constant(get_class_static(), "", "FORCE",         DamageType::FORCE);
    ClassDB::bind_integer_constant(get_class_static(), "", "RADIANT",       DamageType::RADIANT);
    ClassDB::bind_integer_constant(get_class_static(), "", "NECROTIC",      DamageType::NECROTIC);
    ClassDB::bind_integer_constant(get_class_static(), "", "PSYCHIC",       DamageType::PSYCHIC);


    ClassDB::bind_method(D_METHOD("set_cost_type", "cost_type"), &Action::set_cost_type);
    ClassDB::bind_method(D_METHOD("get_cost_type"), &Action::get_cost_type);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cost_type", PROPERTY_HINT_ENUM, "Free,Main,Bonus,Reaction,Legendary"), "set_cost_type", "get_cost_type");

    ClassDB::bind_method(D_METHOD("set_icon", "icon"), &Action::set_icon);
    ClassDB::bind_method(D_METHOD("get_icon"), &Action::get_icon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_icon", "get_icon");

    ClassDB::bind_method(D_METHOD("attack", "attacker", "defender", "attack_bonus", "func_on_hit"), &Action::attack);
}
