#include <bits/stdc++.h>
using namespace std;

struct Node {
    int cost;
    int r, c;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

int main() {
    int n;
    cin >> n;

    vector<vector<char>> grid(n, vector<char>(n));

    pair<int,int> start, goal;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'S')
                start = {i, j};

            if (grid[i][j] == 'G')
                goal = {i, j};
        }
    }

    map<char, int> weight;

    weight['S'] = 0;
    weight['R'] = 1;
    weight['M'] = 3;
    weight['T'] = 5;
    weight['G'] = 1;

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    vector<vector<int>> dist(
        n, vector<int>(n, INT_MAX)
    );

    vector<vector<pair<int,int>>> parent(
        n, vector<pair<int,int>>(n, {-1, -1})
    );

    vector<pair<int,int>> expanded;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    dist[start.first][start.second] = 0;

    pq.push({
        0,
        start.first,
        start.second
    });

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.cost != dist[cur.r][cur.c])
            continue;

        expanded.push_back({cur.r, cur.c});

        if (make_pair(cur.r, cur.c) == goal)
            break;

        for (int k = 0; k < 4; k++) {
            int nr = cur.r + dx[k];
            int nc = cur.c + dy[k];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                continue;

            if (grid[nr][nc] == 'X')
                continue;

            int newCost =
                cur.cost + weight[grid[nr][nc]];

            if (newCost < dist[nr][nc]) {
                dist[nr][nc] = newCost;
                parent[nr][nc] = {cur.r, cur.c};

                pq.push({
                    newCost,
                    nr,
                    nc
                });
            }
        }
    }

    cout << "--- Uniform Cost Search ---\n";

    cout << "Expanded states:\n";

    for (auto [r, c] : expanded)
        cout << "(" << r << ", " << c << ") ";

    cout << "\n";

    if (dist[goal.first][goal.second] == INT_MAX) {
        cout << "No path exists\n";
        return 0;
    }

    vector<pair<int,int>> path;

    pair<int,int> cur = goal;

    while (cur != make_pair(-1, -1)) {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }

    reverse(path.begin(), path.end());

    cout << "Minimum-cost route:\n";

    for (int i = 0; i < (int)path.size(); i++) {
        cout << "(" << path[i].first << ", "
             << path[i].second << ")";

        if (i + 1 < (int)path.size())
            cout << " -> ";
    }

    cout << "\n";

    cout << "Total movements: "
         << path.size() - 1 << "\n";

    cout << "Total path cost: "
         << dist[goal.first][goal.second] << "\n";

    return 0;
}