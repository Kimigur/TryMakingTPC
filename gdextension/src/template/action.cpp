#include "action.h"
#include "template/artifact.h"

using namespace godot;

Action::Action() { }

Dictionary Action::get_impacts() const {
    return impacts;
}

void Action::set_impacts(const Dictionary &p_impacts) {
    impacts = p_impacts;
}

void Action::set_artifact(Artifact *p_artifact)
{
    artifact = p_artifact;
}

Artifact *Action::get_artifact()
{
    return artifact;
}

Array Action::get_valid_targets(Unit *source, Board *board)
{
    Array ret;
    GDVIRTUAL_CALL(get_valid_targets, source, board, ret);
    return ret;
}

bool Action::execute(Unit *source, Board *board, const Variant &target)
{
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
    GDVIRTUAL_CALL(execute, source, board, target, ret);
    return ret;
}

void Action::_bind_methods()
{
    GDVIRTUAL_BIND(get_valid_targets, "source", "board");
    GDVIRTUAL_BIND(execute, "source", "board", "target");

    ClassDB::bind_method(D_METHOD("set_impacts", "impacts"), &Action::set_impacts);
    ClassDB::bind_method(D_METHOD("get_impacts"), &Action::get_impacts);
    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "impacts"), "set_impacts", "get_impacts");

    ClassDB::bind_method(D_METHOD("set_artifact", "artifact"), &Action::set_artifact);
    ClassDB::bind_method(D_METHOD("get_artifact"), &Action::get_artifact);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "artifact"), "set_artifact", "get_artifact");
}
