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

enum class Orientation{up, down, left, right};
enum class Shape{empty, iBlock, jBlock, lBlock, oBlock, sBlock, tBlock, zBlock};
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
    GamePiece(Shape shape, Orientation orientation, int offsetX);
    void Rotate();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    std::vector<std::vector<Occupancy>> GetRepresentation();
    int GetOffsetY();
    int GetOffsetX();
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
    int offsetX_;
    int offsetY_;
};

class GameBoard{

public:
    GameBoard();
    std::vector<Shape>& operator[](int);
private:
    std::vector<std::vector<Shape>> representation_;
};

struct GameState {
    GameBoard board;
    GamePiece currentPiece;
    int score;
    int level;
};
#endif //CPP_TETRIS_MODEL_H
