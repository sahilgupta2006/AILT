#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<char>> board(3, vector<char>(3));

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> board[i][j];

    char winner = '-';

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != '-') {
            winner = board[i][0];
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] &&
            board[1][j] == board[2][j] &&
            board[0][j] != '-') {
            winner = board[0][j];
        }
    }

    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != '-') {
        winner = board[0][0];
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != '-') {
        winner = board[0][2];
    }

    if (winner != '-')
        cout << winner << " wins\n";
    else {
        bool emptyCell = false;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == '-')
                    emptyCell = true;

        if (emptyCell)
            cout << "Game continues\n";
        else
            cout << "Draw\n";
    }

    return 0;
}