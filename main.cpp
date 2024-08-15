#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <thread>
#include <atomic>
#include <mutex>
#include "board.h"
#include "player.h"
#include "utils.h"
#include "music.h"
#include <iomanip>

using namespace std;

void PlayerXWin(int x, int y) {
    setColor(1, 15);
    moveCursor(y, x);
    cout << char(179) << char(219) << " " << " " << " " << char(219) << " " << " " << char(179)
        << char(219) << " " << " " << " " << " " << " " << char(219) << " "
        << char(179) << char(219) << " " << char(179) << char(219) << " " << " " << " " << " " << char(219);
    moveCursor(y + 1, x);
    cout << " " << char(179) << char(219) << " " << char(219) << " " << " " << " " << char(179)
        << char(219) << " " << " " << " " << " " << " " << char(219) << " " << char(179) << char(219)
        << " " << char(179) << char(219) << char(219) << " " << " " << " " << char(219);
    moveCursor(y + 2, x);
    cout << " " << " " << char(179) << char(219) << " " << " " << " " << " " << " "
        << char(179) << char(219) << " " << char(219) << " " << char(219) << " " << " "
        << char(179) << char(219) << " " << char(179) << char(219) << " " << char(219) << " " << " "
        << char(219);
    moveCursor(y + 3, x);
    cout << " " << char(179) << char(219) << " " << char(219) << " " << " " << " " << " "
        << char(179) << char(219) << " " << char(219) << " " << char(219) << " " << " " << char(179)
        << char(219) << " " << char(179) << char(219) << " " << " " << char(219) << " " << char(219);
    moveCursor(y + 4, x);
    cout << char(179) << char(219) << " " << " " << " " << char(219) << " " << " " << " " << " "
        << char(179) << char(219) << " " << char(219) << " " << " " << " " << char(179) << char(219)
        << " " << char(179) << char(219) << " " << " " << " " << " " << char(219);
}

void PlayerOWin(int x, int y) {
    setColor(1, 15);
    moveCursor(y, x);
    cout << " " << char(179) << char(219) << char(219) << char(219) << " " << " " << " " << char(179)
        << char(219) << " " << " " << " " << " " << " " << char(219) << " "
        << char(179) << char(219) << " " << char(179) << char(219) << " " << " " << " " << " " << char(219);
    moveCursor(y + 1, x);
    cout << char(179) << char(219) << " " << " " << " " << char(219) << " " << " " << char(179)
        << char(219) << " " << " " << " " << " " << " " << char(219) << " " << char(179) << char(219)
        << " " << char(179) << char(219) << char(219) << " " << " " << " " << char(219);
    moveCursor(y + 2, x);
    cout << char(179) << char(219) << " " << " " << " " << char(219) << " " << " " << " "
        << char(179) << char(219) << " " << char(219) << " " << char(219) << " " << " "
        << char(179) << char(219) << " " << char(179) << char(219) << " " << char(219) << " " << " "
        << char(219);
    moveCursor(y + 3, x);
    cout << char(179) << char(219) << " " << " " << " " << char(219) << " " << " " << " "
        << char(179) << char(219) << " " << char(219) << " " << char(219) << " " << " " << char(179)
        << char(219) << " " << char(179) << char(219) << " " << " " << char(219) << " " << char(219);
    moveCursor(y + 4, x);
    cout << " " << char(179) << char(219) << char(219) << char(219) << " " << " " << " " << " " << " "
        << char(179) << char(219) << " " << char(219) << " " << " " << " " << char(179) << char(219)
        << " " << char(179) << char(219) << " " << " " << " " << " " << char(219);
}

