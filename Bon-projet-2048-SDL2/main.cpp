#include <iostream>
#include <SDL.h>
#include "Window.h"
#include "GameObject.h"

int main(int argc, char* args[]) {
    const int SCREEN_WIDTH = 430;
    const int SCREEN_HEIGHT = 430;

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, 4);

    window.addRandomTile();
    window.addRandomTile();

    SDL_Event e; // Vous avez besoin de cet �v�nement pour g�rer les �v�nements SDL

    while (window.isOpen()) {
        window.clear();
        window.printBoard();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    window.leftAction();
                    window.checkWin();
                    window.checkLoose();
                    window.addRandomTile();
                    break;
                case SDLK_RIGHT:
                    window.rightAction();
                    window.checkWin();
                    window.checkLoose();
                    window.addRandomTile();
                    break;
                case SDLK_UP:
                    window.topAction();
                    window.checkWin();
                    window.checkLoose();
                    window.addRandomTile();
                    break;
                case SDLK_DOWN:
                    window.bottomAction();
                    window.checkWin();
                    window.checkLoose();
                    window.addRandomTile();
                    break;
                default:
                    break;
                }
            }
            else if (e.type == SDL_QUIT) {
                window.display();
                return 0;
            }
        }

        window.display();
    }

    return 0;
}
