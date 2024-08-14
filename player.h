#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

void playerMove(std::vector<std::vector<char>>& board, char player, bool& againstComputer, int timeElapsed);
void computerMove(std::vector<std::vector<char>>& board, char player);

#endif // PLAYER_H
