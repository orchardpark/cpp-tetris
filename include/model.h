/**
 * @file model.cc
 * @brief Models the game pieces and board.
 *
 *
 * The board is represented as a matrix [row, column].
 * Row 0 Column 0 refers to the upper left of the board.
 * A game piece is represented as a matrix [row, column],
 * where 0 (false) represents an empty square and 1 (true)
 * represents an occupied square.
 * Equal to the board, Row 0 Column 0 refers to the upper left of a game piece.
 */
#ifndef CPP_TETRIS_MODEL_H
#define CPP_TETRIS_MODEL_H

#include <vector>
#include "../include/utils.h"
#include <string>

enum class Orientation{up, down, left, right};
enum class Shape{empty, iBlock, jBlock, lBlock, oBlock, sBlock, tBlock, zBlock};
std::string ShapeToString(Shape s);
struct ShapeComparison {
    bool operator()(Shape const& lhs, Shape const& rhs) const 
    {
        return to_underlying(lhs) < to_underlying(rhs);
    }
};
typedef bool Occupancy; // 0=>empty 1=>occupied
const int NumRowsBoard=19;
const int NumColumnsBoard=10;

class GamePiece{
public:
    /// Instantiates a new GamePiece
    /// \param shape The block shape
    /// \param orientation The orientation of the block
    GamePiece(Shape shape, Orientation orientation);
    /*
    * Rotates the piece 90 degrees clockwise
    */
    void Rotate();
	/*
    * Get the representation for this piece
    * The representation will be a boolean matrix
    * where 0 represents empty space and 1 is a block of the piece
    * (0,0) represents the top left corner
    */
    std::vector<std::vector<Occupancy>> GetRepresentation();
    /*
    * Returns the block shape
    */
    Shape GetShape();

private:
    std::vector<std::vector<Occupancy>> GetIRepresentation();
    std::vector<std::vector<Occupancy>> GetJRepresentation();
    std::vector<std::vector<Occupancy>> GetLRepresentation();
    std::vector<std::vector<Occupancy>> GetORepresentation();
    std::vector<std::vector<Occupancy>> GetSRepresentation();
    std::vector<std::vector<Occupancy>> GetTRepresentation();
    std::vector<std::vector<Occupancy>> GetZRepresentation();

    Shape shape_;
    Orientation orientation_;
};

class GameBoard{

public:
    GameBoard();
    std::vector<Shape>& operator[](int);
    std::vector<std::vector<Shape>> GetRepresentation();
private:
    std::vector<std::vector<Shape>> representation_;
};

struct GameState {
    GameState(GameBoard board, GamePiece piece, int score, int level, int offsetX, bool isFinished);
    GameBoard board;
    GamePiece currentPiece;

    /// <summary>
    /// Gets the the horizontal offset
    /// @invariant 0<=result<NumColumns-GetRepresentation().size()
    /// </summary>
    int currentPieceOffsetX;
    
    /// <summary>
    /// Gets the vertical offset. If the yOffset is 0, that means that the bottom of the representation
    /// matches up with the top of the board. More precisely, the y-coordinate (in the frame of the board)
    /// of the bottom of the representation (that is, the highest numbered row in the representation).
    /// will be at position -1.
    /// </summary>
    int currentPieceOffsetY;
    int score;
    int level;
    bool isFinished;
};


#endif //CPP_TETRIS_MODEL_H
