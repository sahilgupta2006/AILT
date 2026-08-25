#include <bits/stdc++.h>
using namespace std;

struct Result {
    int cleaned;
    int movements;
    int actions;
    int repeated;
    vector<vector<char>> grid;
};

Result simpleReflex(vector<vector<char>> grid, pair<int,int> start) {
    int n = grid.size();

    int r = start.first;
    int c = start.second;

    int dirty = 0;
    int cleaned = 0;
    int movements = 0;
    int actions = 0;

    vector<vector<int>> visits(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == 'D')
                dirty++;

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};

    while (cleaned < dirty && movements < 1000) {
        visits[r][c]++;

        if (grid[r][c] == 'D') {
            grid[r][c] = 'C';
            cleaned++;
            actions++;
            continue;
        }

        bool moved = false;

        for (int k = 0; k < 4; k++) {
            int nr = r + dx[k];
            int nc = c + dy[k];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                continue;

            if (grid[nr][nc] == 'X')
                continue;

            r = nr;
            c = nc;
            movements++;
            actions++;
            moved = true;
            break;
        }

        if (!moved)
            break;
    }

    int repeated = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (visits[i][j] > 1)
                repeated += visits[i][j] - 1;

    return {cleaned, movements, actions, repeated, grid};
}

Result modelBased(vector<vector<char>> grid, pair<int,int> start) {
    int n = grid.size();

    int r = start.first;
    int c = start.second;

    int dirty = 0;
    int cleaned = 0;
    int movements = 0;
    int actions = 0;

    vector<vector<int>> visits(n, vector<int>(n, 0));
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<vector<bool>> cleanedCell(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == 'D')
                dirty++;

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};

    while (cleaned < dirty && movements < 1000) {
        visits[r][c]++;
        visited[r][c] = true;

        if (grid[r][c] == 'D') {
            grid[r][c] = 'C';
            cleanedCell[r][c] = true;
            cleaned++;
            actions++;
            continue;
        }

        bool moved = false;

        for (int k = 0; k < 4; k++) {
            int nr = r + dx[k];
            int nc = c + dy[k];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                continue;

            if (grid[nr][nc] == 'X')
                continue;

            if (!visited[nr][nc]) {
                r = nr;
                c = nc;
                movements++;
                actions++;
                moved = true;
                break;
            }
        }

        if (!moved) {
            for (int k = 0; k < 4; k++) {
                int nr = r + dx[k];
                int nc = c + dy[k];

                if (nr < 0 || nr >= n || nc < 0 || nc >= n)
                    continue;

                if (grid[nr][nc] == 'X')
                    continue;

                r = nr;
                c = nc;
                movements++;
                actions++;
                moved = true;
                break;
            }
        }

        if (!moved)
            break;
    }

    int repeated = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (visits[i][j] > 1)
                repeated += visits[i][j] - 1;

    return {cleaned, movements, actions, repeated, grid};
}

int main() {
    int n;
    cin >> n;

    vector<vector<char>> grid(n, vector<char>(n));
    pair<int,int> start;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'S')
                start = {i, j};
        }
    }

    Result simple = simpleReflex(grid, start);
    Result model = modelBased(grid, start);

    cout << "--- Simple Reflex Agent ---\n";
    cout << "Dirty cells cleaned: " << simple.cleaned << "\n";
    cout << "Movements: " << simple.movements << "\n";
    cout << "Total actions: " << simple.actions << "\n";
    cout << "Repeated visits: " << simple.repeated << "\n";

    cout << "\nFinal Grid:\n";

    for (auto &row : simple.grid) {
        for (char x : row)
            cout << x << ' ';
        cout << '\n';
    }

    cout << "\n--- Model-Based Reflex Agent ---\n";
    cout << "Dirty cells cleaned: " << model.cleaned << "\n";
    cout << "Movements: " << model.movements << "\n";
    cout << "Total actions: " << model.actions << "\n";
    cout << "Repeated visits: " << model.repeated << "\n";

    cout << "\nFinal Grid:\n";

    for (auto &row : model.grid) {
        for (char x : row)
            cout << x << ' ';
        cout << '\n';
    }

    return 0;
}