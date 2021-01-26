#ifndef CPP_TETRIS_TEXTUI_H
#define CPP_TETRIS_TEXTUI_H
#include "observer.h"
#include <thread>
#include "game.h"
#include <iostream>
#include <memory>
#ifdef __GNUC__
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#else
#include "SDL.h"
#include "SDL_tff.h"
#endif

class TextUI : IObserver {
public:
	void Run();
	void Update(const GameState& state);
private:
    std::string StateToString(const GameState& state);
};

#endif // !CPP_TETRIS_TEXTUI_H
