#ifndef CELL_H
#define CELL_H

#include <godot_cpp/classes/resource.hpp>

namespace godot{

class Cell : public Resource
{
    GDCLASS(Cell, Resource);
public:
    Cell();

    void set_cell_name(const String& p_name) { cell_name = p_name; }
    String get_cell_name() const { return cell_name; }

protected:
    static void _bind_methods();

private:
    String cell_name = "EmptyCell";
};

}

#endif // CELL_H
