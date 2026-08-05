#include "constants.h"
#ifndef ACTION_H
#define ACTION_H

#include "template/unit.h"
#include "module/board.h"
#include "godot_cpp/core/gdvirtual.gen.inc"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/texture2d.hpp>

namespace godot {

class Artifact;

class Action : public Resource
{
    GDCLASS(Action, Resource);
public:
    Action();

    void set_impacts(const Dictionary &p_impacts);
    Dictionary get_impacts() const;

    void set_artifact(Ref<Artifact> p_artifact);
    Ref<Artifact> get_artifact();

    void set_cost_type(int p_type);
    int get_cost_type() const;

    void set_icon(const Ref<Texture2D> &p_icon);
    Ref<Texture2D> get_icon() const;

    Array get_valid_targets(Unit *source, Board *board);
    bool execute(Unit *source, Board *board, const Variant &target);

    void attack(Unit *attacker, Unit *defender, int attack_bonus, const Callable &on_hit);

protected:
    static void _bind_methods();
    GDVIRTUAL2R(Array, get_valid_targets, Unit*, Board*)
    GDVIRTUAL3R(bool, _execute, Unit*, Board*, Variant)

private:
    Ref<Artifact> artifact;
    Dictionary impacts;
    int cost_type = MAIN;
    Ref<Texture2D> icon;
};

}

#endif // ACTION_H