void drawWinning(char winner) {
    // Clear the board
    system("cls");

    int messageBoxHeight = 12;  // Height of the message box
    int messageBoxWidth = 60;   // Width of the message box
    int startX = SIZE_H * 2;      // Starting X position (adjust based on your board)
    int startY = SIZE_W * 4;      // Starting Y position (adjust based on your board)

    // Draw the message box frame
    setColor(2, 15); // Text color blue (2), background white (15)

    // Top border
    moveCursor(startX, startY);
    cout << char(201); // ┌
    for (int i = 0; i < messageBoxWidth - 2; ++i) cout << char(205); // ─
    cout << char(187); // ┐

    // Sides
    for (int i = 1; i < messageBoxHeight - 1; ++i) {
        moveCursor(startX + i, startY);
        cout << char(186); // │
        moveCursor(startX + i, startY + messageBoxWidth - 1);
        cout << char(186); // │
    }

    // Bottom border
    moveCursor(startX + messageBoxHeight - 1, startY);
    cout << char(200); // └
    for (int i = 0; i < messageBoxWidth - 2; ++i) cout << char(205); // ─
    cout << char(188); // ┘

    // Determine the starting position for X or O
    int centerX = startX + (messageBoxWidth / 2); // Center X position
    int centerY = startY + (messageBoxHeight / 2) - 3; // Center Y position

    // Draw the custom large "X" if winner is 'X'
    if (winner == 'X') {
        moveCursor(centerX + 2, centerY - 16); // Adjust the offset to center X
        PlayerXWin(centerX + 2, centerY - 16); // Call the function to draw X
    }
    // Draw the custom large "O" if winner is 'O'
    else if (winner == 'O') {
        moveCursor(centerX + 2, centerY - 16); // Adjust the offset to center O
        PlayerOWin(centerX + 2, centerY - 16); // Call the function to draw O
    }

    setColor(15, 0); // Reset to default: text white, background black
}





void timerThreadFunction(atomic<bool>& stopTimer, int& timeElapsed, mutex& mtx) {
    while (!stopTimer) {
        this_thread::sleep_for(chrono::seconds(1));
        {
            lock_guard<mutex> lock(mtx);
            ++timeElapsed;
        }
        updateElapsedTime(timeElapsed);
    }
}

void drawCARO(int x, int y) {
    setColor(1, 15);
    moveCursor(y, x);
    cout << " " << char(179) << char(219) << char(219) << char(219) << " " << " " << " " << char(179)
        << char(219) << " " << " " << " " << char(179) << char(219) << char(219) << char(219)
        << " " << " " << " " << char(179) << char(219) << char(219) << char(219);
    moveCursor(y + 1, x);
    cout << char(179) << char(219) << " " << " " << " " << " " << " " << char(179)
        << char(219) << " " << char(219) << " " << " " << char(179) << char(219) << " " << " "
        << char(219) << " " << char(179) << char(219) << " " << " " << " " << char(219);
    moveCursor(y + 2, x);
    cout << char(179) << char(219) << " " << " " << " " << " " << " " << char(179)
        << char(219) << char(219) << char(219) << " " << " " << char(179) << char(219) << " " << char(219)
        << " " << " " << char(179) << char(219) << " " << " " << " " << char(219);
    moveCursor(y + 3, x);
    cout << char(179) << char(219) << " " << " " << " " << " " << char(179) << char(219) << char(219)
        << " " << char(219) << char(219) << " " << char(179) << char(219) << char(219) << " " << " " << " "
        << char(179) << char(219) << " " << " " << " " << char(219);
    moveCursor(y + 4, x);
    cout << char(179) << char(219) << " " << " " << " " << " " << char(179) << char(219) << " " << " " << " "
        << char(219) << " " << char(179) << char(219) << " " << char(219) << " " << " " << char(179) << char(219)
        << " " << " " << " " << char(219);
    moveCursor(y + 5, x);
    cout << " " << char(179) << char(219) << char(219) << char(219) << " " << char(179) << char(219) << " " << " " << " "
        << char(219) << " " << char(179) << char(219) << " " << " " << char(219) << " " << " "
        << char(179) << char(219) << char(219) << char(219);
    setColor(15, 0);
}


