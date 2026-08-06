#include "helper.h"
#include "constants.h"
#include "module/board.h"
#include <queue>

using namespace godot;

Helper::Helper() { }

Array Helper::get_line_target(Ref<Board> board, Vector2i start_pos, int radius, int target_type)
{
    Array result;
    if (board.is_null() || radius <= 0) return result;
    if (!board->is_valid_coord(start_pos.x, start_pos.y)) return result;

    bool visited[WIDTH][HEIGHT] = {};

    auto process_cell = [&](int x, int y) -> bool {
        if (!board->is_valid_coord(x, y)) return false;
        if (x == start_pos.x && y == start_pos.y) return true;
        if (visited[x][y]) return true;

        Ref<Unit> u = board->get_unit(x, y);
        bool has_unit = u.is_valid();

        if (target_type == TARGET_EMPTY) {
            if (!has_unit) {
                result.append(Vector2i(x, y));
                visited[x][y] = true;
                return true; // пусто — луч летит дальше
            }
            return false; // любой юнит блокирует
        } else if (target_type == TARGET_ANY) {
            if (has_unit) {
                result.append(Vector2i(x, y));
                visited[x][y] = true;
                return false; // блок
            }
            return true; // пусто — дальше
        } else {
            if (has_unit && u->get_type() == target_type) {
                result.append(Vector2i(x, y));
                visited[x][y] = true;
                return false; // нашли нужного — блок
            }
            if (has_unit) return false; // другой юнит тоже блокирует луч
            return true; // пусто — дальше
        }
    };

    auto trace_line = [&](int x2, int y2) {
        int x1 = start_pos.x, y1 = start_pos.y;
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        int x = x1, y = y1;
        while (true) {
            if (x == x2 && y == y2) {
                process_cell(x, y);
                break;
            }
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x += sx; }
            if (e2 < dx)  { err += dx; y += sy; }
            if (x == start_pos.x && y == start_pos.y) continue;
            if (!process_cell(x, y)) break;
        }
    };

    // Периметр квадрата
    for (int d = -radius; d <= radius; ++d) {
        trace_line(start_pos.x + d, start_pos.y - radius);
        trace_line(start_pos.x + d, start_pos.y + radius);
    }
    for (int d = -radius + 1; d <= radius - 1; ++d) {
        trace_line(start_pos.x - radius, start_pos.y + d);
        trace_line(start_pos.x + radius, start_pos.y + d);
    }

    return result;
}

Array Helper::get_bfs_target(Ref<Board> board, Vector2i start_pos, int radius, int target_type) {
    Array result;
    if (board.is_null() || radius <= 0) return result;
    if (!board->is_valid_coord(start_pos.x, start_pos.y)) return result;

    bool visited[WIDTH][HEIGHT] = {};
    std::queue<std::pair<Vector2i, int>> q;
    q.push({start_pos, 0});
    visited[start_pos.x][start_pos.y] = true;

    const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};

    while (!q.empty()) {
        auto [curr, dist] = q.front(); q.pop();
        if (dist >= radius) continue;

        for (int i = 0; i < 8; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (!board->is_valid_coord(nx, ny)) continue;
            if (visited[nx][ny]) continue;

            visited[nx][ny] = true;
            Ref<Unit> u = board->get_unit(nx, ny);
            bool has_unit = u.is_valid();

            if (has_unit) {
                // Юнит блокирует проход, но может быть целью
                if (target_type == TARGET_ANY) {
                    result.append(Vector2i(nx, ny));
                } else if (target_type >= 0 && u->get_type() == target_type) {
                    result.append(Vector2i(nx, ny));
                }
                // Через юнита НЕ идём дальше — не пушим в очередь
            } else {
                // Пустая клетка — проходима
                if (target_type == TARGET_EMPTY) {
                    result.append(Vector2i(nx, ny));
                }
                q.push({Vector2i(nx, ny), dist + 1});
            }
        }
    }

    return result;
}

