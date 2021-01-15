#include "../include/textui.h"

void StartGame(std::unique_ptr<Game> g) 
{
	g->Run();
}

void RunKeyboardController(){

};

void TextUI::Run() 
{
	auto g = std::make_unique<Game>();
	g->Attach(this);
	std::thread t (StartGame, std::move(g));
	t.join();
}

void TextUI::Update(const GameState& state) 
{
	std::cout << StateToString(state);
}

std::string TextUI::StateToString(const GameState &state)
{
	auto gamePiece = state.currentPiece;
	auto score = state.score;
	auto level = state.level;
	auto board = state.board;
	std::string title =
	                          "CPP TETRIS -------------------------------\n";
	std::string scoreString = "SCORE " + std::to_string(score) + "\n";
	std::string levelString = "LEVEL " + std::to_string(level) + "\n";
	auto representation = gamePiece.GetRepresentation();
    auto boardRepresentation = board.GetRepresentation();
	for(int j=0; j<representation.size(); j++){
	    for(int i=0; i<representation[j].size(); i++){
	        if(representation[j][i]){
	            int yCoordinate = gamePiece.GetOffsetY()+j-(int)representation.size()+1;
	            int xCoordinate = gamePiece.GetOffsetX()+i;
	            if(yCoordinate>=0){
	                boardRepresentation[yCoordinate][xCoordinate] = Shape::iBlock;
	            }
	        }
	    }
	}
	std::string boardString;
	for(int j=0;j<boardRepresentation.size(); j++){
	    for(int i=0; i<boardRepresentation[j].size(); i++){
	        boardString += ShapeToString(boardRepresentation[j][i]);
	    } boardString += "\n";
	}


	return title + scoreString + levelString + boardString;
}

