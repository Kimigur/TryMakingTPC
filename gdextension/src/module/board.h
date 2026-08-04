#pragma once
#ifndef BOARD_H
#define BOARD_H

#include "template/cell.h"
#include "template/unit.h"
#include <godot_cpp/classes/ref_counted.hpp>


namespace godot{

class Board : public RefCounted
{
    GDCLASS(Board, RefCounted)
public:
    Board();
    ~Board();

    Ref<Cell> get_cell(int x, int y) const;
    Ref<Cell> get_cell(Vector2i pos) const;
    void set_cell(int x, int y, const Ref<Cell>& cell);

    Ref<Unit> get_unit(int x, int y) const;
    Ref<Unit> get_unit(Vector2i pos) const;
    void set_unit(int x, int y, const Ref<Unit>& unit);

    Array get_reachable_cells(Vector2i from);
    Array get_path(Vector2i from, Vector2i to);
    bool move_unit(Vector2i from, Vector2i to);

    bool is_valid_coord(int x, int y);

    Vector2 get_board_size();
    Array get_units_arrey() const;
    Array get_cells_arrey() const;

protected:
    static void _bind_methods();

private:
    static const int WIDTH = 20;  // Ширина x
    static const int HEIGHT = 20; // Высота y

    Ref<Cell> cells[WIDTH][HEIGHT];
    Ref<Unit> units[WIDTH][HEIGHT];
};

}

#endif // BOARD_H