Array Helper::get_bfs_target_path(Ref<Board> board, Vector2i start_pos, int radius, Vector2i end_pos)
{
    Array path;
    if (board.is_null() || radius <= 0) return path;
    if (!board->is_valid_coord(start_pos.x, start_pos.y)) return path;
    if (!board->is_valid_coord(end_pos.x, end_pos.y)) return path;

    Vector2i parent[WIDTH][HEIGHT];
    for (int x = 0; x < WIDTH; ++x)
        for (int y = 0; y < HEIGHT; ++y)
            parent[x][y] = Vector2i(-1, -1);

    std::queue<std::pair<Vector2i, int>> q;
    q.push({start_pos, 0});
    parent[start_pos.x][start_pos.y] = start_pos;

    const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};

    bool found = false;

    while (!q.empty()) {
        auto [curr, dist] = q.front(); q.pop();
        if (curr == end_pos) { found = true; break; }
        if (dist >= radius) continue;

        for (int i = 0; i < 8; ++i) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (!board->is_valid_coord(nx, ny)) continue;
            if (parent[nx][ny] != Vector2i(-1, -1)) continue;
            // Проходимы только пустые клетки (как в Board::get_path)
            if (board->get_unit(nx, ny).is_valid()) continue;

            parent[nx][ny] = curr;
            q.push({Vector2i(nx, ny), dist + 1});
        }
    }

    if (!found) return path;

    Vector2i curr = end_pos;
    while (curr != start_pos) {
        path.push_back(curr);
        curr = parent[curr.x][curr.y];
    }
    path.reverse();
    return path;
}

Array Helper::get_all_target(Ref<Board> board, Vector2i start_pos, int radius, int target_type)
{
    Array result;
    if (board.is_null() || radius <= 0) return result;

    for (int x = start_pos.x - radius; x <= start_pos.x + radius; ++x) {
        for (int y = start_pos.y - radius; y <= start_pos.y + radius; ++y) {
            if (!board->is_valid_coord(x, y)) continue;
            if (x == start_pos.x && y == start_pos.y) continue;

            Ref<Unit> u = board->get_unit(x, y);
            bool has_unit = u.is_valid();

            if (target_type == TARGET_EMPTY) {
                if (!has_unit) result.append(Vector2i(x, y));
            } else if (target_type == TARGET_ANY) {
                if (has_unit) result.append(Vector2i(x, y));
            } else {
                if (has_unit && u->get_type() == target_type) result.append(Vector2i(x, y));
            }
        }
    }
    return result;
}

void Helper::_bind_methods()
{
    ClassDB::bind_integer_constant(get_class_static(), "", "TARGET_EMPTY",      TargetType::TARGET_EMPTY);
    ClassDB::bind_integer_constant(get_class_static(), "", "TARGET_ANY",        TargetType::TARGET_ANY);
    ClassDB::bind_integer_constant(get_class_static(), "", "TARGET_DM_DUMMY",   TargetType::TARGET_DM_DUMMY);
    ClassDB::bind_integer_constant(get_class_static(), "", "TARGET_ADVENTURER", TargetType::TARGET_ADVENTURER);
    ClassDB::bind_integer_constant(get_class_static(), "", "TARGET_ENVIRONMENT",TargetType::TARGET_ENVIRONMENT);

    ClassDB::bind_method(D_METHOD("get_line_target", "board", "start_pos", "radius", "target_type"), &Helper::get_line_target);
    ClassDB::bind_method(D_METHOD("get_bfs_target", "board", "start_pos", "radius", "target_type"), &Helper::get_bfs_target);
    ClassDB::bind_method(D_METHOD("get_bfs_target_path", "board", "start_pos", "radius", "end_pos"), &Helper::get_bfs_target_path);
    ClassDB::bind_method(D_METHOD("get_all_target", "board", "start_pos", "radius", "target_type"), &Helper::get_all_target);
}
