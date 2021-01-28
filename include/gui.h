#ifndef CPP_TETRIS_GUI_H
#define CPP_TETRIS_GUI_H
#include "observer.h"
#include <thread>
#include "game.h"
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class GUI : IObserver {
public:
	void Run();
	void Update(const GameState& state);
private:
    static void StartGame(std::shared_ptr<Game> game);
    static void RunKeyboardController(std::shared_ptr<Game> game);
    std::string StateToString(const GameState& state);
    void RenderState(const GameState& state);
    void RenderText(int x, int y, const char* text, float scaleFactor);
    void InitializeSDL2();
    void DeInitializeSDL2();

    SDL_Window* gWindow = nullptr;
    SDL_Renderer* gRenderer = nullptr;
    TTF_Font* font = nullptr;
    SDL_Rect* rect = nullptr;
    SDL_Texture *texture;
};

#endif // !CPP_TETRIS_GUI_H
