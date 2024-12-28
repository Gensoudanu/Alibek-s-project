#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER = 'X';
const char AI = 'O';

void displayBoard(const vector<vector<char>>& board) {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "--+---+--\n";
    }
    cout << "\n";
}

char checkWinner(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }

    return ' ';
}

bool isDraw(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

int minimax(vector<vector<char>>& board, bool isMaximizing) {
    char winner = checkWinner(board);
    if (winner == AI) return 10;
    if (winner == PLAYER) return -10;
    if (isDraw(board)) return 0;

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    int score = minimax(board, false);
                    board[i][j] = ' ';
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    int score = minimax(board, true);
                    board[i][j] = ' ';
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestScore = numeric_limits<int>::min();
    pair<int, int> bestMove = { -1, -1 };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int score = minimax(board, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = { i, j };
                }
            }
        }
    }
    return bestMove;
}

void playGame() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char currentPlayer = PLAYER;

    while (true) {
        displayBoard(board);

        if (currentPlayer == PLAYER) {
            int row, col;
            cout << "Ваш ход. Введите строку (1-3) и столбец (1-3): ";
            cin >> row >> col;
            if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
                cout << "Некорректный ход. Попробуйте снова.\n";
                continue;
            }
            board[row - 1][col - 1] = PLAYER;
        }
        else {
            cout << "Ход компьютера:\n";
            pair<int, int> move = findBestMove(board);
            board[move.first][move.second] = AI;
        }

        char winner = checkWinner(board);
        if (winner != ' ') {
            displayBoard(board);
            if (winner == PLAYER) {
                cout << "Поздравляем! Вы победили!\n";
            }
            else {
                cout << "Компьютер победил.\n";
            }
            break;
        }

        if (isDraw(board)) {
            displayBoard(board);
            cout << "Игра закончилась ничьей!\n";
            break;
        }

        currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Добро пожаловать в игру 'Крестики-нолики'!\n";
    playGame();
    return 0;
}