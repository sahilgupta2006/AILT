#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<vector<char>> grid(n, vector<char>(n));

    pair<int,int> start;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'E')
                start = {i, j};
        }
    }

    queue<pair<int,int>> q;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<vector<pair<int,int>>> parent(
        n, vector<pair<int,int>>(n, {-1, -1})
    );

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    q.push(start);
    visited[start.first][start.second] = true;

    pair<int,int> goal = {-1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (grid[x][y] == 'A') {
            goal = {x, y};
            break;
        }

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                continue;

            if (visited[nx][ny])
                continue;

            if (grid[nx][ny] != 'R' && grid[nx][ny] != 'A')
                continue;

            visited[nx][ny] = true;
            parent[nx][ny] = {x, y};
            q.push({nx, ny});
        }
    }

    if (goal.first == -1) {
        cout << "No reachable parking space\n";
        return 0;
    }

    vector<pair<int,int>> path;

    pair<int,int> cur = goal;

    while (cur != make_pair(-1, -1)) {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }

    reverse(path.begin(), path.end());

    cout << "Nearest available parking space: ("
         << goal.first << ", " << goal.second << ")\n";

    cout << "Number of movements required: "
         << path.size() - 1 << "\n";

    cout << "Route: ";

    for (int i = 0; i < (int)path.size(); i++) {
        cout << "(" << path[i].first << ", " << path[i].second << ")";
        if (i + 1 < (int)path.size())
            cout << " -> ";
    }

    cout << "\n";

    return 0;
}