#include <iostream>
#include <SDL.h>
#include <Windows.h>
#include "Window.h"
#include "GameObject.h"

int main(int argc, char* args[]) {
    const int SCREEN_WIDTH = 430;
    const int SCREEN_HEIGHT = 430;

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, 4);

    window.addRandomTile();
    window.addRandomTile();

    SDL_Event e; // Vous avez besoin de cet événement pour gérer les événements SDL

    while (window.isOpen()) {
        window.clear();
        window.printBoard();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    window.leftAction();
                    break;
                case SDLK_RIGHT:
                    window.rightAction();
                    break;
                case SDLK_UP:
                    window.topAction();
                    break;
                case SDLK_DOWN:
                    window.bottomAction();
                    break;
                default:
                    break;
                }

                window.checkWin();
                window.checkLoose();
                window.addRandomTile();
            }
            else if (window.checkLoose() == 1) {
                while (true) {
                    window.imageLoose(window.getRenderer(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    window.display();
                }
                
            }
            else if (window.checkWin() == 1) {
                while (true) {
                    window.imageWin(window.getRenderer(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    window.display();
                }
            }
        }
        window.display();
    }
    return 0;
}
