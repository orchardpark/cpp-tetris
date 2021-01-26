#ifndef CPP_TETRIS_TEXTUI_H
#define CPP_TETRIS_TEXTUI_H
#include "observer.h"
#include <thread>
#include "game.h"
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class TextUI : IObserver {
public:
	void Run();
	void Update(const GameState& state);
private:
    std::string StateToString(const GameState& state);
};

#endif // !CPP_TETRIS_TEXTUI_H
