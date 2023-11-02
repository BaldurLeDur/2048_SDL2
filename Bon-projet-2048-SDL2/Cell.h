#pragma once

#include <iostream>
#include <SDL.h>
#include <map>

class Cell {
private:
	int value;


public:

	static std::map<int, std::string> imageMap;

	Cell() : value(0) {}


	void display() const;

	int getValue() const;

	void setValue(int val);

	bool isEmpty() const;

};