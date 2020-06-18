/**
 * @file gamelogic.cc
 * @brief Models game state and logic
 */
#ifndef CPP_TETRIS_GAMELOGIC_H
#define CPP_TETRIS_GAMELOGIC_H

#endif //CPP_TETRIS_GAMELOGIC_H
#include "model.h"

class Game{
public:
    Game();
    void ExecuteTimeStep();
    bool IsGameFinished();
private:
    GamePiece NextPiece();
    bool IsPieceFinished();
    void clearAndScore();
    GameBoard board_;
    unsigned int score_;
    GamePiece currentPiece_;
};