#include "../include/model.h"

void GamePiece::Rotate() {
    switch (orientation_) {
        case Orientation::up:
            orientation_ = Orientation::right;
            break;
        case Orientation::right:
            orientation_ = Orientation::down;
            break;
        case Orientation::down:
            orientation_ = Orientation::left;
            break;
        case Orientation::left:
            orientation_ = Orientation::up;
            break;
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetRepresentation() {
    switch (shape_) {
    case Shape::iBlock:
            return GetIRepresentation();
        case Shape::jBlock:
            return GetJRepresentation();
        case Shape::lBlock:
            return GetLRepresentation();
        case Shape::oBlock:
            return GetORepresentation();
        case Shape::sBlock:
            return GetSRepresentation();
        case Shape::tBlock:
            return GetTRepresentation();
        case Shape::zBlock:
            return GetZRepresentation();
        default:
            return std::vector<std::vector<Occupancy>>{{0}};
    }
}

GamePiece::GamePiece(Shape shape, Orientation orientation, int offsetX) : orientation_(orientation), shape_(shape), offsetX_(offsetX),offsetY_(0) {
}

std::vector<std::vector<Occupancy>> GamePiece::GetIRepresentation() {
    switch (orientation_) {
    case Orientation::up:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0,0},
                     {1,1,1,1},
                     {0,0,0,0},
                     {0,0,0,0}};
    case Orientation::right:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,1,0},
                     {0,0,1,0},
                     {0,0,1,0},
                     {0,0,1,0}};
    case Orientation::down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0,0},
                     {0,0,0,0},
                     {1,1,1,1},
                     {0,0,0,0}};
    default:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0,0},
                     {0,1,0,0},
                     {0,1,0,0},
                     {0,1,0,0}};
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetJRepresentation() {
    switch (orientation_) {
    case Orientation::up:
            return std::vector<std::vector<Occupancy>>
                    {{1,0,0},
                     {1,1,1},
                     {0,0,0},
                     };
    case Orientation::right:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,1},
                     {0,1,0},
                     {0,1,0},
                    };
    case Orientation::down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {1,1,1},
                     {0,0,1},
                    };
    default:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {0,1,0},
                     {1,1,0},
                    };
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetLRepresentation() {
    switch (orientation_) {
    case Orientation::up:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,1},
                     {1,1,1},
                     {0,0,0},
                    };
    case Orientation::right:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {0,1,0},
                     {0,1,1},
                    };
    case Orientation::down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {1,1,1},
                     {1,0,0},
                    };
    default:
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
    case Orientation::up:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,1},
                     {1,1,0},
                     {0,0,0},
                    };
    case Orientation::right:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {0,1,1},
                     {0,0,1},
                    };
    case Orientation::down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {0,1,1},
                     {1,1,0},
                    };
    default:
            return std::vector<std::vector<Occupancy>>
                    {{1,0,0},
                     {1,1,0},
                     {0,1,0},
                    };
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetTRepresentation() {
    switch (orientation_) {
    case Orientation::up:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {1,1,1},
                     {0,0,0},
                    };
    case Orientation::right:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {0,1,1},
                     {0,1,0},
                    };
    case Orientation::down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {1,1,1},
                     {0,1,0},
                    };
    default:
            return std::vector<std::vector<Occupancy>>
                    {{0,1,0},
                     {1,1,0},
                     {0,1,0},
                    };
    }
}

std::vector<std::vector<Occupancy>> GamePiece::GetZRepresentation() {
    switch (orientation_) {
    case Orientation::up:
            return std::vector<std::vector<Occupancy>>
                    {{1,1,0},
                     {0,1,1},
                     {0,0,0},
                    };
    case Orientation::right:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,1},
                     {0,1,1},
                     {0,1,0},
                    };
    case Orientation::down:
            return std::vector<std::vector<Occupancy>>
                    {{0,0,0},
                     {1,1,0},
                     {0,1,1},
                    };
    default:
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
    if(offsetX_ < NumColumnsBoard-1-4) offsetX_++;
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

std::string ShapeToString(Shape shape) {
    switch (shape)
    {
    case Shape::empty:
        return "-";
    case Shape::iBlock:
        return "I";
    case Shape::jBlock:
        return "J";
    case Shape::lBlock:
        return "L";
    case Shape::oBlock:
        return "O";
    case Shape::sBlock:
        return "S";
    case Shape::tBlock:
        return "T";
    case Shape::zBlock:
        return "Z";
    default:
        return "";
    }
}

GameBoard::GameBoard(){
    std::vector<std::vector<Shape>> v(NumRowsBoard);
    for(int i=0; i<NumRowsBoard; i++)
        v[i] = std::vector<Shape>(NumColumnsBoard, Shape::empty);
    representation_ = std::move(v);
}

std::vector<Shape>& GameBoard::operator[](int i) {
    return representation_[i];
}

GameState::GameState(GameBoard board, GamePiece piece, int score, int level) : board(board), currentPiece(piece), score(score), level(level) {
}
