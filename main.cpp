#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <thread>
#include <atomic>
#include <mutex>
#include "board.h"
#include "player.h"
#include "utils.h"

using namespace std;

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

void displayMenu(int selectedOption) {
    clearScreen();
    cout << "====== Tic-Tac-Toe ======" << endl;
    cout << (selectedOption == 1 ? "> " : "  ") << "1. New Game" << endl;
    cout << (selectedOption == 2 ? "> " : "  ") << "2. Load Game" << endl;
    cout << (selectedOption == 3 ? "> " : "  ") << "3. Instructions" << endl;
    cout << (selectedOption == 4 ? "> " : "  ") << "4. Credit" << endl;
    cout << (selectedOption == 5 ? "> " : "  ") << "5. Exit" << endl;
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
    cout << "Developed by Your Name" << endl;
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
        cout << "Choose Game Mode:" << endl;
        cout << (selectedOption == 1 ? "> " : "  ") << "1. PVP" << endl;
        cout << (selectedOption == 2 ? "> " : "  ") << "2. PVE" << endl;
        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) { // Up arrow
                selectedOption = (selectedOption > 1) ? selectedOption - 1 : 2;
            } else if (key == 80) { // Down arrow
                selectedOption = (selectedOption < 2) ? selectedOption + 1 : 1;
            }
        } else if (key == 13) { // Enter key
            optionSelected = true;
        }
    }

    return selectedOption == 2; // Return true if PVE is selected
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
                    selectedOption = (selectedOption > 1) ? selectedOption - 1 : 5;
                } else if (key == 80) { // Down arrow
                    selectedOption = (selectedOption < 5) ? selectedOption + 1 : 1;
                }
            } else if (key == 13) { // Enter key
                optionSelected = true;
            }
        }

        if (selectedOption == 5) {
            break;
        } else if (selectedOption == 3) {
            displayInstructions();
            continue;
        } else if (selectedOption == 4) {
            displayCredit();
            continue;
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
        while (!gameEnded) {
            {
                lock_guard<mutex> lock(mtx);
                //printBoard(board, currentPlayer, timeElapsed);
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

    return 0;
}
