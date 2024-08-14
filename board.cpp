#include <iostream>
#include <vector>
#include <fstream>
#include "board.h"
#include "utils.h"

using namespace std;

void printCell(int x, int y, char value) {
    setColor(1, 15);

    moveCursor(y, x);
    cout << char(218) << char(196) << char(196) << char(196) << char(191);

    moveCursor(y + 1, x);
    cout << char(179) << " " << value << " " << char(179);

    moveCursor(y + 2, x);
    cout << char(192) << char(196) << char(196) << char(196) << char(217);
}

void printBoard(const vector<vector<char>>& board, char currentPlayer, int timeElapsed) {
    hideCursor();
    clearScreen();

    int startX = 2, startY = 4; // Điểm bắt đầu cho lưới
    int cellWidth = 5, cellHeight = 3; // Kích thước của mỗi ô

    for (int i = 0; i < SIZE_H; ++i) {
        for (int j = 0; j < SIZE_W; ++j) {
            int y = startX + i * cellHeight;
            int x = startY + j * cellWidth;

            if (board[i][j] == PLAYER_X) {
                setColor(4, 15); // Đỏ cho PLAYER_X
            } else if (board[i][j] == PLAYER_O) {
                setColor(9, 15); // Xanh dương cho PLAYER_O
            } else {
                setColor(1, 15); // Màu mặc định
            }
            printCell(x, y, board[i][j]);
        }
    }

    moveCursor(4, SIZE_W * 2 + 43);
    cout << "Current player: ";
    moveCursor(12, SIZE_W * 2 + 43);
    cout << "Time: ";
    // Vẽ hình trang trí X và O
    drawXDecoration();
    drawODecoration();

}

void updateElapsedTime(int timeElapsed) {
    int startX = 13;
    int startY = SIZE_W * 2 + 48;
    hideCursor();
    moveCursor(3, SIZE_W * 2 + 43);
    std::vector<void(*)(int startX, int startY)> drawFunctions = { drawZero, drawOne, drawTwo, drawThree, drawFour, drawFive, drawSix, drawSeven, drawEight, drawNine };

    // Chuyển số timeElapsed thành các chữ số riêng lẻ
    std::vector<int> digits;
    while (timeElapsed > 0) {
        digits.push_back(timeElapsed % 10);
        timeElapsed /= 10;
    }

    // In từng số theo thứ tự ngược lại
    int i = 0;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        drawFunctions[*it](startX, startY + i * 8);
        i++;
    }
}

bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows
    for (int i = 0; i < SIZE_H; ++i) {
        for (int j = 0; j <= SIZE_W - 5; ++j) {
            if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player && board[i][j+4] == player) {
                return true;
            }
        }
    }
    
    // Check columns
    for (int i = 0; i <= SIZE_H - 5; ++i) {
        for (int j = 0; j < SIZE_W; ++j) {
            if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player && board[i+4][j] == player) {
                return true;
            }
        }
    }

    // Check diagonals (\ direction)
    for (int i = 0; i <= SIZE_H - 5; ++i) {
        for (int j = 0; j <= SIZE_W - 5; ++j) {
            if (board[i][j] == player && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player && board[i+4][j+4] == player) {
                return true;
            }
        }
    }

    // Check diagonals (/ direction)
    for (int i = 4; i < SIZE_H; ++i) {
        for (int j = 0; j <= SIZE_W - 5; ++j) {
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
        for (int i = 0; i < SIZE_H; ++i) {
            for (int j = 0; j < SIZE_W; ++j) {
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
    for (int i = 0; i < SIZE_H; ++i) {
        for (int j = 0; j < SIZE_W; ++j) {
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

void drawXDecoration() {
    int startX = 5;
    int startY = SIZE_W * 2 + 48;

    setColor(4, 15);
    moveCursor(startX + 1, startY);
    cout << char(219) << char(219) << char(187) << char(32) << char(32) << char(219) << char(219) << char(187);
    moveCursor(startX + 2, startY);
    cout << char(200) << char(219) << char(219) << char(187) << char(219) << char(219) << char(201) << char(188);
    moveCursor(startX + 3, startY);
    cout << char(32) << char(200) << char(219) << char(219) << char(219) << char(201) << char(188) << char(32);
    moveCursor(startX + 4, startY);
    cout << char(32) << char(219) << char(219) << char(201) << char(219) << char(219) << char(187) << char(32);
    moveCursor(startX + 5, startY);
    cout << char(219) << char(219) << char(201) << char(188) << char(32) << char(219) << char(219) << char(187);
    moveCursor(startX + 6, startY);
    cout << char(200) << char(205) << char(188) << char(32) << char(32) << char(200) << char(205) << char(188);
    setColor(1, 15);
}

void drawODecoration() {
    int startX = 5;
    int startY = SIZE_W * 2 + 63;

    setColor(9, 15);
    moveCursor(startX + 1, startY);
    cout << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(187);
    moveCursor(startX + 2, startY);
    cout << char(219) << char(219) << char(201) << char(205) << char(205) << char(205) << char(219) << char(219) << char(187);
    moveCursor(startX + 3, startY);
    cout << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(219) << char(219) << char(186);
    moveCursor(startX + 4, startY);
    cout << char(219) << char(219) << char(186) << char(32) << char(32) << char(32) << char(219) << char(219) << char(186);
    moveCursor(startX + 5, startY);
    cout << char(200) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(201) << char(188);
    moveCursor(startX + 6, startY);
    cout << char(32) << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188);
    setColor(1, 15);
}

void drawZero(int startX, int startY) {
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32);
    moveCursor(startX + 2, startY);
    cout << char(219) << char(32) << char(32) << char(219) << char(219) << char(219) << char(219) << char(219);
    moveCursor(startX + 3, startY);
    cout << char(219) << char(32) << char(219) << char(219) << char(219) << char(219) << char(32) << char(219);
    moveCursor(startX + 4, startY);
    cout << char(219) << char(219) << char(219) << char(219) << char(32) << char(219) << char(219) << char(219);
    moveCursor(startX + 5, startY);
    cout << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32);
    setColor(1, 15);
}

void drawSeven(int startX, int startY) {
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
    moveCursor(startX + 2, startY);
    cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 3, startY);
    cout << char(32) << char(32) << char(32) << char(32) << char(219) << char(219) << char(32);
    moveCursor(startX + 4, startY);
    cout << char(32) << char(32) << char(32) << char(219) << char(219) << char(32) << char(32);
    moveCursor(startX + 5, startY);
    cout << char(32) << char(32) << char(219) << char(219) << char(32) << char(32) << char(32);
    setColor(1, 15);
}

void drawNine(int startX, int startY) {
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(32);
    moveCursor(startX + 2, startY);
    cout << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 3, startY);
    cout << char(32) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
    moveCursor(startX + 4, startY);
    cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 5, startY);
    cout << char(32) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    setColor(1, 15);
}

