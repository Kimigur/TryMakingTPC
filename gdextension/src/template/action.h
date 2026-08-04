#ifndef ACTION_H
#define ACTION_H

#include "template/unit.h"
#include "module/board.h"
#include "godot_cpp/core/gdvirtual.gen.inc"
#include <godot_cpp/classes/resource.hpp>

namespace godot {

class Artifact;

class Action : public Resource
{
    GDCLASS(Action, Resource);
public:
    Action();

    void set_impacts(const Dictionary &p_impacts);
    Dictionary get_impacts() const;

    void set_artifact(Artifact* p_artifact);
    Artifact *get_artifact();

    Array get_valid_targets(Unit *source, Board *board);
    bool execute(Unit *source, Board *board, const Variant &target);

protected:
    static void _bind_methods();
    GDVIRTUAL2R(Array, get_valid_targets, Unit*, Board*)
    GDVIRTUAL3R(bool, execute, Unit*, Board*, Variant)

private:
    Artifact* artifact = nullptr;
    Dictionary impacts;
};

}

#endif // ACTION_H
