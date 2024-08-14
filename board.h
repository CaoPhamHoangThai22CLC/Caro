#ifndef BOARD_H
#define BOARD_H

#include <vector>

const int SIZE = 8;
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

void printCell(int x, int y, char value);
void printBoard(const std::vector<std::vector<char>>& board, char currentPlayer, int timeElapsed);
bool checkWin(const std::vector<std::vector<char>>& board, char player);
void saveGame(const std::vector<std::vector<char>>& board, char currentPlayer, bool againstComputer);
bool loadGame(std::vector<std::vector<char>>& board, char& currentPlayer, bool& againstComputer);
void updateElapsedTime(int timeElapsed); // New function declaration

#endif // BOARD_H
