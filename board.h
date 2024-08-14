#ifndef BOARD_H
#define BOARD_H

#include <vector>

const int SIZE_H = 8;
const int SIZE_W = 13;
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

void printCell(int x, int y, char value);
void printBoard(const std::vector<std::vector<char>>& board, char currentPlayer, int timeElapsed);
bool checkWin(const std::vector<std::vector<char>>& board, char player);
void saveGame(const std::vector<std::vector<char>>& board, char currentPlayer, bool againstComputer);
bool loadGame(std::vector<std::vector<char>>& board, char& currentPlayer, bool& againstComputer);
void updateElapsedTime(int timeElapsed); // New function declaration
void drawXDecoration();
void drawODecoration();
void drawZero(int startX, int startY);
void drawSeven(int startX, int startY);
void drawNine(int startX, int startY);
void drawEight(int startX, int startY);
void drawSix(int startX, int startY);
void drawFive(int startX, int startY);
void drawFour(int startX, int startY);
void drawThree(int startX, int startY);
void drawTwo(int startX, int startY);
void drawOne(int startX, int startY);

#endif // BOARD_H