void drawEight(int startX, int startY) {
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(32) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    moveCursor(startX + 2, startY);
    cout << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 3, startY);
    cout << char(32) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32); 
    moveCursor(startX + 4, startY);
    cout << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 5, startY);
    cout << char(32) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    setColor(1, 15);
}

void drawSix(int startX, int startY) {
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(32) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    moveCursor(startX + 2, startY);
    cout << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32);
    moveCursor(startX + 3, startY);
    cout << char(219) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    moveCursor(startX + 4, startY);
    cout << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 5, startY);
    cout << char(32) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    setColor(1, 15);
}

void drawFive(int startX, int startY) {
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(219) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(219);
    moveCursor(startX + 2, startY);
    cout << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32);
    moveCursor(startX + 3, startY);
    cout << char(219) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(219);
    moveCursor(startX + 4, startY);
    cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 5, startY);
    cout << char(219) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(219);
    setColor(1, 15);
}

void drawFour(int startX, int startY) {;
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 2, startY);
    cout << char(219) << char(219) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 3, startY);
    cout << char(219) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(219);
    moveCursor(startX + 4, startY);
    cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 5, startY);
    cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219);
    setColor(1, 15);
}

void drawThree(int startX, int startY) {
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(219) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    moveCursor(startX + 2, startY);
    cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 3, startY);
    cout << char(32) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    moveCursor(startX + 4, startY);
    cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 5, startY);
    cout << char(219) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    setColor(1, 15);
}

void drawTwo(int startX, int startY) {
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(219) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    moveCursor(startX + 2, startY);
    cout << char(32) << char(32) << char(32) << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 3, startY);
    cout << char(32) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(32);
    moveCursor(startX + 4, startY);
    cout << char(219) << char(219) << char(32) << char(32) << char(32) << char(32) << char(32);
    moveCursor(startX + 5, startY);
    cout << char(219) << char(219) << char(219)  << char(219)  << char(219) << char(219) << char(219);
    setColor(1, 15);
}

void drawOne(int startX, int startY) {
    moveCursor(startX + 1, startY); cout << "        ";
    moveCursor(startX + 2, startY); cout << "        ";
    moveCursor(startX + 3, startY); cout << "        ";
    moveCursor(startX + 4, startY); cout << "        ";
    moveCursor(startX + 5, startY); cout << "        ";
    setColor(14, 15);
    moveCursor(startX + 1, startY);
    cout << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 2, startY);
    cout << char(219) << char(219) << char(219) << char(219);
    moveCursor(startX + 3, startY);
    cout << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 4, startY);
    cout << char(32) << char(32) << char(219) << char(219);
    moveCursor(startX + 5, startY);
    cout << char(32) << char(32) << char(219) << char(219);
    setColor(1, 15);
}
