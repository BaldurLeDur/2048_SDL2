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
            tile.drawImage(renderer, board[i][j], tile.x, tile.y, tile.width, tile.height);
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

int Window::checkWin() {
    //  si 2048 atteind win
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].getValue() == 16) {
                std::cout << "WIN !!! 2^11 HAS BEEN REACHED" << std::endl;
                return 1;
            }
        }
    }
}

int Window::checkLoose() {
    int emptyCells = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].isEmpty()) {
                emptyCells++;
            }

            if (i < size - 1 && board[i][j].getValue() == board[i + 1][j].getValue()) {
                return 0;  // Si deux cellules adjacentes ont la même valeur, le jeu continue
            }

            if (j < size - 1 && board[i][j].getValue() == board[i][j + 1].getValue()) {
                return 0;  // Si deux cellules adjacentes ont la même valeur, le jeu continue
            }
        }
    }

    if (emptyCells == 0) {
        std::cout << "\nYOU LOSE !!!" << std::endl;
        return 1;
    }

    return 0;  // Le jeu continue
}



void Window::imageLoose(SDL_Renderer* renderer, int x, int y, int width, int height) {
    SDL_Rect rect = { x, y, width, height };
    SDL_Surface* imageLoose = SDL_LoadBMP("../img/LooseScreen.bmp");

    if (!imageLoose) {

        printf("Erreur lors du chargement de l'image : %s", SDL_GetError());
    }
    else {
        SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageLoose);

        if (!imageTexture) {
            printf("Erreur lors de la création de la texture : %s", SDL_GetError());
        }
        else {
            SDL_RenderCopy(renderer, imageTexture, NULL, &rect);

            SDL_FreeSurface(imageLoose);

            SDL_DestroyTexture(imageTexture);
        }
    }
}

void Window::imageWin(SDL_Renderer* renderer, int x, int y, int width, int height) {
    SDL_Rect rect = { x, y, width, height };
    SDL_Surface* imageLoose = SDL_LoadBMP("../img/WinScreen.bmp");

    if (!imageLoose) {

        printf("Erreur lors du chargement de l'image : %s", SDL_GetError());
    }
    else {
        SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageLoose);

        if (!imageTexture) {
            printf("Erreur lors de la création de la texture : %s", SDL_GetError());
        }
        else {
            SDL_RenderCopy(renderer, imageTexture, NULL, &rect);

            SDL_FreeSurface(imageLoose);

            SDL_DestroyTexture(imageTexture);
        }
    }
}

void Window::display() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::getRenderer() {
    return renderer;
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 255, 182, 183, 255); // Couleur noire
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
