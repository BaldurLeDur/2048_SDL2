#include<iostream>
#include "GameObject.h"
#include "Cell.h"

GameObject::GameObject(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

void GameObject::drawImage(SDL_Renderer* renderer, const Cell& cell, int x, int y, int width, int height) {
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

void GameObject::draw(SDL_Renderer* renderer, const Cell& cell, int x, int y, int width, int height) {
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
