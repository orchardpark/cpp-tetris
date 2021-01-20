#include "../include/gamelogic.h"
std::random_device device;
std::mt19937 generator(device());


Game::Game() : gameState_(GameState(GameBoard(), NextPiece(), 0, 1)){
    CreateRandomGenerator();
}

Game::Game(GameState state) : gameState_(std::move(state)){
    CreateRandomGenerator();
}

void Game::Run() {
    // Initialize first piece
    gameState_.currentPiece = NextPiece();
	std::uniform_int_distribution<int> offsetX_distribution(0, NumColumnsBoard-1-gameState_.currentPiece.GetRepresentation().size());
	gameState_.currentPieceOffsetX = offsetX_distribution(generator);
	gameState_.currentPieceOffsetY = 0;

    // Run Game Loop
	while (!IsGameFinished()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/gameState_.level));
        ExecuteTimeStep();
	}
}

void Game::Attach(IObserver* observer) {
    observers.emplace_back(observer);
}

void Game::Detach(IObserver* observer) {
    //@TODO
}

void Game::CreateRandomGenerator() {
}

GamePiece Game::NextPiece() {
    std::uniform_int_distribution<int> shape_distribution(1,7);
    std::uniform_int_distribution<int> orientation_distribution(0, 3);
    return GamePiece(
            (Shape)shape_distribution(generator),
            (Orientation)orientation_distribution(generator)
            );
}

bool Game::IsGameFinished() {
    // In order for the game to be finished, the piece must be blocked and stick out
    // the top of the game board. That is, the lowest y-coordinate of an non-empty square
    // in the reference frame of the piece is lower than 0 in the reference frame of the board
    bool finished= false;
    if(IsPieceBlocked()){
        auto representation = gameState_.currentPiece.GetRepresentation();

        auto FindLowestNonEmptyY = [representation]() {
            int lowest = 0;
            for (; lowest < representation.size(); lowest++) {
                bool empty = true;
                for(unsigned int i=0; i<representation[lowest].size() && empty; i++){
                    empty = !representation[lowest][i];
                }
            }
            return lowest;
        };

        auto lowestNonEmptyY = FindLowestNonEmptyY();
        if(PieceToBoardYCoordinate(lowestNonEmptyY) < 0) finished=true;
    }
    return finished;

}

bool Game::IsPieceBlocked() {
    // A piece is blocked if either the floor of the board or already placed pieces
    // are directly below one of its non-empty squares.
    bool blocked = false;
    auto representation = gameState_.currentPiece.GetRepresentation();
    for(int j=0; j<representation.size() && !blocked; j++){
        for(int i=0; i<representation[j].size() && !blocked; i++){
            // non-empty
            if(representation[j][i]){
               int positionBelowY = PieceToBoardYCoordinate(j)+1;
               int positionBelowX = PieceToBoardXCoordinate(i);
               // not on the board
               if(positionBelowY < 0)
                   ;
               // floor or already in place piece
               else if (positionBelowY >= NumRowsBoard || gameState_.board[positionBelowY][positionBelowX] != Shape::empty) blocked = true;
            }
        }
    }
    return blocked;
}

