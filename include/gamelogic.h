/**
 * @file gamelogic.cc
 * @brief Models game state and logic
 */
#ifndef CPP_TETRIS_GAMELOGIC_H
#define CPP_TETRIS_GAMELOGIC_H

#endif //CPP_TETRIS_GAMELOGIC_H
#include "model.h"
#include <random>
class Game{
public:
    /**
    * Creates a new game instance
    */
    Game();
    /**
     * Executes one time step (moving current piece down 1)
     * @return true if succeeded and false if game is finished
     */
    bool ExecuteTimeStep();
    bool IsGameFinished();
    /*
    * Returns the next gamepiece that will be dropped
    */
    GamePiece NextPiece();
    bool IsPieceBlocked();
    void AddPieceToBoard();
    void ClearAndScore();
private:
    GameBoard board_;
    unsigned int score_;
    GamePiece currentPiece_;
    int level_;
};