#pragma once
#ifndef CORE_H
#define CORE_H

#include "module/board.h"
#include "module/bus.h"
#include <godot_cpp/classes/node.hpp>
#include <vector>

namespace godot{

struct TurnEntry {
    Ref<Unit> unit;
    int initiative = 0;
};

class Core : public Node {
    GDCLASS(Core, Node);
public:
    Core();

    void _ready() override;

    Ref<Board> get_board();
    Ref<Bus> get_event_bus();

    bool move_unit(Vector2i from, Vector2i to);

    void start_combat();
    void add_to_queue(Ref<Unit> unit);
    void ask_next_turn();
    void next_turn();
    Ref<Unit> get_current_unit() const;

    void attack(Unit *attacker, Unit *defender, int attack_bonus, const Callable &on_hit);

    int roll_dice(int dice_count, int dice_sides, int modifier = 0);

protected:
    static void _bind_methods();

private:
    Ref<Board> board;
    Ref<Bus> event_bus;

    std::vector<TurnEntry> turn_queue;
    int current_turn_index = 0;
    int round_number = 0;
    bool in_combat = false;
};

}

#endif // CORE_H
