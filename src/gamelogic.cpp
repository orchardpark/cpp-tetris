#include "../include/gamelogic.h"
Game::Game() : gameState_(GameState(GameBoard(), NextPiece(), 0, 1)){
}

Game::Game(GameState state) : gameState_(state){
}

void Game::Run() {
	while (!IsGameFinished()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        ExecuteTimeStep();
	}
}

void Game::Attach(IObserver* observer) {
    observers.emplace_back(observer);
}

void Game::Detach(IObserver* observer) {
    //@TODO
}

GamePiece Game::NextPiece() {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> shape_distribution(1,7);
    std::uniform_int_distribution<int> orientation_distribution(0, 3);
    std::uniform_int_distribution<int> offsetX_distribution(0, NumColumnsBoard-1-4);
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
        auto representation = gameState_.currentPiece.GetRepresentation();

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
        if(gameState_.currentPiece.GetOffsetY()-highestNonEmptyY < 0) finished=true;
    }
    return finished;

}

bool Game::IsPieceBlocked() {
    // A piece is blocked if either the floor of the board or already placed pieces
    // are directly below one of its non-empty squares.
    bool blocked = false;
    auto representation = gameState_.currentPiece.GetRepresentation();
    int offsetY = gameState_.currentPiece.GetOffsetY();
    int offsetX = gameState_.currentPiece.GetOffsetX();
    for(unsigned int j=0; j<representation.size() && !blocked; j++){
        for(unsigned int i=0; i<representation[j].size() && !blocked; i++){
            // non-empty
            if(representation[j][i]){
               int positionBelowY = offsetY-(int)j+1;
               int positionBelowX = offsetX+(int)i;
               if (gameState_.board[0][0] != Shape::empty) {
                   std::cout << "hello world\n";
               }
               // floor or already in place piece
               if (positionBelowY >= NumRowsBoard || gameState_.board[positionBelowY][positionBelowX] != Shape::empty) blocked = true;
            }
        }
    }
    return blocked;
}

void Game::ClearAndScore() {
    // find lines to be cleared
    std::vector<int> clearRows;
    auto representation = gameState_.currentPiece.GetRepresentation();
    int offsetY = gameState_.currentPiece.GetOffsetY();
    for(unsigned int j=0; j<representation.size(); j++){
        int positionY = offsetY-(int)j;
        bool full = true;
        for(unsigned int i=0; i<NumColumnsBoard && full; i++){
            full = gameState_.board[positionY][i] != Shape::empty;
        }
        if(full) clearRows.push_back(positionY);
    }
    for(int row : clearRows){
        gameState_.board[row] = std::move(gameState_.board[row+1]);
    }
    if(!clearRows.empty() && clearRows.back()>0)
        gameState_.board[clearRows.back()+1LL] = std::vector<Shape>(NumColumnsBoard, Shape::empty);
    // score clears
    if(clearRows.size()==1) gameState_.score += 40;
    else if(clearRows.size()==2) gameState_.score += 100;
    else if(clearRows.size()==3) gameState_.score += 300;
    else if(clearRows.size()==4) gameState_.score += 1200;

}

void Game::AddPieceToBoard() {
    auto representation = gameState_.currentPiece.GetRepresentation();
    int offsetY = gameState_.currentPiece.GetOffsetY();
    int offsetX = gameState_.currentPiece.GetOffsetX();
    Shape shape = gameState_.currentPiece.GetShape();
    for(unsigned int j=0; j<representation.size(); j++){
        for(unsigned int i=0; i<representation[j].size(); i++){
            int positionY = offsetY-(int)j;
            int positionX = offsetX+(int)i;
            // non-empty
            if(representation[j][i] && positionY>0){
                gameState_.board[positionY][positionX]=shape;
            }
        }
    }
}

bool Game::ExecuteTimeStep() {
    gameState_.currentPiece.MoveDown();
    bool blocked = IsPieceBlocked();
    if(blocked){
        if(IsGameFinished()) return false;
        AddPieceToBoard();
        ClearAndScore();
        gameState_.currentPiece = NextPiece();
    }
    for (auto observer : observers) {
        observer->Update(gameState_);
    }
    return true;
}
