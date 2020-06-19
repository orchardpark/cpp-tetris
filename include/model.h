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

#endif //CPP_TETRIS_MODEL_H
#include <vector>

enum Orientation{up, down, left, right};
enum Shape{i_block=1, j_block=2, l_block=3, o_block=4, s_block=5, t_block=6, z_block=7};
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

typedef std::vector<std::vector<Shape>> GameBoard;

GameBoard InitBoard();