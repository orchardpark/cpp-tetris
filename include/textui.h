#ifndef CPP_TETRIS_TEXTUI_H
#define CPP_TETRIS_TEXTUI_H
#include "observer.h"

class TextUI : IObserver {
public:
	void Run();
	void Update(const GameState& state);
};


#endif // !CPP_TETRIS_TEXTUI_H