void Game::ClearAndScore() {
    // find lines to be cleared
    std::vector<int> clearRows;
    auto representation = gameState_.currentPiece.GetRepresentation();

    auto HasNonEmptyRow = [representation](int j) {
        bool hasNonEmpty = false;
        for (int i = 0; i < representation[j].size() && !hasNonEmpty; i++) {
            hasNonEmpty = representation[j][i];
        }
        return hasNonEmpty;
    };

    for(unsigned int j=0; j<representation.size(); j++){
        if (!HasNonEmptyRow(j)) 
            continue;
        int positionY = PieceToBoardYCoordinate(j);
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
        gameState_.board[clearRows.back()+1] = std::vector<Shape>(NumColumnsBoard, Shape::empty);

    // score clears
    if(clearRows.size()==1) gameState_.score += 40;
    else if(clearRows.size()==2) gameState_.score += 100;
    else if(clearRows.size()==3) gameState_.score += 300;
    else if(clearRows.size()==4) gameState_.score += 1200;

}

void Game::AddPieceToBoard() {
    auto representation = gameState_.currentPiece.GetRepresentation();
    Shape shape = gameState_.currentPiece.GetShape();
    for(unsigned int j=0; j<representation.size(); j++){
        for(unsigned int i=0; i<representation[j].size(); i++){
            int positionY = PieceToBoardYCoordinate(j);
            int positionX = PieceToBoardXCoordinate(i);
            // non-empty
            if(representation[j][i] && positionY>0){
                gameState_.board[positionY][positionX]=shape;
            }
        }
    }
}

int Game::PieceToBoardYCoordinate(int pieceYCoordinate) {
    return gameState_.currentPieceOffsetY + pieceYCoordinate - gameState_.currentPiece.GetRepresentation().size();
}

int Game::PieceToBoardXCoordinate(int pieceXCoordinate) {
    return gameState_.currentPieceOffsetX + pieceXCoordinate;
}

bool Game::ExecuteTimeStep() {
    MoveCurrentPieceDown();
    bool blocked = IsPieceBlocked();
    if(blocked){
        if(IsGameFinished()) return false;
        AddPieceToBoard();
        ClearAndScore();
        gameState_.currentPiece = NextPiece();
		std::uniform_int_distribution<int> offsetX_distribution(0, NumColumnsBoard-1-gameState_.currentPiece.GetRepresentation().size());
        gameState_.currentPieceOffsetX = offsetX_distribution(generator);
        gameState_.currentPieceOffsetY = 0;
    }
    for (auto observer : observers) {
        observer->Update(gameState_);
    }
    return true;
}

void Game::SendGameInput(GameInput input) {
	switch (input) {
	case GameInput::MOVE_DOWN:
        MoveCurrentPieceDown();
		break;
    case GameInput::MOVE_LEFT:
        MoveCurrentPieceLeft();
        break;
    case GameInput::MOVE_RIGHT:
        MoveCurrentPieceRight();
        break;
    case GameInput::ROTATE:
        gameState_.currentPiece.Rotate();
        break;
	}
}

void Game::MoveCurrentPieceLeft() {
    auto representation = gameState_.currentPiece.GetRepresentation();

    // check if left is free
    for (int j = 0; j < representation.size(); j++) {
        int leftYCoordinate = PieceToBoardYCoordinate(j);
        for (int i = 0; i < representation[j].size(); i++) {
            if (representation[j][i]) {
				int leftXCoordinate = PieceToBoardXCoordinate(i) - 1;
				if (leftXCoordinate > 0) {
					if (gameState_.board[leftYCoordinate][leftXCoordinate] != Shape::empty) return;
				}
				break;
            }
        }
    }

    // find leftmost nonzero
    int leftMost = representation.size();
    for (int j = 0; j < representation.size(); j++) {
        for (int i = 0; i < representation[j].size(); i++) {
            if (representation[j][i]) {
                if (i < leftMost) leftMost = i;
            }
        }
    }
    if(gameState_.currentPieceOffsetX+leftMost > 0) gameState_.currentPieceOffsetX--;
}

void Game::MoveCurrentPieceRight() {
    auto representation = gameState_.currentPiece.GetRepresentation();
    // check if right is free
    for (int j = 0; j < representation.size(); j++) {
        int rightYCoordinate = PieceToBoardYCoordinate(j);
        for (int i = representation.size() - 1; i >= 0; i--) {
            if (representation[j][i]) {
                int rightXCoordinate = PieceToBoardXCoordinate(i) + 1;
                if (rightXCoordinate < representation.size()) {
                    if (gameState_.board[rightYCoordinate][rightXCoordinate] != Shape::empty) return;
                }
            }
        }
    }
    // find rightmost nonzero
    int rightMost = 0;
    for (int j = 0; j < representation.size(); j++) {
        for (int i = 0; i < representation[j].size(); i++) {
            if (representation[j][i]) {
                if (i > rightMost) rightMost = i;
            }
        }
    }
    if(gameState_.currentPieceOffsetX+rightMost < NumColumnsBoard-1) gameState_.currentPieceOffsetX++;
}

void Game::MoveCurrentPieceDown() {
    if (!IsPieceBlocked())
        gameState_.currentPieceOffsetY++;
}