void drawHeart(int x, int y, char value) {
    //setColor(4, 0); // Text color red (4), background black (0)
    setColor(1, 15); // Text color blue (1), background white (15)

    moveCursor(y, x); // Swap x and y when calling moveCursor
    cout << char(218) << char(196) << char(196) << char(196) << char(191);

    moveCursor(y + 1, x);
    cout << char(179) << " " << value << " " << char(179);

    moveCursor(y + 2, x);
    cout << char(192) << char(196) << char(196) << char(196) << char(217);

    //setColor(0, 15); // Reset to default: text black, background white

    setColor(15, 0); // Reset to default: text white, background black
}

void drawRabbit(int x, int y, char value) {
    //setColor(4, 0); // Text color red (4), background black (0)
    setColor(1, 15); // Text color blue (1), background white (15)
    moveCursor(y, x); // Swap x and y when calling moveCursor
    cout << " " << " " << " " << char(219) << char(219) << char(219);
    moveCursor(y + 1, x);
    cout << " " << " " << char(219) << char(219) << " " << char(219) << char(219);
    moveCursor(y + 2, x);
    cout << " " << char(219) << char(219) << " " << " " << " " << char(219) << char(219);
    moveCursor(y + 3, x);
    cout << " " << char(219) << char(219) << " " << " " << " " << char(219) << char(219)
        << " " << " " << " " << " " << " " << " " << " " << " " << " "
        << char(219) << char(219) << char(219);
    moveCursor(y + 4, x);
    cout << " " << char(219) << char(219) << " " << " " << " " << char(219) << char(219)
        << " " << " " << " " << " " << " " << " " << " " << char(219) << char(219)
        << " " << " " << " " << char(219) << char(219) << char(219) << char(219);
    moveCursor(y + 5, x);
    cout << " " << char(219) << char(219) << " " << " " << char(219) << char(219) << " " << " " << " "
        << " " << " " << " " << " "
        << char(219) << " " << " " << " " << char(219) << char(219) << " " << " " << " " << char(219) << char(219);
    moveCursor(y + 6, x);
    cout << " " << " " << char(219) << char(219) << " " << " " << char(219)
        << " " << " " << " " << " " << " " << " "
        << char(219) << " " << " " << char(219) << char(219) << " " << " " << char(219) << char(219) << char(219)
        << " " << " " << char(219) << char(219);
    moveCursor(y + 7, x);
    cout << " " << " " << " " << char(219) << char(219) << " " << " " << char(219) << " " << " "
        << " " << " " << char(219) << " " << " " << char(219) << char(219) << " " << " " << " "
        << " " << " " << char(219) << char(219) << " " << " " << char(219);
    moveCursor(y + 8, x);
    cout << " " << " " << " " << " " << char(219) << char(219) << " " << char(219) << char(219)
        << " " << " " << char(219) << char(219) << " " << char(219) << char(219)
        << " " << " " << " " << " " << " " << " " << " " << " "
        << char(219) << char(219);
    moveCursor(y + 9, x);
    cout << " " << " " << " " << " " << char(219) << char(219) << " " << " " << " "
        << char(219) << char(219) << " " << " " << char(219) << char(219);
    moveCursor(y + 10, x);
    cout << " " << " " << " " << char(219) << " " << " " << " " << " " << " "
        << " " << " " << " " << " " << " " << " " << char(219);
    moveCursor(y + 11, x);
    cout << " " << " " << char(219) << " " << " " << " " << " " << " " << " "
        << " " << " " << " " << " " << " " << " " << " " << char(219);
    moveCursor(y + 12, x);
    cout << " " << char(219) << " " << " " << " " << " " << char(79) << " " << " " << " "
        << " " << " " << char(79) << " " << " " << " " << " " << char(219);
    moveCursor(y + 13, x);
    cout << " " << char(219) << " " << " " << " " << char(47) << " " << " " << " "
        << char(248) << " " << " " << " " << " " << char(92) << " " << " " << char(219);
    moveCursor(y + 14, x);
    cout << " " << char(219) << " " << " " << " " << char(92) << char(95) << char(95) << char(47)
        << " " << " " << char(92) << char(95) << char(95) << char(47) << " " << " " << char(219);
    moveCursor(y + 15, x);
    cout << " " << " " << " " << char(219) << " " << " " << " " << " " << " "
        << "W" << " " << " " << " " << " " << " " << char(219);
    moveCursor(y + 16, x);
    cout << " " << " " << " " << " " << " " << char(219) << char(219) << " " << " " << " "
        << " " << " " << char(219) << char(219);
    moveCursor(y + 17, x);
    cout << " " << " " << " " << " " << " " << " " << " "
        << char(219) << char(219) << char(219) << char(219) << char(219);

    //setColor(0, 15); // Reset to default: text black, background white

    setColor(15, 0); // Reset to default: text white, background black
}

