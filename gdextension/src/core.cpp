#include "core.h"

using namespace godot;

Core::Core() { }

void Core::_ready()
{
    board.instantiate();

    Ref<Unit> dummy;
    dummy.instantiate();
    dummy->set_unit_name("Target Dummy");

    Vector2 board_size = board->get_board_size();

    board->set_unit(board_size[0]/2, board_size[1]/2, dummy);

    Ref<Unit> dummy1;
    dummy.instantiate();
    dummy->set_unit_name("Target Dummy");

    board->set_unit(board_size[0]/2-2, board_size[1]/2, dummy);

    Ref<Unit> dummy2;
    dummy.instantiate();
    dummy->set_unit_name("Target Dummy");

    board->set_unit(board_size[0]/2-2, board_size[1]/2+1, dummy);

    Ref<Unit> dummy3;
    dummy.instantiate();
    dummy->set_unit_name("Target Dummy");

    board->set_unit(board_size[0]/2-2, board_size[1]/2-1, dummy);

    Ref<Unit> dummy4;
    dummy.instantiate();
    dummy->set_unit_name("Target Dummy");

    board->set_unit(board_size[0]/2-2, board_size[1]/2+2, dummy);

    Ref<Unit> dummy5;
    dummy.instantiate();
    dummy->set_unit_name("Target Dummy");

    board->set_unit(board_size[0]/2-2, board_size[1]/2-2, dummy);

    UtilityFunctions::print("CoreLoad");
}

Ref<Board> Core::get_board()
{
    return board;
}

Array Core::get_reachable_cells(Vector2i from)
{
    return board->get_reachable_cells(from);
}

bool Core::move_unit(Vector2i from, Vector2i to)
{
    return board->move_unit(from, to);
}

void Core::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("_ready_cpp"), &Core::_ready);
    ClassDB::bind_method(D_METHOD("get_board"), &Core::get_board);

    ClassDB::bind_method(D_METHOD("get_reachable_cells", "from"), &Core::get_reachable_cells);
    ClassDB::bind_method(D_METHOD("move_unit", "from", "to"), &Core::move_unit);
}
