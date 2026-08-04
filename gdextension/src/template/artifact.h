#ifndef ARTIFACT_H
#define ARTIFACT_H

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

    Array get_actions();

    void set_artifact_name(String p_artifact_name);
    String get_artifact_name();

    void set_artifact_type(String p_artifact_type);
    String get_artifact_type();

    void set_artifact_slot_type(String p_artifact_slot_type);
    String get_artifact_slot_type();

    void set_unit(Unit* p_unit);
    Unit *get_unit();

protected:
    static void _bind_methods();

    GDVIRTUAL0(ready);
    GDVIRTUAL0R(Array, get_actions);

private:
    String artifact_name = "";
    String artifact_type = "";
    String artifact_slot_type = "";

    Unit* unit;
};

}


#endif // ARTIFACT_H
