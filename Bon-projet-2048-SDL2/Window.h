#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <vector>
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
    void checkWin();
    void checkLoose();
    void display();
    SDL_Renderer* getRenderer();
    void clear();
    bool isOpen();
};

#endif // WINDOW_H
