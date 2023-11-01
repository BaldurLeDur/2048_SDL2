#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <SDL.h>
#include <map>
#include "Cell.h"

const int CELL_SIZE = 100; // taille en pixel d'un game object

class GameObject {
public:
    int x, y, width, height;
    int R = 156;
    int G = 156;
    int B = 156;
    GameObject(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    void drawImage(SDL_Renderer* renderer, const Cell& cell, int x, int y, int width, int height) {
        SDL_Rect rect = { x, y, width, height };
        SDL_Surface* imageSurface = SDL_LoadBMP(cell.imageMap[cell.getValue()].c_str()); // Charger l'image BMP correspondante à la valeur de la cellule

        if (!imageSurface) {
            // Gérer les erreurs si l'image n'a pas été chargée correctement
            printf("Erreur lors du chargement de l'image : %s", SDL_GetError());
        }
        else {
            SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface); // Convertir la surface en texture

            if (!imageTexture) {
                // Gérer les erreurs si la texture n'a pas été créée correctement
                printf("Erreur lors de la création de la texture : %s", SDL_GetError());
            }
            else {
                // Afficher la texture à l'écran
                SDL_RenderCopy(renderer, imageTexture, NULL, &rect);

                // Libérer la surface car la texture est créée
                SDL_FreeSurface(imageSurface);

                // Détruire la texture lorsqu'elle n'est plus nécessaire
                SDL_DestroyTexture(imageTexture);
            }
        }
    }


    void draw(SDL_Renderer* renderer, const Cell& cell, int x, int y, int width, int height) {
        SDL_Rect rect = { x, y, width, height };
        SDL_Color color;
        auto it = cell.colorMap.find(cell.getValue());
        if (it != cell.colorMap.end()) {
            color = it->second;
        }
        else {
            color = cell.colorMap.at(0); // Couleur par défaut si la valeur n'est pas trouvée
        }
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
};

/*class Grid {
private:
    GameObject tiles[4][4];
public:
    Grid() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tiles[i][j] = GameObject(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, 0); // VOIR GAME OBJECT PEUT ETRE A CHANGER
            }
        }

        void draw(SDL_Renderer * renderer) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    tiles[i][j].draw(renderer);
                }
            }
        }
    }
};*/

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<std::vector<Cell>> board;
    int size;
    int width;
    int height;

public:

    Window(int width, int height, int n) : width(width), height(height), size(n) {
        board = std::vector<std::vector<Cell>>(size, std::vector<Cell>(size, Cell())); // Ajouter cette ligne pour initialiser les cellules
        srand(time(0));
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("2048", 800, 400, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    ~Window() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void printBoard() const {
        int spacement = 10;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                GameObject tile(j * (CELL_SIZE + spacement), i * (CELL_SIZE + spacement), CELL_SIZE, CELL_SIZE);
                tile.draw(renderer, board[i][j], tile.x, tile.y, tile.width, tile.height);
                //tile.drawImage(renderer, board[i][j], tile.x, tile.y, tile.width, tile.height);
            }
        }
    }

    void addRandomTile() {
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

    void leftAction() {
        system("cls");
        for (int i = 0; i < size; i++) {
            for (int j = 1; j < size; j++) {
                if (!board[i][j].isEmpty()) {
                    //  k permet de ne pas faire 2 fusions consécutive
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

    void rightAction() {
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

    void topAction() {
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

    void bottomAction() {
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

    void checkWin() {
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
    void checkLoose() {
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

    void display() {
        SDL_RenderPresent(renderer);
    }

    SDL_Renderer* getRenderer() {
        return renderer;
    }

    void clear() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Couleur noire
        SDL_RenderClear(renderer);
    }

    bool isOpen() {
        SDL_Event open;
        while (SDL_PollEvent(&open)) {
            if (open.type == SDL_QUIT) {
                return false;
            }
        }
        return true;
    }
};



int main(int argc, char* args[]) {
    const int SCREEN_WIDTH = 430;
    const int SCREEN_HEIGHT = 430;

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, 4);

    GameObject obj(100, 100, CELL_SIZE, CELL_SIZE);
    window.addRandomTile();
    window.addRandomTile();

    while (window.isOpen()) {
        window.clear();
        window.printBoard();
        if (GetKeyState(VK_LEFT) & 0x8000) {
            window.leftAction();
            window.checkWin();
            window.checkLoose();
            window.addRandomTile();
            Sleep(200);
        }
        else if (GetKeyState(VK_RIGHT) & 0x8000) {
            window.rightAction();
            window.checkWin();
            window.checkLoose();
            window.addRandomTile();
            Sleep(200);
        }
        else if (GetKeyState(VK_UP) & 0x8000) {
            window.topAction();
            window.checkWin();
            window.checkLoose();
            window.addRandomTile();
            Sleep(200);
        }
        else if (GetKeyState(VK_DOWN) & 0x8000) {
            window.bottomAction();
            window.checkWin();
            window.checkLoose();
            window.addRandomTile();
            Sleep(200);
        }
        window.display();
    }

    return 0;
}