void drawMenuFrame(int x, int y, int width, int height) {
    setColor(1, 15); // Set text color to blue (1), background white (15)

    // Draw top border
    moveCursor(y, x);
    cout << char(201); // ┌
    for (int i = 0; i < width; ++i) cout << char(205); // ─
    cout << char(187); // ┐

    // Draw sides
    for (int i = 1; i < height - 1; ++i) {
        moveCursor(y + i, x);
        cout << char(186); // │
        moveCursor(y + i, x + width + 1);
        cout << char(186); // │
    }

    // Draw bottom border
    moveCursor(y + height - 1, x);
    cout << char(200); // └
    for (int i = 0; i < width; ++i) cout << char(205); // ─
    cout << char(188); // ┘

    setColor(15, 0); // Reset to default: text white, background black
}

void displayMenu(int selectedOption) {
    clearScreen();
    setColor(0, 15); // Set the console to have a white background throughout the menu

    for (int i = 1; i <= 6; i++) {
        int yPos = 8 + (i - 1) * 3; // Calculate Y position for each option
        drawMenuFrame(46, yPos, 25, 3); // Draw frame for each menu item

        moveCursor(yPos + 1, 48);
        if (i == selectedOption) {
            setColor(0, 11); // Black text on yellow background for the selected option
            cout << "> ";
        }
        else {
            setColor(0, 15); // Black text on white background for unselected options
            cout << "  ";
        }

        switch (i) {
        case 1: cout << "1. New Game" << endl; break;
        case 2: cout << "2. Load Game" << endl; break;
        case 3: cout << "3. Instructions" << endl; break;
        case 4: cout << "4. Credit" << endl; break;
        case 5: cout << "5. Setting" << endl; break;
        case 6: cout << "6. Exit" << endl; break;
        }
    }

    drawRabbit(85, 10, char(3));
    drawCARO(47, 1);
    setColor(0, 15); // Reset to black text on white background after menu display
}

void displayInstructions() {
    clearScreen();
    cout << "Instructions:" << endl;
    cout << "1. Use arrow keys to move the cursor." << endl;
    cout << "2. Press space to place your mark." << endl;
    cout << "3. Press 'L' to save the game." << endl;
    cout << "4. Press 'T' to load the game." << endl;
    _getch(); // Wait for a key press
}

void displayCredit() {
    clearScreen();
    cout << "Credit:" << endl;
    cout << "Developed by Group 3" << endl;
    cout << "Cao Pham Hoang Thai - 22127382 " << endl;
    cout << "Nguyen Gia Phuc - 22127331 " << endl;
    cout << "Nguyen Thi Yen Nhi - 22127312 " << endl;
    cout << "Bui Cong Mau - 22127260 " << endl;
    cout << "Duong Quang Thang - 22127384 " << endl;
    _getch(); // Wait for a key press
}

bool playAgain() {
    char choice;
    cout << "Do you want to play again? (Y/N): ";
    cin >> choice;
    return (toupper(choice) == 'Y');
}



