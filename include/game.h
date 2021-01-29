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

    /// <summary>
    /// Creates a new game instance
    /// </summary>
    /// <returns>New game instance</returns>
    Game();
    
	/// <summary>
    /// Creates a new game from specified game state
    /// </summary>
    /// <param name="state">State used to initialize the game</param>
    /// <returns></returns>
    Game(GameState state);
    
	/// <summary>
    /// Run the game
    /// </summary>
    void Run();
    
    /// <summary>
    /// Attach observer to the game 
    /// </summary>
    /// <param name="observer">Observer object (e.g. a GUI) that observes changes to the game</param>
    void Attach(IObserver* observer);
    
	/// <summary>
    /// Detach observer from the game
    /// </summary>
    /// <param name="observer">Observer to detach</param>
    void Detach(IObserver* observer);

    /// <summary>
    /// Send keyboard input to game
    /// </summary>
    /// <param name="input">input (move down, left, right, rotate)</param>
    void SendGameInput(GameInput input);

	/// <returns>True if game is finished</returns>
	bool IsFinished();

	/// Quits the game
	void QuitGame();

private:
    /// <summary>
    /// Executes one time step (moving current piece down 1)
    /// </summary>
    void ExecuteTimeStep();
	bool IsGameFinished();
    GamePiece NextPiece();
    bool IsPieceBlocked();
    void AddPieceToBoard();
    void ClearAndScore();

    /// <summary>
    /// Converts a y coordinate from the frame of the piece to a y coordinate on the board
    /// </summary>
    /// <param name="pieceYCoordinate">The y coordinate of the current piece</param>
    /// <returns>Y coordinate in board reference frame</returns>
    int PieceToBoardYCoordinate(int pieceYCoordinate);

    /// <summary>
    ///Converts a x coordinate form the frame of the piece to a x coordinate on the board
    /// </summary>
    /// <param name="pieceXCoordinate"></param>
    /// <returns></returns>
    int PieceToBoardXCoordinate(int pieceXCoordinate);

    /// <summary>
    /// Moves the current GamePiece down (if possible)
    /// </summary>
    void MoveCurrentPieceDown();

    /// <summary>
    /// Moves the current GamePiece left (if possible)
    /// </summary>
    void MoveCurrentPieceLeft();

    /// <summary>
    /// Moves the current GamePiece right (if possible)
    /// </summary>
    void MoveCurrentPieceRight();

    /// <summary>
    /// Rotates the current GamePiece (if possible)
    /// </summary>
    void RotateCurrentPiece();

    GameState gameState_;
    std::vector<IObserver*> observers;
    std::mutex mutex_;
};
#endif //CPP_TETRIS_GAMELOGIC_H