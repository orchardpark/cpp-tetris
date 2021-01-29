#include "../include/gui.h"

void GUI::StartGame(std::shared_ptr<Game> game)
{
	game->Run();
}

void GUI::RenderText(int x, int y, const char *text, float scaleFactor) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 0, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *(&texture) = SDL_CreateTextureFromSurface(gRenderer, surface);
    text_width = surface->w*scaleFactor;
    text_height = surface->h*scaleFactor;
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    // free resources
    SDL_FreeSurface(surface);

    /* Use TTF textures. */
    SDL_RenderCopy(gRenderer, texture, nullptr, rect);
    SDL_RenderPresent(gRenderer);
}


void GUI::RunKeyboardController(std::shared_ptr<Game> game)
{
	while (!game->IsFinished()) {
		SDL_Event event;
		/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
        /* more events on the event queue, our while loop will exit when */
        /* that occurs.                                                  */
        while (SDL_PollEvent(&event) && !game->IsFinished()) {
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
                    break;
                case SDL_QUIT:
                    game->QuitGame();
                    break;
                default:
                    break;
            }
        }
    }
};

void GUI::Run()
{
    InitializeSDL2();
    auto g = std::make_shared<Game>();
	g->Attach(this);
	std::thread gameThread (StartGame, g);
	std::thread controllerThread(RunKeyboardController, g);
    controllerThread.join();
	gameThread.join();
	DeInitializeSDL2();
}

void GUI::Update(const GameState& state)
{
	RenderState(state);
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
    auto gamePiece = state.currentPiece;
    auto score = state.score;
    auto level = state.level;
    auto board = state.board;
    std::string title ="CPP TETRIS";
    std::string scoreString = "SCORE " + std::to_string(score);
    std::string levelString = "LEVEL " + std::to_string(level);
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

    RenderText(0,0,title.c_str(), 1);
    RenderText(0, 100, scoreString.c_str(), 0.5);
    RenderText(0,125,levelString.c_str(), 0.5);
    RenderBoard(boardRepresentation);
    SDL_RenderClear(gRenderer);

}

void GUI::RenderSquare(int row, int column, Shape s){
    SDL_Texture *img = nullptr;
    img = IMG_LoadTexture(gRenderer, "../textures/yellow.png");
    int w,h;
    SDL_QueryTexture(img, nullptr, nullptr, &w, &h);
    SDL_Rect texr;
    texr.x = 200;
    texr.y = 200;
    texr.h = h;
    texr.w = w;
    SDL_RenderCopy(gRenderer, img, nullptr, &texr);
    SDL_RenderPresent(gRenderer);
}

void GUI::RenderBoard(std::vector<std::vector<Shape>>& board) {
    RenderSquare(0,0,Shape::iBlock);
}

void GUI::InitializeSDL2() {
    // init sdl2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
        exit(1);
    }
    // init ttf
    if(TTF_Init() < 0){
        fprintf(stderr, "Could not initialize TTF: %s\n", TTF_GetError());
        exit(1);
    }
    int SCREEN_WIDTH = 1024;
    int SCREEN_HEIGHT = 786;

    // init window
    gWindow = SDL_CreateWindow("CPP Tetris",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        exit(1);
    }

    // init renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr)
    {
        fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }

    // init font
    font = TTF_OpenFont("../fonts/FreeSans.ttf", 48);
    if(!font) {
        fprintf(stderr,"TTF_OpenFont: %s\n", TTF_GetError());
    }

    // init rect
    rect = new SDL_Rect();
}

void GUI::DeInitializeSDL2() {
    SDL_DestroyTexture(texture);
    delete rect;
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