bool chooseGameMode() {
    int selectedOption = 1;
    bool optionSelected = false;

    while (!optionSelected) {
        clearScreen();
        setColor(0, 15); // Set the console to have a white background

        cout << "Choose Game Mode:" << endl;

        for (int i = 1; i <= 2; i++) {
            if (i == selectedOption) {
                setColor(0, 11); // Black text on yellow background for the selected option
                cout << "> ";
            }
            else {
                setColor(0, 15); // Black text on white background for unselected options
                cout << "  ";
            }

            switch (i) {
            case 1: cout << "1. PVP" << endl; break;
            case 2: cout << "2. PVE" << endl; break;
            }
        }
        setColor(0, 15); // Reset to black text on white background after menu display

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) { // Up arrow
                selectedOption = (selectedOption > 1) ? selectedOption - 1 : 2;
            }
            else if (key == 80) { // Down arrow
                selectedOption = (selectedOption < 2) ? selectedOption + 1 : 1;
            }
        }
        else if (key == 13) { // Enter key
            optionSelected = true;
        }
    }

    return selectedOption == 2; // Return true if PVE is selected
}

void displaySetting() {
    clearScreen();

}

int main() {
    srand(time(0)); // Seed the random number generator for the AI
    bool replay = true;
    hideCursor();
    

    while (replay) {
        hideCursor();
        setColor(0, 15);
        clearScreen();
        int selectedOption = 1;
        bool optionSelected = false;

        while (!optionSelected) {
            displayMenu(selectedOption);
            int key = _getch();
            if (key == 224) {
                key = _getch();
                if (key == 72) { // Up arrow
                    selectedOption = (selectedOption > 1) ? selectedOption - 1 : 6;
                } else if (key == 80) { // Down arrow
                    selectedOption = (selectedOption < 6) ? selectedOption + 1 : 1;
                }
            } else if (key == 13) { // Enter key
                optionSelected = true;
            }
        }

        if (selectedOption == 6) {
            break;
        } else if (selectedOption == 3) {
            displayInstructions();
            continue;
        } else if (selectedOption == 4) {
            displayCredit();
            continue;
        }
        else if (selectedOption == 5) {
            displaySetting();
        }

        bool againstComputer = false;
        vector<vector<char>> board(SIZE_H, vector<char>(SIZE_W, EMPTY));
        char currentPlayer = PLAYER_X;

        if (selectedOption == 1) {
            clearScreen();
            againstComputer = chooseGameMode();
        } else if (selectedOption == 2) {
            if (!loadGame(board, currentPlayer, againstComputer)) {
                _getch(); // Pause to let the user see the error message
                continue;
            }
        }

        atomic<bool> stopTimer(false);
        int timeElapsed = 0;
        mutex mtx;
        thread timerThread(timerThreadFunction, ref(stopTimer), ref(timeElapsed), ref(mtx));

        bool gameEnded = false;

        clearScreen(); // Clear the screen before starting the game loop
        printBoard(board, currentPlayer, timeElapsed);
        std::thread backgroundMusicThread(playBackgroundMusic, "nhacnen.wav");
        while (!gameEnded) {
            
            {
                lock_guard<mutex> lock(mtx);
            }

            if (currentPlayer == PLAYER_X || !againstComputer) {
                playerMove(board, currentPlayer, againstComputer, timeElapsed);
            } else {
                computerMove(board, currentPlayer);
            }

            if (checkWin(board, currentPlayer)) {
                stopTimer = true;
                timerThread.join(); // Ensure the timer thread is stopped
                clearScreen();
                {
                    lock_guard<mutex> lock(mtx);
                    printBoard(board, currentPlayer, timeElapsed);
                }
                cout << "Player " << currentPlayer << " wins!" << endl;
                gameEnded = true;
            } else {
                currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
            }
        }

        stopTimer = true;
        if (timerThread.joinable()) {
            timerThread.join();
        }

        if (!playAgain()) {
            replay = false;
        }
    }

    //backgroundMusicThread.join();
    
    return 0;
}
