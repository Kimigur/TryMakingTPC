#include "cell.h"

using namespace godot;

Cell::Cell() {

}

void Cell::set_cell_name(const String &p_name) {
    cell_name = p_name;
}

String Cell::get_cell_name() const {
    return cell_name;
}

void Cell::set_cell_icon(const Ref<Texture2D> &p_icon)
{
    icon = p_icon;
}

Ref<Texture2D> Cell::get_cell_icon() const
{
    return icon;
}

void Cell::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_cell_name"), &Cell::get_cell_name);
    ClassDB::bind_method(D_METHOD("set_cell_name", "name"), &Cell::set_cell_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_cell_name", "get_cell_name");

    ClassDB::bind_method(D_METHOD("get_cell_icon"), &Cell::get_cell_icon);
    ClassDB::bind_method(D_METHOD("set_cell_icon", "icon"), &Cell::set_cell_icon);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_cell_icon", "get_cell_icon");
}
