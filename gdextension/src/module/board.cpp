#include "board.h"
#include <queue>

using namespace godot;

Board::Board() {
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            Ref<Cell> cell;
            cell.instantiate();
            cells[x][y] = cell;
        }
    }
}

Board::~Board()
{

}

Ref<Cell> Board::get_cell(int x, int y) const
{
    return cells[x][y];
}

Ref<Cell> Board::get_cell(Vector2i pos) const
{
    return cells[pos.x][pos.y];
}

void Board::set_cell(int x, int y, const Ref<Cell> &cell)
{
    cells[x][y] = cell;
}

Ref<Unit> Board::get_unit(int x, int y) const
{
    return units[x][y];
}

Ref<Unit> Board::get_unit(Vector2i pos) const
{
    return units[pos.x][pos.y];
}

void Board::set_unit(int x, int y, const Ref<Unit> &unit)
{
    units[x][y] = unit;
    unit->set_position(Vector2i(x,y));
}

Array Board::get_reachable_cells(Vector2i from)
{
    Array result;

    Ref<Unit> unit = get_unit(from.x, from.y);
    int max_dist = unit->get_current_speed();
    if (max_dist <= 0) return result;

    std::vector<std::vector<int>> dist(WIDTH, std::vector<int>(HEIGHT, -1));
    std::queue<Vector2i> q;

    q.push(from);
    dist[from.x][from.y] = 0;

    const int dx[] = { 1, -1,  0,  0,  1,  1, -1, -1 };
    const int dy[] = { 0,  0,  1, -1,  1, -1,  1, -1 };

    while (!q.empty()) {
        Vector2i curr = q.front();
        q.pop();

        int d = dist[curr.x][curr.y];

        if (d >= max_dist) continue;

        for (int i = 0; i < 8; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (!is_valid_coord(nx, ny)) continue;

            if (units[nx][ny] != nullptr && !(nx == from.x && ny == from.y)) continue;

            if (dist[nx][ny] == -1) {
                dist[nx][ny] = d + 1;
                result.append(Vector2i(nx, ny));
                q.push(Vector2i(nx, ny));
            }
        }
    }

    return result;
}

Array Board::get_path(Vector2i from, Vector2i to)
{
    Array path;

    // if (!is_valid_coord(from.x, from.y) || !is_valid_coord(to.x, to.y)) return path;
    // if (units[from.x][from.y] == nullptr) return path;

    Ref<Unit> unit = get_unit(from.x, from.y);
    int max_dist = unit->get_current_speed();
    if (max_dist <= 0) return path;

    std::vector<std::vector<Vector2i>> parent(WIDTH, std::vector<Vector2i>(HEIGHT, Vector2i(-1, -1)));
    std::vector<std::vector<int>> dist(WIDTH, std::vector<int>(HEIGHT, -1));
    std::queue<Vector2i> q;

    q.push(from);
    dist[from.x][from.y] = 0;

    const int dx[] = { 1, -1,  0,  0,  1,  1, -1, -1 };
    const int dy[] = { 0,  0,  1, -1,  1, -1,  1, -1 };

    bool reached = false;

    while (!q.empty()) {
        Vector2i curr = q.front();
        q.pop();

        if (curr == to) {
            reached = true;
            break;
        }

        int d = dist[curr.x][curr.y];
        if (d >= max_dist) continue;

        for (int i = 0; i < 8; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (!is_valid_coord(nx, ny)) continue;
            if (units[nx][ny] != nullptr && !(nx == from.x && ny == from.y)) continue;

            if (dist[nx][ny] == -1) {
                dist[nx][ny] = d + 1;
                parent[nx][ny] = curr;
                q.push(Vector2i(nx, ny));
            }
        }
    }

    if (!reached) return path;

    Vector2i curr = to;
    while (curr != from) {
        path.push_back(curr);
        curr = parent[curr.x][curr.y];
    }

    path.reverse();

    return path;
}

