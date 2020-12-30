#include "../include/gamelogic.h"

Game::Game() : currentPiece_(NextPiece()), score_(0), board_(GameBoard()), level_(1) {
}

GamePiece Game::NextPiece() {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> shape_distribution(1,7);
    std::uniform_int_distribution<int> orientation_distribution(0, 3);
    std::uniform_int_distribution<int> offsetX_distribution(0, NumColumnsBoard-1);
    return GamePiece(
            (Shape)shape_distribution(generator),
            (Orientation)orientation_distribution(generator),
            offsetX_distribution(generator));
}

bool Game::IsGameFinished() {
    // In order for the game to be finished, the piece must be blocked and stick out
    // the top of the game board. That is, the highest y-coordinate an non-empty square
    // of the piece is lower than 0.
    bool finished= false;
    if(IsPieceBlocked()){
        auto representation = currentPiece_.GetRepresentation();

        auto FindHighestNonEmptyY = [representation]() {
            int highest = representation.size() - 1;
            for (; highest >= 0; highest--) {
                bool empty = true;
                for(unsigned int i=0; i<representation[highest].size() && empty; i++){
                    empty = !representation[highest][i];
                }
            }
            return highest;
        };

        auto highestNonEmptyY = FindHighestNonEmptyY();
        if(currentPiece_.GetOffsetY()-highestNonEmptyY < 0) finished=true;
    }
    return finished;

}

bool Game::IsPieceBlocked() {
    // A piece is blocked if either the floor of the board or already placed pieces
    // are directly below one of its non-empty squares.
    bool blocked = false;
    auto representation = currentPiece_.GetRepresentation();
    int offsetY = currentPiece_.GetOffsetY();
    int offsetX = currentPiece_.GetOffsetX();
    for(unsigned int j=0; j<representation.size() && !blocked; j++){
        for(unsigned int i=0; i<representation[j].size() && !blocked; i++){
            // non-empty
            if(representation[j][i]){
               int positionBelowY = offsetY-(int)j+1;
               int positionBelowX = offsetX+(int)i;
               // floor or already in place piece
               if (positionBelowY >= 19 || board_[positionBelowY][positionBelowX] != Shape::empty) blocked = true;
            }
        }
    }
    return blocked;
}

void Game::ClearAndScore() {
    // find lines to be cleared
    std::vector<int> clearRows;
    auto representation = currentPiece_.GetRepresentation();
    int offsetY = currentPiece_.GetOffsetY();
    for(unsigned int j=0; j<representation.size(); j++){
        int positionY = offsetY-(int)j;
        bool full = true;
        for(unsigned int i=0; i<NumColumnsBoard && full; i++){
            full = board_[positionY][i] != Shape::empty;
        }
        if(full) clearRows.push_back(positionY);
    }
    for(int row : clearRows){
        board_[row] = std::move(board_[row+1]);
    }
    if(!clearRows.empty() && clearRows.back()>0)
        board_[clearRows.back()+1LL] = std::vector<Shape>(NumColumnsBoard, Shape::empty);
    // score clears
    if(clearRows.size()==1) score_ += 40;
    else if(clearRows.size()==2) score_ += 100;
    else if(clearRows.size()==3) score_ += 300;
    else if(clearRows.size()==4) score_ += 1200;

}

void Game::AddPieceToBoard() {
    auto representation = currentPiece_.GetRepresentation();
    int offsetY = currentPiece_.GetOffsetY();
    int offsetX = currentPiece_.GetOffsetX();
    Shape shape = currentPiece_.GetShape();
    for(unsigned int j=0; j<representation.size(); j++){
        for(unsigned int i=0; i<representation[j].size(); i++){
            int positionY = offsetY-(int)j;
            int positionX = offsetX+(int)i;
            // non-empty
            if(representation[j][i] && positionY>0){
                board_[positionY][positionX]=shape;
            }
        }
    }
}

bool Game::ExecuteTimeStep() {
    currentPiece_.MoveDown();
    bool blocked = IsPieceBlocked();
    if(blocked){
        if(IsGameFinished()) return false;
        AddPieceToBoard();
        ClearAndScore();
        currentPiece_ = NextPiece();
    }
    return true;
}
