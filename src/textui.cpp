#include "../include/textui.h"

//The window renderer
SDL_Renderer* gRenderer = NULL;

void StartGame(std::shared_ptr<Game> game)
{
	game->Run();
}

/*
* Sets up the screen
*/
void Initialize_SDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
		exit(-1);
	}

	SDL_Window* gWindow = NULL;
	SDL_Surface* screenSurface = NULL;
	int SCREEN_WIDTH = 1024;
	int SCREEN_HEIGHT = 786;

	gWindow = SDL_CreateWindow("Sphere Rendering",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		exit(1);
	}

	screenSurface = SDL_GetWindowSurface(gWindow);

	if (!screenSurface) {
		fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}

	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}
void RunKeyboardController(std::shared_ptr<Game> game)
{
	Initialize_SDL();

	while (!game->IsFinished()) {
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

