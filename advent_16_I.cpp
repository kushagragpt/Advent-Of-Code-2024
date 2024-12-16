#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <map>
#include <set>
using namespace std;

struct State {
    int x, y, dir, cost;
    bool operator<(const State& other) const {
        return cost > other.cost; // Priority queue: smallest cost first
    }
};

const int INF = 1e9;
const vector<pair<int, int>> directions = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}}; // E, N, W, S

int find_min_cost(const vector<string>& maze) {
    int rows = maze.size(), cols = maze[0].size();
    int start_x = 0, start_y = 0, end_x = 0, end_y = 0;

    // Locate S and E
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 'S') {
                start_x = i;
                start_y = j;
            }
            if (maze[i][j] == 'E') {
                end_x = i;
                end_y = j;
            }
        }
    }

    priority_queue<State> pq;
    map<tuple<int, int, int>, int> dist; // ((x, y, dir) -> cost)

    // Initial state: Start facing East (direction 0)
    pq.push({start_x, start_y, 0, 0});
    dist[make_tuple(start_x, start_y, 0)] = 0;

    while (!pq.empty()) {
        // Extract the state with the minimum cost
        State current = pq.top();
        pq.pop();

        int x = current.x;
        int y = current.y;
        int dir = current.dir;
        int cost = current.cost;

        // If at the endpoint, return the cost
        if (x == end_x && y == end_y) {
            return cost;
        }

        // Skip if we already found a better way
        if (dist[make_tuple(x, y, dir)] < cost) {
            continue;
        }

        // Move forward in the current direction
        int nx = x + directions[dir].first;
        int ny = y + directions[dir].second;
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] != '#') {
            int new_cost = cost + 1;
            tuple<int, int, int> forward_state = make_tuple(nx, ny, dir);
            if (dist.find(forward_state) == dist.end() || dist[forward_state] > new_cost) {
                dist[forward_state] = new_cost;
                pq.push({nx, ny, dir, new_cost});
            }
        }

        // Rotate clockwise or counterclockwise
        for (int d = -1; d <= 1; d += 2) { // -1: counterclockwise, +1: clockwise
            int new_dir = (dir + d + 4) % 4;
            int new_cost = cost + 1000;
            tuple<int, int, int> rotated_state = make_tuple(x, y, new_dir);
            if (dist.find(rotated_state) == dist.end() || dist[rotated_state] > new_cost) {
                dist[rotated_state] = new_cost;
                pq.push({x, y, new_dir, new_cost});
            }
        }
    }

    return -1; // No path found
}

int main() {
    vector<string> maze (140);
        
    
    for(int i=0;i<140;i++) cin>>maze[i];

    cout << "Minimum cost: " << find_min_cost(maze) << endl;
    return 0;
}
