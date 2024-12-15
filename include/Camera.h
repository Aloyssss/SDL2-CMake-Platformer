#pragma once

/* Includes */
#include "Header.h"

/* Camera class definition */
class Camera 
{
private:
    SDL_Rect view; // Rectangle représentant la vue de la caméra
    int worldWidth; // Largeur totale du monde
    int worldHeight; // Hauteur totale du monde

    float lerpFactor; // Facteur de lissage pour les transitions

public:
    // Constructeur
    Camera(int screenWidth, int screenHeight, int worldWidth, int worldHeight)
        : view{ 0, 0, screenWidth, screenHeight },
        worldWidth(worldWidth),
        worldHeight(worldHeight),
        lerpFactor(0.1f) {
    }

    // Définit le facteur de lissage pour les transitions
    void setLerpFactor(float factor) {
        lerpFactor = factor;
    }

    // Déplace la caméra vers une position spécifique (sans suivre une entité)
    void moveTo(int x, int y) {
        view.x = x - view.w / 2;
        view.y = y - view.h / 2;
        clampToBounds();
    }

    // Suit une entité et centre la caméra dessus
    void follow(int targetX, int targetY) {
        int targetViewX = targetX - view.w / 2;
        int targetViewY = targetY - view.h / 2;

        view.x += static_cast<int>((targetViewX - view.x) * lerpFactor);
        view.y += static_cast<int>((targetViewY - view.y) * lerpFactor);

        clampToBounds();
    }

    // Transitionne progressivement vers une position donnée
    void transitionTo(int x, int y) {
        int targetX = x - view.w / 2;
        int targetY = y - view.h / 2;

        view.x += static_cast<int>((targetX - view.x) * lerpFactor);
        view.y += static_cast<int>((targetY - view.y) * lerpFactor);

        clampToBounds();
    }

    // Retourne le rectangle de la caméra (utile pour SDL_RenderSetViewport)
    SDL_Rect getView() const {
        return view;
    }

    // Définit les dimensions du monde (utile si le monde est redimensionné)
    void setWorldBounds(int width, int height) {
        worldWidth = width;
        worldHeight = height;
    }

private:
    // Empêche la caméra de sortir des limites du monde
    void clampToBounds() {
        if (view.x < 0) view.x = 0;
        if (view.y < 0) view.y = 0;
        if (view.x + view.w > worldWidth) view.x = worldWidth - view.w;
        if (view.y + view.h > worldHeight) view.y = worldHeight - view.h;
    }
};