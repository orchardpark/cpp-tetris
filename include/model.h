/**
 * @file model.cc
 * @brief Models the game pieces and board.
 *
 *
 * The board is represented as a matrix [row, column].
 * Row 0 Column 0 refers to the lower left of the board.
 */
#ifndef CPP_TETRIS_MODEL_H
#define CPP_TETRIS_MODEL_H

#endif //CPP_TETRIS_MODEL_H
#include <vector>

enum Orientation{up, down, left, right};
enum Shape{i_block=1, j_block=2, l_block=3, o_block=4, s_block=5, t_block=6, z_block=7};
typedef bool Occupancy; // 0=>empty 1=>occupied

class GamePiece{
public:
    GamePiece(Shape shape, Orientation orientation);
    void rotate();
    std::vector<std::vector<Occupancy>> GetRepresentation();

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
    int offset_;
};

typedef std::vector<std::vector<Shape>> GameBoard;

GameBoard InitBoard();