#include "../include/model.h"

void GamePiece::Rotate() {
    switch (orientation_) {
        case up:
            orientation_ = right;
            break;
        case right:
            orientation_ = down;
            break;
        case down:
            orientation_ = left;
            break;
        case left:
            orientation_ = up;
            break;
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetRepresentation() {
    switch (shape_) {
        case i_block:
            return GetIRepresentation();
        case j_block:
            return GetJRepresentation();
        case l_block:
            return GetLRepresentation();
        case o_block:
            return GetORepresentation();
        case s_block:
            return GetSRepresentation();
        case t_block:
            return GetTRepresentation();
        case z_block:
            return GetZRepresentation();
    }
}

GamePiece::GamePiece(Shape shape, Orientation orientation, int offsetX) : orientation_(orientation), shape_(shape), offsetX_(offsetX),offsetY_(0) {
}

std::vector<std::vector<Occupancy>> GamePiece::GetIRepresentation() {
    switch (orientation_) {
        case up:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0,0},
                     {1,1,1,1},
                     {0,0,0,0},
                     {0,0,0,0}};
        case right:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,1,0},
                     {0,0,1,0},
                     {0,0,1,0},
                     {0,0,1,0}};
        case down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0,0},
                     {0,0,0,0},
                     {1,1,1,1},
                     {0,0,0,0}};
        case left:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0,0},
                     {0,1,0,0},
                     {0,1,0,0},
                     {0,1,0,0}};
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetJRepresentation() {
    switch (orientation_) {
        case up:
            return std::vector<std::vector<Occupancy>>
                    {{1,0,0},
                     {1,1,1},
                     {0,0,0},
                     };
        case right:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,1},
                     {0,1,0},
                     {0,1,0},
                    };
        case down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {1,1,1},
                     {0,0,1},
                    };
        case left:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {0,1,0},
                     {1,1,0},
                    };
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetLRepresentation() {
    switch (orientation_) {
        case up:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,1},
                     {1,1,1},
                     {0,0,0},
                    };
        case right:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {0,1,0},
                     {0,1,1},
                    };
        case down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {1,1,1},
                     {1,0,0},
                    };
        case left:
            return std::vector<std::vector<Occupancy>>
                    {{1,1,0},
                     {0,1,0},
                     {0,1,0},
                    };
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetORepresentation() {
    return std::vector<std::vector<Occupancy>>{
            {1,1},
            {1,1}
    };
}

std::vector<std::vector<Occupancy>> GamePiece::GetSRepresentation() {
    switch (orientation_) {
        case up:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,1},
                     {1,1,0},
                     {0,0,0},
                    };
        case right:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {0,1,1},
                     {0,0,1},
                    };
        case down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {0,1,1},
                     {1,1,0},
                    };
        case left:
            return std::vector<std::vector<Occupancy>>
                    {{1,0,0},
                     {1,1,0},
                     {0,1,0},
                    };
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetTRepresentation() {
    switch (orientation_) {
        case up:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {1,1,1},
                     {0,0,0},
                    };
        case right:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {0,1,1},
                     {0,1,0},
                    };
        case down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {1,1,1},
                     {0,1,0},
                    };
        case left:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {1,1,0},
                     {0,1,0},
                    };
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetZRepresentation() {
    switch (orientation_) {
        case up:
            return std::vector<std::vector<Occupancy>>
                    {{1,1,0},
                     {0,1,1},
                     {0,0,0},
                    };
        case right:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,1},
                     {0,1,1},
                     {0,1,0},
                    };
        case down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {1,1,0},
                     {0,1,1},
                    };
        case left:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {1,1,0},
                     {1,0,0},
                    };
    }
}

void GamePiece::MoveLeft() {
    if(offsetX_ > 0) offsetX_--;
}

void GamePiece::MoveRight() {
    if(offsetX_ < NumColumnsBoard-1) offsetX_++;
}

int GamePiece::GetOffsetY() {
    return offsetY_;
}

int GamePiece::GetOffsetX() {
    return offsetX_;
}

Shape GamePiece::GetShape() {
    return shape_;
}

void GamePiece::MoveDown() {
    offsetY_++;
}

GameBoard InitBoard(){
    std::vector<std::vector<Shape>> v(NumRowsBoard);
    for(int i=0; i<NumRowsBoard; i++)
        v[i] = std::vector<Shape>(NumColumnsBoard, (Shape)NULL);
    return v;
}

