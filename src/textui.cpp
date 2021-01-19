#include "../include/textui.h"

bool quit = false;

void StartGame(std::shared_ptr<Game> game)
{
	game->Run();
	quit = true;
}

/*
* Sets up the screen
*/
void Initialize_SDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
		exit(-1);
	}

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	int SCREEN_WIDTH = 1024;
	int SCREEN_HEIGHT = 786;

	window = SDL_CreateWindow("Sphere Rendering",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		exit(1);
	}

	screenSurface = SDL_GetWindowSurface(window);

	if (!screenSurface) {
		fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
}

void RunKeyboardController(std::shared_ptr<Game> game)
{
	Initialize_SDL();

	while (!quit) {
		SDL_Event event;
		/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
		/* more events on the event queue, our while loop will exit when */
		/* that occurs.                                                  */
		while (SDL_PollEvent(&event)) {
			/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_DOWN:
					game->SendGameInput(GameInput::MOVE_DOWN);
					break;
				case SDL_SCANCODE_UP:
					game->SendGameInput(GameInput::ROTATE);
					break;
				case SDL_SCANCODE_LEFT:
					game->SendGameInput(GameInput::MOVE_LEFT);
					break;
				case SDL_SCANCODE_RIGHT:
					game->SendGameInput(GameInput::MOVE_RIGHT);
					break;
				default:
					break;
				}
			}
		}
	}
};

void TextUI::Run() 
{
	auto g = std::make_shared<Game>();
	g->Attach(this);
	std::thread gameThread (StartGame, g);
	std::thread controllerThread(RunKeyboardController, g);
	gameThread.join();
	controllerThread.join();
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
	            int yCoordinate = state.currentPieceOffsetY+j-(int)representation.size();
	            int xCoordinate = state.currentPieceOffsetX+i;
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

