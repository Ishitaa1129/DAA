#include <iostream>
#include <vector>
#include <limits>

#define ROW 5
#define COL 5

using namespace std;

struct Cell {
    int row;
    int col;
};

int isValid(const Cell& cell) {
    return (cell.row >= 0) && (cell.row < ROW) && (cell.col >= 0) && (cell.col < COL);
}

int isBlocked(const vector<vector<int>>& maze, const Cell& cell) {
    return maze[cell.row][cell.col] == 1;
}

int minDistance(const vector<int>& dist, const vector<int>& visited) {
    int min = numeric_limits<int>::max();
    int min_index;
    for (int v = 0; v < ROW * COL; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printPath(const vector<int>& parent, int dest) {
    if (parent[dest] == -1)
        return;
    printPath(parent, parent[dest]);
    cout << "(" << dest / COL << ", " << dest % COL << ") ";
}

void dijkstra(const vector<vector<int>>& maze, int src, int dest) {
    vector<int> dist(ROW * COL, numeric_limits<int>::max());
    vector<int> parent(ROW * COL, -1);
    vector<int> visited(ROW * COL, 0);

    dist[src] = 0;

    for (int count = 0; count < ROW * COL - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        if (u == dest)
            break;

        int row = u / COL;
        int col = u % COL;
        Cell current{row, col};
        Cell adjacent;

        // Move up
        adjacent.row = current.row - 1;
        adjacent.col = current.col;
        if (isValid(adjacent) && !isBlocked(maze, adjacent) && !visited[adjacent.row * COL + adjacent.col] && dist[u] + 1 < dist[adjacent.row * COL + adjacent.col]) {
            dist[adjacent.row * COL + adjacent.col] = dist[u] + 1;
            parent[adjacent.row * COL + adjacent.col] = u;
        }

        // Move down
        adjacent.row = current.row + 1;
        adjacent.col = current.col;
        if (isValid(adjacent) && !isBlocked(maze, adjacent) && !visited[adjacent.row * COL + adjacent.col] && dist[u] + 1 < dist[adjacent.row * COL + adjacent.col]) {
            dist[adjacent.row * COL + adjacent.col] = dist[u] + 1;
            parent[adjacent.row * COL + adjacent.col] = u;
        }

        // Move left
        adjacent.row = current.row;
        adjacent.col = current.col - 1;
        if (isValid(adjacent) && !isBlocked(maze, adjacent) && !visited[adjacent.row * COL + adjacent.col] && dist[u] + 1 < dist[adjacent.row * COL + adjacent.col]) {
            dist[adjacent.row * COL + adjacent.col] = dist[u] + 1;
            parent[adjacent.row * COL + adjacent.col] = u;
        }

        // Move right
                adjacent.row = current.row;
        adjacent.col = current.col + 1;
        if (isValid(adjacent) && !isBlocked(maze, adjacent) && !visited[adjacent.row * COL + adjacent.col] && dist[u] + 1 < dist[adjacent.row * COL + adjacent.col]) {
            dist[adjacent.row * COL + adjacent.col] = dist[u] + 1;
            parent[adjacent.row * COL + adjacent.col] = u;
        }
    }

    if (parent[dest] == -1) {
        cout << "No path exists" << endl;
        return;
    }

    cout << "Path: ";
    printPath(parent, dest);
    cout << endl;
    cout << "Distance: " << dist[dest] << endl;
}

int main() {
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0}
    };

    int src = 0, dest = 24;
    dijkstra(maze, src, dest);

    return 0;
}
