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
}

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
    auto currentShape = gamePiece.GetShape();
    for(int j=0; j<representation.size(); j++){
        for(int i=0; i<representation[j].size(); i++){
            if(representation[j][i]){
                int yCoordinate = state.currentPieceOffsetY+j-(int)representation.size();
                int xCoordinate = state.currentPieceOffsetX+i;
                if(yCoordinate>=0){
                    boardRepresentation[yCoordinate][xCoordinate] = currentShape;
                }
            }
        }
    }

    SDL_RenderClear(gRenderer);
    RenderText(0,0,title.c_str(), 1);
    RenderText(0, 100, scoreString.c_str(), 0.5);
    RenderText(0,125,levelString.c_str(), 0.5);
    RenderBoard(boardRepresentation);
    SDL_RenderPresent(gRenderer);

}

void GUI::RenderSquare(int row, int column, Shape s){
    SDL_Rect texr;
    texr.x = 200+column*IMAGE_BLOCK_WIDTH;
    texr.y = 100+row*IMAGE_BLOCK_HEIGHT;
    texr.h = IMAGE_BLOCK_HEIGHT;
    texr.w = IMAGE_BLOCK_WIDTH;
    SDL_Texture *img;
    switch(s){
        case Shape::iBlock:
            img = imageTextures["cyan"];
            break;
        case Shape::lBlock:
            img = imageTextures["orange"];
            break;
        case Shape::jBlock:
            img = imageTextures["blue"];
            break;
        case Shape::oBlock:
            img = imageTextures["yellow"];
            break;
        case Shape::sBlock:
            img = imageTextures["green"];
            break;
        case Shape::tBlock:
            img = imageTextures["magenta"];
            break;
        case Shape::zBlock:
            img = imageTextures["red"];
            break;
        default:
            img = imageTextures["white"];
            break;

    }
    SDL_RenderCopy(gRenderer, img, nullptr, &texr);
}

void GUI::RenderBoard(std::vector<std::vector<Shape>>& board) {
    for(int j=0;j<NumRowsBoard;j++){
        for(int i=0;i<NumColumnsBoard;i++){
            RenderSquare(j, i, board[j][i]);
        }
    }
}

void GUI::LoadImageTextures() {
    for(const auto& entry : std::filesystem::directory_iterator(TEXTURES_PATH)){
        std::string fileName = entry.path().filename();
        std::string delimiter = ".png";
        std::string color = fileName.substr(0, fileName.find(delimiter));
        SDL_Texture *img;
        img = IMG_LoadTexture(gRenderer, entry.path().c_str());
        imageTextures[color]=img;
    }
}

void GUI::ClearImageTextures() {
    for(auto const&it : imageTextures){
        SDL_DestroyTexture(it.second);
    }
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
    int SCREEN_WIDTH = 768;
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

    LoadImageTextures();
}

void GUI::DeInitializeSDL2() {
    SDL_DestroyTexture(texture);
    delete rect;
    ClearImageTextures();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

