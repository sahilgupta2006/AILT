#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> grid;
int n;
pair<int,int> goal;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool valid(int r, int c) {
    return r >= 0 &&
           r < n &&
           c >= 0 &&
           c < n &&
           grid[r][c] != 'X';
}

string dls(
    pair<int,int> node,
    int limit,
    vector<pair<int,int>>& path,
    vector<pair<int,int>>& expanded
) {
    expanded.push_back(node);

    if (node == goal)
        return "SUCCESS";

    if ((int)path.size() - 1 == limit)
        return "CUTOFF";

    bool cutoffOccurred = false;

    for (int k = 0; k < 4; k++) {
        int nr = node.first + dx[k];
        int nc = node.second + dy[k];

        if (!valid(nr, nc))
            continue;

        pair<int,int> next = {nr, nc};

        if (find(path.begin(), path.end(), next) != path.end())
            continue;

        path.push_back(next);

        string result = dls(
            next,
            limit,
            path,
            expanded
        );

        if (result == "SUCCESS")
            return "SUCCESS";

        if (result == "CUTOFF")
            cutoffOccurred = true;

        path.pop_back();
    }

    if (cutoffOccurred)
        return "CUTOFF";

    return "FAILURE";
}

void runDLS(
    pair<int,int> start,
    int limit
) {
    vector<pair<int,int>> path;
    vector<pair<int,int>> expanded;

    path.push_back(start);

    string result = dls(
        start,
        limit,
        path,
        expanded
    );

    cout << "--- Depth-Limited Search: Limit = "
         << limit << " ---\n";

    cout << "Expanded states:\n";

    for (auto [r, c] : expanded)
        cout << "(" << r << ", " << c << ") ";

    cout << "\n";

    if (result == "SUCCESS") {
        cout << "Result: SUCCESS\n";
        cout << "Route:\n";

        for (int i = 0; i < (int)path.size(); i++) {
            cout << "(" << path[i].first
                 << ", " << path[i].second << ")";

            if (i + 1 < (int)path.size())
                cout << " -> ";
        }

        cout << "\n";

        cout << "Solution depth / movements: "
             << path.size() - 1 << "\n";
    } else if (result == "CUTOFF") {
        cout << "Result: CUTOFF / Goal not found within depth limit\n";
        cout << "Maximum allowed depth: "
             << limit << "\n";
    } else {
        cout << "Result: FAILURE / Goal does not exist in reachable space\n";
    }

    cout << "\n";
}

int main() {
    cin >> n;

    grid.assign(n, vector<char>(n));

    pair<int,int> start;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'S')
                start = {i, j};

            if (grid[i][j] == 'G')
                goal = {i, j};
        }
    }

    int limit1, limit2;

    cin >> limit1 >> limit2;

    runDLS(start, limit1);
    runDLS(start, limit2);

    return 0;
}