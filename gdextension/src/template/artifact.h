#ifndef ARTIFACT_H
#define ARTIFACT_H

#include "godot_cpp/classes/texture2d.hpp"
#include "godot_cpp/core/gdvirtual.gen.inc"
#include <godot_cpp/classes/resource.hpp>

namespace godot {

class Unit;

class Artifact : public Resource
{
    GDCLASS(Artifact, Resource);
public:
    Artifact();

    void ready();
    void add_bonus();

    Array get_actions();

    void set_artifact_name(String p_artifact_name);
    String get_artifact_name();

    void set_artifact_type(String p_artifact_type);
    String get_artifact_type();

    void set_artifact_slot_type(String p_artifact_slot_type);
    String get_artifact_slot_type();

    void set_icon(const Ref<Texture2D> &p_icon);
    Ref<Texture2D> get_icon() const;

    void set_unit(Ref<Unit> p_unit);
    Ref<Unit> get_unit();

protected:
    static void _bind_methods();

    GDVIRTUAL0(ready);
    GDVIRTUAL0(add_bonus);
    GDVIRTUAL0R(Array, get_actions);

private:
    String artifact_name = "";
    String artifact_type = "";
    String artifact_slot_type = "";
    Ref<Texture2D> icon;

    Ref<Unit> unit;
};

}


#endif // ARTIFACT_H
