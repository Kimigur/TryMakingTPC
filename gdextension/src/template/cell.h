#ifndef CELL_H
#define CELL_H

#include "godot_cpp/classes/texture2d.hpp"
#include <godot_cpp/classes/resource.hpp>

namespace godot{

class Cell : public Resource
{
    GDCLASS(Cell, Resource);
public:
    Cell();

    void set_cell_name(const String& p_name);
    String get_cell_name() const;

    void set_cell_icon(const Ref<Texture2D>& p_icon);
    Ref<Texture2D> get_cell_icon() const;

protected:
    static void _bind_methods();

private:
    String cell_name = "EmptyCell";
    Ref<Texture2D> icon;
};

}

#endif // CELL_H
