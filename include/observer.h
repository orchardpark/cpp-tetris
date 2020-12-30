/**
* @brief Classes for the observer pattern
*/
#ifndef CPP_TETRIS_OBSERVER_H
#define CPP_TETRIS_OBSERVER_H

#include <memory>
#include <string>
/*
* 
*/
class IObserver {
public:
	virtual ~IObserver() {};
	virtual void update(const std::string& message) = 0;
};

class ISubject {
public:
	virtual ~ISubject() {};
	virtual void attach(std::shared_ptr<IObserver> observer) = 0;
	virtual void detach(std::shared_ptr<IObserver> observer) = 0;
};
#endif CPP_TETRIS_OBSERVER_H
