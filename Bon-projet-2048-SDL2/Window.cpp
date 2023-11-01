#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Window.h"
#include "Cell.h"
#include "GameObject.h"

Window::Window(int width, int height, int n) : width(width), height(height), size(n) {
    board = std::vector<std::vector<Cell>>(size, std::vector<Cell>(size, Cell()));
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("2048", 800, 400, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::printBoard() const {
    int CELL_SIZE = 100;
    int spacement = 10;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            GameObject tile(j * (CELL_SIZE + spacement), i * (CELL_SIZE + spacement), CELL_SIZE, CELL_SIZE);
            tile.draw(renderer, board[i][j], tile.x, tile.y, tile.width, tile.height);
        }
    }
}

void Window::addRandomTile() {
    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].isEmpty()) {
                emptyCells.emplace_back(i, j);
            }
        }
    }
    if (!emptyCells.empty()) {
        int index = rand() % emptyCells.size();
        int value = (rand() % 2 + 1) * 2;
        board[emptyCells[index].first][emptyCells[index].second].setValue(value);
    }
}

void Window::leftAction() {
    system("cls");
    for (int i = 0; i < size; i++) {
        for (int j = 1; j < size; j++) {
            if (!board[i][j].isEmpty()) {
                int k = j;
                while (k > 0 && board[i][k - 1].isEmpty()) {
                    k--;
                }
                if (k > 0 && board[i][k - 1].getValue() == board[i][j].getValue()) {
                    board[i][k - 1].setValue(board[i][k - 1].getValue() * 2);
                    board[i][j].setValue(0);
                }
                else if (k != j) {
                    board[i][k].setValue(board[i][j].getValue());
                    board[i][j].setValue(0);
                }
            }
        }
    }
}

void Window::rightAction() {
    system("cls");
    for (int i = 0; i < size; i++) {
        for (int j = size - 2; j >= 0; j--) {
            if (!board[i][j].isEmpty()) {
                int k = j;
                while (k < size - 1 && board[i][k + 1].isEmpty()) {
                    k++;
                }
                if (k < size - 1 && board[i][k + 1].getValue() == board[i][j].getValue()) {
                    board[i][k + 1].setValue(board[i][k + 1].getValue() * 2);
                    board[i][j].setValue(0);
                }
                else if (k != j) {
                    board[i][k].setValue(board[i][j].getValue());
                    board[i][j].setValue(0);
                }
            }
        }
    }
}

void Window::topAction() {
    system("cls");
    for (int j = 0; j < size; j++) {
        for (int i = 1; i < size; i++) {
            if (!board[i][j].isEmpty()) {
                int k = i;
                while (k > 0 && board[k - 1][j].isEmpty()) {
                    k--;
                }
                if (k > 0 && board[k - 1][j].getValue() == board[i][j].getValue()) {
                    board[k - 1][j].setValue(board[k - 1][j].getValue() * 2);
                    board[i][j].setValue(0);
                }
                else if (k != i) {
                    board[k][j].setValue(board[i][j].getValue());
                    board[i][j].setValue(0);
                }
            }
        }
    }
}

void Window::bottomAction() {
    system("cls");
    for (int j = 0; j < size; j++) {
        for (int i = size - 2; i >= 0; i--) {
            if (!board[i][j].isEmpty()) {
                int k = i;
                while (k < size - 1 && board[k + 1][j].isEmpty()) {
                    k++;
                }
                if (k < size - 1 && board[k + 1][j].getValue() == board[i][j].getValue()) {
                    board[k + 1][j].setValue(board[k + 1][j].getValue() * 2);
                    board[i][j].setValue(0);
                }
                else if (k != i) {
                    board[k][j].setValue(board[i][j].getValue());
                    board[i][j].setValue(0);
                }
            }
        }
    }
}

void Window::checkWin() {
    //  si 2048 atteind win
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].getValue() == 2048) {
                std::cout << "WIN !!! 2^11 HAS BEEN REACHED" << std::endl;
                return;
            }
        }
    }
}

void Window::checkLoose() {
    int loose = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].isEmpty()) {
                return; // si case vide, le jeu n'est pas perdu
            }

            if (i < size - 1 && board[i][j].getValue() == board[i + 1][j].getValue()) {
                return; // si tuile fusionnable en bas, le jeu n'est pas perdu
            }

            if (j < size - 1 && board[i][j].getValue() == board[i][j + 1].getValue()) {
                return; //si tuile fusionnable à droite, le jeu n'est pas perdu
            }
        }
    }
    std::cout << "\nYOU LOSE !!!" << std::endl;
}

void Window::display() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::getRenderer() {
    return renderer;
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Couleur noire
    SDL_RenderClear(renderer);
}

bool Window::isOpen() {
    SDL_Event open;
    while (SDL_PollEvent(&open)) {
        if (open.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}
