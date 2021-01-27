#include "../include/gui.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void StartGame(std::shared_ptr<Game> game)
{
	game->Run();
}

void Initialize_SDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
		exit(-1);
	}
	if(TTF_Init() < 0){
	    fprintf(stderr, "Could not initialize TTF: %s\n", TTF_GetError());
	    exit(-1);
	}
	int SCREEN_WIDTH = 1024;
	int SCREEN_HEIGHT = 786;

	gWindow = SDL_CreateWindow("CPP Tetris",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		exit(1);
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
}

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, const char *text,
                       TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 0, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;

}

void DeInitialize_SDL(){
    TTF_Quit();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void RunKeyboardController(std::shared_ptr<Game> game)
{
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

void GUI::Run()
{
    Initialize_SDL();
    TTF_Font *font = TTF_OpenFont("../fonts/FreeSans.ttf", 120);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    SDL_Texture *texture1, *texture2;
    SDL_Rect rect1, rect2;
    std::string text = "hello world";
    get_text_and_rect(gRenderer, 0, 0,text.c_str(),font,&texture1, &rect1);

    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(gRenderer);

    /* Use TTF textures. */
    SDL_RenderCopy(gRenderer, texture1, NULL, &rect1);
    SDL_RenderCopy(gRenderer, texture2, NULL, &rect2);

    SDL_RenderPresent(gRenderer);

    auto g = std::make_shared<Game>();
	g->Attach(this);
	std::thread gameThread (StartGame, g);
	std::thread controllerThread(RunKeyboardController, g);
	gameThread.join();
	controllerThread.join();

	DeInitialize_SDL();
}

void GUI::Update(const GameState& state)
{
	std::cout << StateToString(state);
}

std::string GUI::StateToString(const GameState &state)
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

void GUI::RenderState(const GameState &state) {

}

void GUI::InitializeSDL2() {

}

void GUI::DeInitializeSDL2() {

}

