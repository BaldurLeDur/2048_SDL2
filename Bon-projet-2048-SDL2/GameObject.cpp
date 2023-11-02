#include "GameObject.h"
#include "Cell.h"

GameObject::GameObject(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}


void GameObject::drawImage(SDL_Renderer* renderer, const Cell& cell, int x, int y, int width, int height) {
    SDL_Rect rect = { x, y, width, height };
    SDL_Surface* imageSurface = SDL_LoadBMP(cell.imageMap[cell.getValue()].c_str());

    if (!imageSurface) {

        printf("Erreur lors du chargement de l'image : %s", SDL_GetError());
    }
    else {
        SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);

        if (!imageTexture) {
            printf("Erreur lors de la création de la texture : %s", SDL_GetError());
        }
        else {
            SDL_RenderCopy(renderer, imageTexture, NULL, &rect);

            SDL_FreeSurface(imageSurface);

            SDL_DestroyTexture(imageTexture);
        }
    }
}
