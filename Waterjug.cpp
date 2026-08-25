#include <bits/stdc++.h>
using namespace std;

int main() {
    pair<int,int> start = {0, 0};

    queue<pair<int,int>> q;
    map<pair<int,int>, bool> visited;
    map<pair<int,int>, pair<int,int>> parent;
    map<pair<int,int>, string> action;

    q.push(start);
    visited[start] = true;
    parent[start] = {-1, -1};

    pair<int,int> goal = {-1, -1};

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        int a = cur.first;
        int b = cur.second;

        if (a == 2) {
            goal = cur;
            break;
        }

        vector<pair<pair<int,int>, string>> next;

        next.push_back({{4, b}, "Fill 4L jug"});
        next.push_back({{a, 3}, "Fill 3L jug"});
        next.push_back({{0, b}, "Empty 4L jug"});
        next.push_back({{a, 0}, "Empty 3L jug"});

        int pour = min(a, 3 - b);
        next.push_back({
            {a - pour, b + pour},
            "Pour 4L -> 3L"
        });

        pour = min(b, 4 - a);
        next.push_back({
            {a + pour, b - pour},
            "Pour 3L -> 4L"
        });

        for (auto &x : next) {
            auto state = x.first;

            if (!visited[state]) {
                visited[state] = true;
                parent[state] = cur;
                action[state] = x.second;
                q.push(state);
            }
        }
    }

    if (goal.first == -1) {
        cout << "No solution\n";
        return 0;
    }

    vector<pair<int,int>> path;
    vector<string> actions;

    pair<int,int> cur = goal;

    while (cur != start) {
        path.push_back(cur);
        actions.push_back(action[cur]);
        cur = parent[cur];
    }

    path.push_back(start);

    reverse(path.begin(), path.end());
    reverse(actions.begin(), actions.end());

    for (int i = 0; i < (int)path.size(); i++) {
        cout << "(" << path[i].first << ", " << path[i].second << ")";

        if (i + 1 < (int)path.size())
            cout << " -> ";
    }

    cout << "\n\n";

    for (int i = 0; i < (int)actions.size(); i++) {
        cout << actions[i] << "\n";
    }

    cout << "\nMinimum number of steps: "
         << path.size() - 1 << "\n";

    return 0;
}