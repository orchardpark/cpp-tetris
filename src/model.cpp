#include "../include/model.h"

void GamePiece::rotate() {
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

GamePiece::GamePiece(Shape shape, Orientation orientation) : orientation_(orientation), shape_(shape), offset_(0) {
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

GameBoard InitBoard(){
    std::vector<std::vector<Shape>> v(19);
    for(int i=0; i<19; i++)
        v[i] = std::vector<Shape>(10); // initialize with NULL
    return v;
}