bool Board::move_unit(Vector2i from, Vector2i to)
{
    if (!is_valid_coord(from.x, from.y) || !is_valid_coord(to.x, to.y)) {
        return false;
    }

    if (get_unit(from.x, from.y) == nullptr || get_unit(to.x, to.y) != nullptr) {
        return false;
    }

    Ref<Unit> unit = get_unit(from.x, from.y);
    int current_speed = unit->get_current_speed();

    std::vector<std::vector<int>> dist(WIDTH, std::vector<int>(HEIGHT, -1));
    std::queue<Vector2i> q;

    q.push(from);
    dist[from.x][from.y] = 0;

    const int dx[] = { 1, -1,  0,  0,  1,  1, -1, -1 };
    const int dy[] = { 0,  0,  1, -1,  1, -1,  1, -1 };

    while (!q.empty()) {
        Vector2i curr = q.front();
        q.pop();

        if (curr == to) break;

        for (int i = 0; i < 8; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (!is_valid_coord(nx, ny)) continue;
            if (units[nx][ny] != nullptr && !(nx == from.x && ny == from.y)) continue;

            if (dist[nx][ny] == -1) {
                dist[nx][ny] = dist[curr.x][curr.y] + 1;
                q.push(Vector2i(nx, ny));
            }
        }
    }

    int path_cost = dist[to.x][to.y];

    if (path_cost == -1 || path_cost > current_speed) return false;

    units[to.x][to.y] = units[from.x][from.y];
    units[from.x][from.y] = Ref<Unit>();

    units[to.x][to.y]->set_position(Vector2i(to.x, to.y));

    unit->set_current_speed(current_speed - path_cost);

    return true;
}

bool Board::is_valid_coord(int x, int y)
{
    return (x>=0 && x<WIDTH) && (y>=0 && y<HEIGHT);
}

Vector2 Board::get_board_size()
{
    return Vector2(WIDTH, HEIGHT);
}

Array Board::get_cells_arrey() const
{
    Array ret;
    for (int x = 0; x < WIDTH; ++x) {
        Array w;
        for (int y = 0; y < HEIGHT; ++y) {
            w.push_back(get_cell(x,y));
        }
        ret.append_array(w);
    }
    return ret;
}

Array Board::get_units_arrey() const
{
    Array ret;
    for (int x = 0; x < WIDTH; ++x) {
        Array w;
        for (int y = 0; y < HEIGHT; ++y) {
            w.push_back(get_unit(x,y));
        }
        ret.append_array(w);
    }
    return ret;
}

void Board::_bind_methods()
{
    ClassDB::bind_method(
        D_METHOD("get_cell", "x", "y"),
        static_cast<Ref<Cell> (Board::*)(int, int) const>(&Board::get_cell)
        );

    ClassDB::bind_method(
        D_METHOD("get_cellv", "pos"),
        static_cast<Ref<Cell> (Board::*)(Vector2i) const>(&Board::get_cell)
        );
    ClassDB::bind_method(D_METHOD("set_cell", "x", "y", "cell"), &Board::set_cell);
    ClassDB::bind_method(D_METHOD("get_cells_arrey"), &Board::get_cells_arrey);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "cells"), "", "get_cells_arrey");

    ClassDB::bind_method(
        D_METHOD("get_unit", "x", "y"),
        static_cast<Ref<Unit> (Board::*)(int, int) const>(&Board::get_unit)
        );

    ClassDB::bind_method(
        D_METHOD("get_unitv", "pos"),
        static_cast<Ref<Unit> (Board::*)(Vector2i) const>(&Board::get_unit)
        );
    ClassDB::bind_method(D_METHOD("set_unit", "x", "y", "unit"), &Board::set_unit);
    ClassDB::bind_method(D_METHOD("get_units_arrey"), &Board::get_units_arrey);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "units"), "", "get_units_arrey");

    ClassDB::bind_method(D_METHOD("get_reachable_cells", "from"), &Board::get_reachable_cells);
    ClassDB::bind_method(D_METHOD("move_unit", "from", "to"), &Board::move_unit);

    ClassDB::bind_method(D_METHOD("is_valid_coord", "x", "y"), &Board::is_valid_coord);
    ClassDB::bind_method(D_METHOD("get_board_size"), &Board::get_board_size);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "board_size"), "", "get_board_size");
}
