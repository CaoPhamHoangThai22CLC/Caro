#include <iostream>
#include <vector>
#include <fstream>
#include "board.h"
#include "utils.h"

using namespace std;

void printCell(int x, int y, char value) {
    setColor(1, 15); // Text color blue (1), background white (15)

    moveCursor(y, x); // Swap x and y when calling moveCursor
    cout << char(218) << char(196) << char(196) << char(196) << char(191);

    moveCursor(y + 1, x);
    cout << char(179) << " " << value << " " << char(179);

    moveCursor(y + 2, x);
    cout << char(192) << char(196) << char(196) << char(196) << char(217);

    //setColor(0, 15); // Reset to default: text black, background white
}

void printBoard(const vector<vector<char>>& board, char currentPlayer, int timeElapsed) {
    hideCursor();
    clearScreen(); // Clear the screen before printing the board

    int startX = 2, startY = 4; // Starting point for the grid
    int cellWidth = 5, cellHeight = 3; // Size of each cell

    /*for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int y = startX + i * cellHeight;
            int x = startY + j * cellWidth;
            printCell(x, y, ' ');
        }
    }*/

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            moveCursor(i, j * 2);
            int y = startX + i * cellHeight;
            int x = startY + j * cellWidth;
            if (board[i][j] == PLAYER_X) {
                setColor(4, 15); // Red for PLAYER_X
            }
            else if (board[i][j] == PLAYER_O) {
                setColor(9, 15); // Blue for PLAYER_O
            }
            printCell(x, y, board[i][j]);
        }
    }
    moveCursor(2, SIZE * 2 + 30);
    cout << "Current player: " << currentPlayer;
    showCursor();
}

void updateElapsedTime(int timeElapsed) {
    hideCursor();
    moveCursor(3, SIZE * 2 + 30); // Move to the position where the time elapsed is displayed
    cout << "Time elapsed: " << timeElapsed << " seconds";
    showCursor();
}

bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j <= SIZE - 5; ++j) {
            if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player && board[i][j+4] == player) {
                return true;
            }
        }
    }
    
    // Check columns
    for (int i = 0; i <= SIZE - 5; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player && board[i+4][j] == player) {
                return true;
            }
        }
    }

    // Check diagonals (\ direction)
    for (int i = 0; i <= SIZE - 5; ++i) {
        for (int j = 0; j <= SIZE - 5; ++j) {
            if (board[i][j] == player && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player && board[i+4][j+4] == player) {
                return true;
            }
        }
    }

    // Check diagonals (/ direction)
    for (int i = 4; i < SIZE; ++i) {
        for (int j = 0; j <= SIZE - 5; ++j) {
            if (board[i][j] == player && board[i-1][j+1] == player && board[i-2][j+2] == player && board[i-3][j+3] == player && board[i-4][j+4] == player) {
                return true;
            }
        }
    }

    return false;
}

void saveGame(const vector<vector<char>>& board, char currentPlayer, bool againstComputer) {
    string filename;
    cout << "Enter filename to save the game: ";
    cin >> filename;
    ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << currentPlayer << endl;
        outFile << againstComputer << endl;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                outFile << board[i][j] << " ";
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Game saved successfully!" << endl;
    } else {
        cout << "Failed to save the game." << endl;
    }
}

bool loadGame(vector<vector<char>>& board, char& currentPlayer, bool& againstComputer) {
    string filename;
    cout << "Enter filename to load the game: ";
    cin >> filename;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Failed to load the game. File not found." << endl;
        return false;
    }

    inFile >> currentPlayer;
    inFile >> againstComputer;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            inFile >> board[i][j];
        }
    }

    if (inFile.fail()) {
        cout << "Failed to load the game. Data corrupted." << endl;
        return false;
    }

    inFile.close();
    cout << "Game loaded successfully!" << endl;
    return true;
}
