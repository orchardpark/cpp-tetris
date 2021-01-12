#ifndef CPP_TETRIS_TEXTUI_H
#define CPP_TETRIS_TEXTUI_H
#include "observer.h"
#include <thread>
#include "gamelogic.h"
#include <iostream>
#include <memory>

class TextUI : IObserver {
public:
	void Run();
	void Update(const GameState& state);
private:
    std::string StateToString(const GameState& state);
};

#endif // !CPP_TETRIS_TEXTUI_H
