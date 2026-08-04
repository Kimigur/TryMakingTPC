#include "artifact.h"
#include "template/unit.h"

using namespace godot;

Artifact::Artifact() {
    unit = nullptr;
}

void Artifact::ready()
{
    GDVIRTUAL_CALL(ready);
}

Array Artifact::get_actions()
{
    Array ret;
    GDVIRTUAL_CALL(get_actions, ret);
    return ret;
}

void Artifact::set_artifact_name(String p_artifact_name)
{
    artifact_name = p_artifact_name;
}

String Artifact::get_artifact_name()
{
    return artifact_name;
}

void Artifact::set_artifact_type(String p_artifact_type)
{
    artifact_type = p_artifact_type;
}

String Artifact::get_artifact_type()
{
    return artifact_type;
}

void Artifact::set_artifact_slot_type(String p_artifact_slot_type)
{
    artifact_slot_type = p_artifact_slot_type;
}

String Artifact::get_artifact_slot_type()
{
    return artifact_slot_type;
}

void Artifact::set_unit(Unit *p_unit)
{
    unit = p_unit;
}

Unit* Artifact::get_unit()
{
    return unit;
}

void Artifact::_bind_methods()
{
    GDVIRTUAL_BIND(ready);
    GDVIRTUAL_BIND(get_actions);

    ClassDB::bind_method(D_METHOD("set_artifact_name", "name"), &Artifact::set_artifact_name);
    ClassDB::bind_method(D_METHOD("get_artifact_name"), &Artifact::get_artifact_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "artifact_name"), "set_artifact_name", "get_artifact_name");

    ClassDB::bind_method(D_METHOD("set_artifact_type", "type"), &Artifact::set_artifact_type);
    ClassDB::bind_method(D_METHOD("get_artifact_type"), &Artifact::get_artifact_type);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "artifact_type"), "set_artifact_type", "get_artifact_type");

    ClassDB::bind_method(D_METHOD("set_artifact_slot_type", "category"), &Artifact::set_artifact_slot_type);
    ClassDB::bind_method(D_METHOD("get_artifact_slot_type"), &Artifact::get_artifact_slot_type);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "artifact_slot_type"), "set_artifact_slot_type", "get_artifact_slot_type");

    ClassDB::bind_method(D_METHOD("set_unit", "unit"), &Artifact::set_unit);
    ClassDB::bind_method(D_METHOD("get_unit"), &Artifact::get_unit);
}
