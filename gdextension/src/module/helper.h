#ifndef HELPER_H
#define HELPER_H

#include "godot_cpp/classes/ref_counted.hpp"

namespace godot {

class Board;

class Helper : public RefCounted
{
    GDCLASS(Helper, RefCounted)
public:
    Helper();

    Array get_line_target(Ref<Board> board, Vector2i start_pos, int radius, int target_type);

    Array get_bfs_target(Ref<Board> board, Vector2i start_pos, int radius, int target_type);

    Array get_bfs_target_path(Ref<Board> board, Vector2i start_pos, int radius, Vector2i end_pos);

    Array get_all_target(Ref<Board> board, Vector2i start_pos, int radius, int target_type);

protected:
    static void _bind_methods();
};

}

#endif // HELPER_H
