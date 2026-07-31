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

Ref<Cell> Board::get_cell(int x, int y) const
{
    return cells[x][y];
}

void Board::set_cell(int x, int y, const Ref<Cell> &cell)
{
    cells[x][y] = cell;
}

Ref<Unit> Board::get_unit(int x, int y) const
{
    return units[x][y];
}

void Board::set_unit(int x, int y, const Ref<Unit> &unit)
{
    units[x][y] = unit;
}

Array Board::get_reachable_cells(Vector2i from)
{
    Array result;

    if (!is_valid_coord(from.x, from.y) || units[from.x][from.y] == nullptr) {
        return result;
    }

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

        for (int i = 0; i < 8; ++i) { // ← Изменено с 4 на 8
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (!is_valid_coord(nx, ny)) continue;

            // Не проходим сквозь занятые клетки (кроме стартовой)
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

bool Board::move_unit(Vector2i from, Vector2i to)
{
    if (!is_valid_coord(from.x, from.y) || !is_valid_coord(to.x, to.y)) return false;

    if (units[from.x][from.y] == nullptr || units[to.x][to.y] != nullptr) return false;

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

void Board::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_cell", "x", "y"), &Board::get_cell);
    ClassDB::bind_method(D_METHOD("set_cell", "x", "y", "cell"), &Board::set_cell);

    ClassDB::bind_method(D_METHOD("get_unit", "x", "y"), &Board::get_unit);
    ClassDB::bind_method(D_METHOD("set_unit", "x", "y", "unit"), &Board::set_unit);

    ClassDB::bind_method(D_METHOD("get_reachable_cells", "from"), &Board::get_reachable_cells);
    ClassDB::bind_method(D_METHOD("move_unit", "from", "to"), &Board::move_unit);

    ClassDB::bind_method(D_METHOD("get_board_size"), &Board::get_board_size);
}
