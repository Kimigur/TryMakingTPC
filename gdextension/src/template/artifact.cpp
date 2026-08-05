#include "artifact.h"
#include "template/unit.h"

using namespace godot;

Artifact::Artifact() {}

void Artifact::ready()
{
    GDVIRTUAL_CALL(ready);
}

void Artifact::add_bonus()
{
    GDVIRTUAL_CALL(add_bonus);
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

void Artifact::set_icon(const Ref<Texture2D> &p_icon)
{
    icon = p_icon;
}

Ref<Texture2D> Artifact::get_icon() const
{
    return icon;
}

void Artifact::set_unit(Ref<Unit> p_unit)
{
    unit = p_unit;
}

Ref<Unit> Artifact::get_unit()
{
    return unit;
}

void Artifact::_bind_methods()
{
    GDVIRTUAL_BIND(ready);
    GDVIRTUAL_BIND(add_bonus);
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

    ClassDB::bind_method(D_METHOD("set_icon", "icon"), &Artifact::set_icon);
    ClassDB::bind_method(D_METHOD("get_icon"), &Artifact::get_icon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_icon", "get_icon");

    ClassDB::bind_method(D_METHOD("set_unit", "unit"), &Artifact::set_unit);
    ClassDB::bind_method(D_METHOD("get_unit"), &Artifact::get_unit);
}
