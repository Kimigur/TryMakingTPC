#ifndef CORE_H
#define CORE_H

#include "module/board.h"
#include <godot_cpp/classes/node.hpp>

namespace godot{

class Core : public Node {
    GDCLASS(Core, Node);
public:
    Core();

    void _ready() override;

    Ref<Board> get_board();

    Array get_reachable_cells(Vector2i from);
    bool move_unit(Vector2i from, Vector2i to);


protected:
    static void _bind_methods();

private:
    Ref<Board> board;
};

}

#endif // CORE_H
