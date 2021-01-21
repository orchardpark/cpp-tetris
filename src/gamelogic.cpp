#include "../include/gamelogic.h"
std::random_device device;
std::mt19937 generator(device());


Game::Game() : gameState_(
    GameState(
        GameBoard(), 
        NextPiece(), 
        0, 
        1, 
		[]() {
			std::uniform_int_distribution<int> offsetX_distribution(0, NumColumnsBoard - 1 - 4);
			return offsetX_distribution(generator);
		}()
			))
{
}

Game::Game(GameState state) : gameState_(std::move(state)){
}

void Game::Run() {
    // Initialize first piece
    gameState_.currentPiece = NextPiece();
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

    std::vector<int> clearRows;
    auto representation = gameState_.currentPiece.GetRepresentation();

    auto HasNonEmptyRow = [representation](int j) {
        bool hasNonEmpty = false;
        for (int i = 0; i < representation[j].size() && !hasNonEmpty; i++) {
            hasNonEmpty = representation[j][i];
        }
        return hasNonEmpty;
    };

    // Find the rows to clear
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

    // Clear rows one by one starting from the top
    for (int i = 0; i < clearRows.size(); i++) {
        int row = clearRows[i];
        for (int j = row-1; j >=0; j--) {
            gameState_.board[j + 1] = std::move(gameState_.board[j]);
        }
        gameState_.board[0] = std::vector<Shape>(NumColumnsBoard, Shape::empty);
    }
    
    // score clears
    int numClearedRows = clearRows.size();
    if(numClearedRows==1) gameState_.score += 40;
    else if(numClearedRows==2) gameState_.score += 100;
    else if(numClearedRows==3) gameState_.score += 300;
    else if(numClearedRows==4) gameState_.score += 1200;

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
    bool gameFinished = false;
    mutex_.lock();
    MoveCurrentPieceDown();
    bool blocked = IsPieceBlocked();
    if(blocked){
        if (IsGameFinished()) {
            gameFinished = true;
        }
        else {
            AddPieceToBoard();
            ClearAndScore();
            gameState_.currentPiece = NextPiece();
            std::uniform_int_distribution<int> offsetX_distribution(0, NumColumnsBoard - 1 - gameState_.currentPiece.GetRepresentation().size());
            gameState_.currentPieceOffsetX = offsetX_distribution(generator);
            gameState_.currentPieceOffsetY = 0;
        }
    }
    for (auto observer : observers) {
        observer->Update(gameState_);
    }
    mutex_.unlock();
    return !gameFinished;
}

void Game::SendGameInput(GameInput input) {
    mutex_.lock();
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
        RotateCurrentPiece();
        break;
	}
    mutex_.unlock();
}

void Game::MoveCurrentPieceLeft() {
    auto representation = gameState_.currentPiece.GetRepresentation();

    // check if left is free
    for (int j = 0; j < representation.size(); j++) {
        int leftYCoordinate = PieceToBoardYCoordinate(j);
        if (leftYCoordinate >= 0) {
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
    if (gameState_.currentPieceOffsetX + leftMost > 0) {
        gameState_.currentPieceOffsetX--;
		for (auto observer : observers) {
			observer->Update(gameState_);
		}
	}
}

void Game::MoveCurrentPieceRight() {
    auto representation = gameState_.currentPiece.GetRepresentation();
    // check if right is free
    for (int j = 0; j < representation.size(); j++) {
        int rightYCoordinate = PieceToBoardYCoordinate(j);
        if (rightYCoordinate >= 0) {
            for (int i = representation.size() - 1; i >= 0; i--) {
                if (representation[j][i]) {
                    int rightXCoordinate = PieceToBoardXCoordinate(i) + 1;
                    if (rightXCoordinate < representation.size()) {
                        if (gameState_.board[rightYCoordinate][rightXCoordinate] != Shape::empty) return;
                    }
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
    if (gameState_.currentPieceOffsetX + rightMost < NumColumnsBoard - 1) {
		gameState_.currentPieceOffsetX++;
		for (auto observer : observers) {
			observer->Update(gameState_);
		}
	}
}

void Game::MoveCurrentPieceDown() {
    if (!IsPieceBlocked()) {
		gameState_.currentPieceOffsetY++;
		for (auto observer : observers) {
			observer->Update(gameState_);
		}
	}
}

void Game::RotateCurrentPiece() {
    gameState_.currentPiece.Rotate();
    auto representation = gameState_.currentPiece.GetRepresentation();
    bool isPossible = true;
    for (int j = 0; j < representation.size() && isPossible; j++) {
        for (int i = 0; i < representation[j].size() && isPossible; i++) {
            if (representation[j][i]) {
                int x = PieceToBoardXCoordinate(i);
                int y = PieceToBoardYCoordinate(j);
                // outside bounds
                if (x < 0 || x >= NumColumnsBoard || y < 0 || y >= NumRowsBoard) isPossible = false;
                // already occupied
                else if (gameState_.board[y][x] != Shape::empty) isPossible = false;
            }
        }
    }

    if (isPossible) {
        for (auto observer : observers) {
            observer->Update(gameState_);
        }
    }
    else {
        // Rotate back to original position
        for (int i = 0; i < 3; i++)
            gameState_.currentPiece.Rotate();
    }
    
}
