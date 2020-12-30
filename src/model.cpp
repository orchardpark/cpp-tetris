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
    case Shape::i_block:
            return GetIRepresentation();
        case Shape::j_block:
            return GetJRepresentation();
        case Shape::l_block:
            return GetLRepresentation();
        case Shape::o_block:
            return GetORepresentation();
        case Shape::s_block:
            return GetSRepresentation();
        case Shape::t_block:
            return GetTRepresentation();
        case Shape::z_block:
            return GetZRepresentation();
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
    case Orientation::left:
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
    case Orientation::left:
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
    case Orientation::left:
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
    case Orientation::left:
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
    case Orientation::left:
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
    case Orientation::left:
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

GameBoard::GameBoard(){
    std::vector<std::vector<Shape>> v(NumRowsBoard);
    for(int i=0; i<NumRowsBoard; i++)
        v[i] = std::vector<Shape>(NumColumnsBoard, Shape::empty);
    representation_ = std::move(v);
}

void GameBoard::attach(std::shared_ptr<IObserver> observer) {

}

void GameBoard::detach(std::shared_ptr<IObserver> observer) {

}

std::vector<Shape>& GameBoard::operator[](int i) {
    return representation_[i];
}
