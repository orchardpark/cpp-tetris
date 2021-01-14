/**
 * @file gamelogic.cc
 * @brief Models game state and logic
 */
#ifndef CPP_TETRIS_GAMELOGIC_H
#define CPP_TETRIS_GAMELOGIC_H

#include "model.h"
#include "observer.h"
#include "textui.h"
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <utility>

class Game : public ISubject{
public:
    /**
    * Creates a new game instance
    */
    Game();
    /*
    * Creates a new game from specified game state
    */
    Game(GameState state);
    /*
    * Run the game
    */
    void Run();
    void Attach(IObserver* observer);
    void Detach(IObserver* observer);
        
private:
	/**
     * Executes one time step (moving current piece down 1)
     * @return true if succeeded and false if game is finished
     */
    bool ExecuteTimeStep();
	bool IsGameFinished();
    GamePiece NextPiece();
    bool IsPieceBlocked();
    void AddPieceToBoard();
    void ClearAndScore();

    void CreateRandomGenerator();

    GameState gameState_;
    std::vector<IObserver*> observers;
};
#endif //CPP_TETRIS_GAMELOGIC_H