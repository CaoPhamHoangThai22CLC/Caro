#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include "player.h"
#include "board.h"
#include "utils.h"


using namespace std;

void playerMove(vector<vector<char>>& board, char player, bool& againstComputer, int timeElapsed) {
    int x = 0, y = 0;
    char previousChar = board[x][y];

    while (true) {
        moveCursor(x * 3 + 3, y * 5 + 6);
        cout << '?';

        int key = _getch();
        if (key == 224) {
            key = _getch();
            moveCursor(x * 3 + 3, y * 5 + 6);
            cout << previousChar; // Restore the previous character

            switch (key) {
                case 72: // Up arrow
                    x = (x > 0) ? x - 1 : SIZE - 1;
                    break;
                case 80: // Down arrow
                    x = (x < SIZE - 1) ? x + 1 : 0;
                    break;
                case 75: // Left arrow
                    y = (y > 0) ? y - 1 : SIZE - 1;
                    break;
                case 77: // Right arrow
                    y = (y < SIZE - 1) ? y + 1 : 0;
                    break;
            }
            previousChar = board[x][y];
        } else if (key == 32) { // Space bar
            if (board[x][y] == EMPTY) {
                board[x][y] = player;
                moveCursor(x * 3 + 3, y * 5 + 6);
                setColor((player == PLAYER_X) ? 12 : 9, 15);
                cout << player;
                setColor(1, 15);
                break;
            } else {
                moveCursor(4, SIZE * 2 + 30);
                cout << "Invalid move. The cell is already occupied. Try again." << endl;
                _getch(); // Pause to let the player see the error message
            }
        } else if (key == 'L' || key == 'l') { // Save game
            saveGame(board, player, againstComputer);
        } else if (key == 'T' || key == 't') { // Load game
            if (loadGame(board, player, againstComputer)) {
                break;
            }
        }
    }
}



void computerMove(vector<vector<char>>& board, char player) {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (board[x][y] != EMPTY);

    board[x][y] = player;
    moveCursor(x * 3 + 3, y * 5 + 6);
    setColor((player == PLAYER_X) ? 12 : 9, 15);
    cout << player;
    setColor(1, 15);
}
