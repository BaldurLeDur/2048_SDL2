
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include "Cell.h" 
// Assurez-vous d'inclure les fichiers nécessaires.

class GameObject {
public:
    int x, y, width, height;
    int R, G, B;
    GameObject(int x, int y, int width, int height);
    void drawImage(SDL_Renderer* renderer, const Cell& cell, int x, int y, int width, int height);
    void draw(SDL_Renderer* renderer, const Cell& cell, int x, int y, int width, int height);
};

#endif // GAMEOBJECT_H
