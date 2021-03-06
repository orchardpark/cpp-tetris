/**
* @brief Classes for the observer pattern
*/
#ifndef CPP_TETRIS_OBSERVER_H
#define CPP_TETRIS_OBSERVER_H

#include <string>
#include "model.h"
/*
* 
*/
class IObserver {
public:
	virtual ~IObserver() {};
	virtual void Update(const GameState& state) = 0;
};

class ISubject {
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
};
#endif //CPP_TETRIS_OBSERVER_H
