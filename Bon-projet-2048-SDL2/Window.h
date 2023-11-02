#pragma once

#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "Cell.h"

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<std::vector<Cell>> board;
    int size;
    int width;
    int height;
    

public:
    Window(int width, int height, int n);
    ~Window();
    void printBoard() const;
    void addRandomTile();
    void leftAction();
    void rightAction();
    void topAction();
    void bottomAction();
    int checkWin();
    int checkLoose();
    void imageLoose(SDL_Renderer* renderer, int x, int y, int width, int height);
    void imageWin(SDL_Renderer* renderer, int x, int y, int width, int height);
    void display();
    SDL_Renderer* getRenderer();
    void clear();
    bool isOpen();
};
