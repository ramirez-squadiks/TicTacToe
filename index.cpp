#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';

class TicTacToe {
private:
    vector<vector<char>> board;
    int size;

public:
    TicTacToe(int n) : size(n) {
        board.resize(size, vector<char>(size, EMPTY));
    }

    void printBoard() {
        cout << "   ";
        for (int j = 0; j < size; ++j) {
            cout << " " << j + 1 << " ";
            if (j < size - 1) cout << "|";
        }
        cout << endl;

        cout << "  ";
        for (int j = 0; j < size - 1; ++j) {
            cout << "---";
        }
        cout << endl;

        for (int i = 0; i < size; ++i) {
            cout << " " << i + 1 << " ";
            for (int j = 0; j < size; ++j) {
                cout << " " << board[i][j] << " ";
                if (j < size - 1) cout << "|";
            }
            cout << endl;

            if (i < size - 1) {
                cout << "  ";
                for (int j = 0; j < size - 1; ++j) {
                    cout << "---";
                }
                cout << endl;
            }
        }
    }

    bool makeMove(int row, int col, char player) {
        if (row >= 0 && row < size && col >= 0 && col < size && board[row][col] == EMPTY) {
            board[row][col] = player;
            return true;
        }
        return false;
    }

    bool checkWin(char player) {
        for (int i = 0; i < size; ++i) {
            if (checkRow(i, player) || checkCol(i, player)) {
                return true;
            }
        }
        return checkDiagonal(player);
    }

    bool checkRow(int row, char player) {
        for (int j = 0; j < size; ++j) {
            if (board[row][j] != player) return false;
        }
        return true;
    }

    bool checkCol(int col, char player) {
        for (int i = 0; i < size; ++i) {
            if (board[i][col] != player) return false;
        }
        return true;
    }

    bool checkDiagonal(char player) {
        bool diag1 = true, diag2 = true;
        for (int i = 0; i < size; ++i) {
            if (board[i][i] != player) diag1 = false;
            if (board[i][size - 1 - i] != player) diag2 = false;
        }
        return diag1 || diag2;
    }

    bool isFull() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == EMPTY) return false;
            }
        }
        return true;
    }

    void computerMove() {
        int row, col;
        do {
            row = rand() % size;
            col = rand() % size;
        } while (!makeMove(row, col, COMPUTER));
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    TicTacToe game(3);
    int row, col;

    while (true) {
        game.printBoard();
        cout << "Введите ваш ход (строка и столбец): ";
        cin >> row >> col;

        if (!game.makeMove(row - 1, col - 1, PLAYER)) {
            cout << "Неверный ход. Попробуйте снова." << endl;
            continue;
        }

        if (game.checkWin(PLAYER)) {
            game.printBoard();
            cout << "Вы выиграли!" << endl;
            break;
        }

        if (game.isFull()) {
            game.printBoard();
            cout << "Ничья!" << endl;
            break;
        }

        game.computerMove();

        if (game.checkWin(COMPUTER)) {
            game.printBoard();
            cout << "Компьютер выиграл!" << endl;
            break;
        }

        if (game.isFull()) {
            game.printBoard();
            cout << "Ничья!" << endl;
            break;
        }
    }

    return 0;
}
