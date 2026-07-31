#include "cell.h"

using namespace godot;

Cell::Cell() {

}

void Cell::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_cell_name"), &Cell::get_cell_name);
    ClassDB::bind_method(D_METHOD("set_cell_name", "name"), &Cell::set_cell_name);
}
