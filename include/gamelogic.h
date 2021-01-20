/**
 * @file gamelogic.cc
 * @brief Models game state and logic
 */
#ifndef CPP_TETRIS_GAMELOGIC_H
#define CPP_TETRIS_GAMELOGIC_H

#include "model.h"
#include "observer.h"
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <utility>
#include <mutex>

enum class GameInput {
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    ROTATE
};

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
    /*
    * Attach observer to the game
    * @param observer Observer object (e.g. a GUI) that observes changes to the game
    */
    void Attach(IObserver* observer);
    /*
    * Detach observer from the game
    */
    void Detach(IObserver* observer);

    /*
    * Send keyboard input to game
    * @param input (move down, left, right, rotate)
    */
    void SendGameInput(GameInput input);
        
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
    /*
    * Converts a y coordinate from the frame of the piece to a y coordinate on the board
    */
    int PieceToBoardYCoordinate(int pieceYCoordinate);
    /*
    * Converts a x coordinate form the frame of the piece to a x coordinate on the board
    */
    int PieceToBoardXCoordinate(int pieceXCoordinate);
    /*
    * Moves the current GamePiece down (if possible)
    */
    void MoveCurrentPieceDown();
    /*
    * Moves the current GamePiece left (if possible)
    */
    void MoveCurrentPieceLeft();
    /*
    * Moves the current GamePiece right (if possible)
    */
    void MoveCurrentPieceRight();
    /*
    * Rotates the current GamePiece (if possible)
    */
    void RotateCurrentPiece();

    GameState gameState_;
    std::vector<IObserver*> observers;
    std::mutex mutex_;
};
#endif //CPP_TETRIS_GAMELOGIC_H