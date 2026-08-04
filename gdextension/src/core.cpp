#include "core.h"
#include <algorithm>

using namespace godot;

Core::Core() { }

void Core::_ready()
{
    board.instantiate();
    event_bus.instantiate();

    UtilityFunctions::print("CoreLoad");
}

Ref<Board> Core::get_board()
{
    return board;
}

Ref<Bus> Core::get_event_bus()
{
    return event_bus;
}

Array Core::get_reachable_cells(Vector2i from)
{
    if (!board->is_valid_coord(from.x, from.y) || board->get_unit(from.x, from.y) == nullptr) {
        return Array();
    }
    return board->get_reachable_cells(from);
}

Array Core::get_path(Vector2i from, Vector2i to)
{
    if (!board->is_valid_coord(from.x, from.y) || !board->is_valid_coord(to.x, to.y)) {
        return Array();
    }
    if (board->get_unit(from.x, from.y) == nullptr) {
        return Array();
    }
    return board->get_path(from, to);
}

bool Core::move_unit(Vector2i from, Vector2i to)
{
    if(board->move_unit(from, to)){
        event_bus->bus_emit("unit_move", Array::make(board->get_unit(to), from, to));
        return true;
    } else {
        return false;
    }
}

void Core::start_combat()
{
    turn_queue.clear();
    round_number = 1;
    current_turn_index = -1;
    in_combat = true;

    std::vector<TurnEntry> active_units;
    std::vector<TurnEntry> environment_units;

    Vector2 board_size = board->get_board_size();

    for (int x = 0; x < board_size[0]; ++x) {
        for (int y = 0; y < board_size[1]; ++y) {
            Ref<Unit> unit = board->get_unit(x, y);
            if (unit.is_valid()) {
                TurnEntry entry;
                entry.unit = unit;
                unit->set_core(this);
                unit->set_board(&board);
                unit->ready();

                if (unit->get_type() == 2) {
                    entry.initiative = -999;
                    environment_units.push_back(entry);
                } else {
                    entry.initiative = roll_dice(1, 20, unit->get_dexterity_mod());
                    active_units.push_back(entry);
                }
            }
        }
    }

    std::sort(active_units.begin(), active_units.end(), [](const TurnEntry &a, const TurnEntry &b) {
        if (a.initiative != b.initiative) {
            return a.initiative > b.initiative;
        }
        return a.unit->get_dexterity() > b.unit->get_dexterity();
    });

    turn_queue.insert(turn_queue.end(), active_units.begin(), active_units.end());
    turn_queue.insert(turn_queue.end(), environment_units.begin(), environment_units.end());

    event_bus->bus_emit("combat_started", Array::make(round_number));

    if (!turn_queue.empty()) {
        next_turn();
    }
}

void Core::add_to_queue(Ref<Unit> unit)
{
    if (unit.is_valid()) {
        TurnEntry entry;
        entry.unit = unit;
        unit->set_core(this);
        unit->set_board(&board);
        unit->ready();
        turn_queue.push_back(entry);
    }
}

void Core::ask_next_turn()
{
    if(get_current_unit()->get_type()==0){
        next_turn();
    }
}

void Core::next_turn()
{
    if (!in_combat || turn_queue.empty()) return;

    bool found_player = false;
    size_t processed_count = 0;
    size_t total_units = turn_queue.size();

    while (!found_player && processed_count < total_units) {

        current_turn_index++;
        processed_count++;

        if (current_turn_index >= total_units) {
            current_turn_index = 0;
            round_number++;
            event_bus->bus_emit("round_changed", Array::make(round_number));
        }

        TurnEntry &current_entry = turn_queue[current_turn_index];
        Ref<Unit> current_unit = current_entry.unit;

        if (current_unit.is_null()) {
            continue;
        }

        if (current_unit->get_type() == 1){
            current_unit->reset_speed();
            event_bus->bus_emit("turn_changed", Array::make(current_unit));
            current_unit->execute_turn();
            continue;
        } else if (current_unit->get_type() == 2) {
            current_unit->execute_turn();
            continue;
        }

        found_player = true;
        current_unit->reset_speed();

        event_bus->bus_emit("turn_changed", Array::make(current_unit));
    }
}

Ref<Unit> Core::get_current_unit() const
{
    if (current_turn_index < turn_queue.size()) {
        return turn_queue[current_turn_index].unit;
    }
    return nullptr;
}

int Core::roll_dice(int dice_count, int dice_sides, int modifier)
{
    int total = modifier;
    for (int i = 0; i < dice_count; ++i) {
        total += (rand() % dice_sides) + 1;
    }
    return total;
}

void Core::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("_ready_cpp"), &Core::_ready);
    ClassDB::bind_method(D_METHOD("get_board"), &Core::get_board);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "board"), "", "get_board");
    ClassDB::bind_method(D_METHOD("get_event_bus"), &Core::get_event_bus);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "event_bus"), "", "get_event_bus");

    ClassDB::bind_method(D_METHOD("get_reachable_cells", "from"), &Core::get_reachable_cells);
    ClassDB::bind_method(D_METHOD("get_path", "from", "to"), &Core::get_path);
    ClassDB::bind_method(D_METHOD("move_unit", "from", "to"), &Core::move_unit);
    ClassDB::bind_method(D_METHOD("roll_dice", "count", "sides", "mod"), &Core::roll_dice);

    ClassDB::bind_method(D_METHOD("start_combat"), &Core::start_combat);
    ClassDB::bind_method(D_METHOD("add_to_queue", "unit"), &Core::add_to_queue);
    ClassDB::bind_method(D_METHOD("next_turn"), &Core::ask_next_turn);
    ClassDB::bind_method(D_METHOD("get_current_unit"), &Core::get_current_unit);
}
