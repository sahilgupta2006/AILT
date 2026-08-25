#include <bits/stdc++.h>
using namespace std;

struct Node {
    double cost;
    int r, c;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

vector<pair<int,int>> reconstruct(
    vector<vector<pair<int,int>>> &parent,
    pair<int,int> goal
) {
    vector<pair<int,int>> path;

    pair<int,int> cur = goal;

    while (cur != make_pair(-1, -1)) {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }

    reverse(path.begin(), path.end());

    return path;
}

vector<pair<int,int>> bfs(
    vector<vector<char>> &grid,
    pair<int,int> start,
    pair<int,int> goal
) {
    int n = grid.size();

    queue<pair<int,int>> q;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<vector<pair<int,int>>> parent(
        n, vector<pair<int,int>>(n, {-1, -1})
    );

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    q.push(start);
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (make_pair(r, c) == goal)
            return reconstruct(parent, goal);

        for (int k = 0; k < 4; k++) {
            int nr = r + dx[k];
            int nc = c + dy[k];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                continue;

            if (visited[nr][nc])
                continue;

            if (grid[nr][nc] == 'X')
                continue;

            visited[nr][nc] = true;
            parent[nr][nc] = {r, c};
            q.push({nr, nc});
        }
    }

    return {};
}

vector<pair<int,int>> utilitySearch(
    vector<vector<char>> &grid,
    pair<int,int> start,
    pair<int,int> goal,
    vector<vector<double>> &energy,
    vector<vector<double>> &risk,
    vector<vector<double>> &traffic
) {
    int n = grid.size();

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    vector<vector<double>> dist(
        n, vector<double>(n, 1e18)
    );

    vector<vector<pair<int,int>>> parent(
        n, vector<pair<int,int>>(n, {-1, -1})
    );

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    dist[start.first][start.second] = 0;
    pq.push({0, start.first, start.second});

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        int r = cur.r;
        int c = cur.c;

        if (cur.cost > dist[r][c])
            continue;

        if (make_pair(r, c) == goal)
            return reconstruct(parent, goal);

        for (int k = 0; k < 4; k++) {
            int nr = r + dx[k];
            int nc = c + dy[k];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                continue;

            if (grid[nr][nc] == 'X')
                continue;

            double stepCost =
                0.4 +
                0.3 * energy[nr][nc] +
                0.2 * risk[nr][nc] +
                0.1 * traffic[nr][nc];

            double newCost = cur.cost + stepCost;

            if (newCost < dist[nr][nc]) {
                dist[nr][nc] = newCost;
                parent[nr][nc] = {r, c};
                pq.push({newCost, nr, nc});
            }
        }
    }

    return {};
}

double routeCost(
    vector<pair<int,int>> &path,
    vector<vector<double>> &energy,
    vector<vector<double>> &risk,
    vector<vector<double>> &traffic
) {
    double distance = path.size() - 1;
    double e = 0;
    double r = 0;
    double t = 0;

    for (auto [x, y] : path) {
        e += energy[x][y];
        r += risk[x][y];
        t += traffic[x][y];
    }

    return 0.4 * distance + 0.3 * e + 0.2 * r + 0.1 * t;
}

void printPath(vector<pair<int,int>> path) {
    for (int i = 0; i < (int)path.size(); i++) {
        cout << "(" << path[i].first << ", " << path[i].second << ")";

        if (i + 1 < (int)path.size())
            cout << " -> ";
    }

    cout << '\n';
}

int main() {
    int n;
    cin >> n;

    vector<vector<char>> grid(n, vector<char>(n));

    pair<int,int> start, pickup, goal;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'S')
                start = {i, j};

            if (grid[i][j] == 'P')
                pickup = {i, j};

            if (grid[i][j] == 'G')
                goal = {i, j};
        }
    }

    vector<vector<double>> energy(n, vector<double>(n));
    vector<vector<double>> risk(n, vector<double>(n));
    vector<vector<double>> traffic(n, vector<double>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> energy[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> risk[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> traffic[i][j];

    vector<pair<int,int>> goalToPickup =
        bfs(grid, start, pickup);

    vector<pair<int,int>> goalToDestination =
        bfs(grid, pickup, goal);

    cout << "--- Goal-Based Agent ---\n";

    if (goalToPickup.empty() || goalToDestination.empty()) {
        cout << "No path exists\n";
    } else {
        cout << "Route to Package: ";
        printPath(goalToPickup);

        cout << "Movements to Package: "
             << goalToPickup.size() - 1 << '\n';

        cout << "Route to Destination: ";
        printPath(goalToDestination);

        cout << "Movements to Destination: "
             << goalToDestination.size() - 1 << '\n';

        cout << "Total Movements: "
             << goalToPickup.size() - 1 +
                goalToDestination.size() - 1 << '\n';
    }

    vector<pair<int,int>> utilityToPickup =
        utilitySearch(
            grid, start, pickup,
            energy, risk, traffic
        );

    vector<pair<int,int>> utilityToDestination =
        utilitySearch(
            grid, pickup, goal,
            energy, risk, traffic
        );

    cout << "\n--- Utility-Based Agent ---\n";

    if (utilityToPickup.empty() || utilityToDestination.empty()) {
        cout << "No path exists\n";
    } else {
        cout << "Route to Package: ";
        printPath(utilityToPickup);

        cout << "Route to Destination: ";
        printPath(utilityToDestination);

        int totalMovements =
            (int)utilityToPickup.size() - 1 +
            (int)utilityToDestination.size() - 1;

        double totalCost =
            routeCost(
                utilityToPickup,
                energy,
                risk,
                traffic
            ) +
            routeCost(
                utilityToDestination,
                energy,
                risk,
                traffic
            );

        cout << "Total Movements: "
             << totalMovements << '\n';

        cout << fixed << setprecision(2);

        cout << "Total Cost: "
             << totalCost << '\n';
    }

    return 0;
}