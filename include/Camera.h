#pragma once

/* Includes */
#include "Header.h"

/* Camera class definition */
class Camera 
{
private:
    SDL_Rect _view; // Rectangle représentant la vue de la caméra
    int _worldWidth, _worldHeight; // Taille du monde
    int _screenWidth,_screenHeight;  // Taile de la fenetre

    float lerpFactor; // Facteur de lissage pour les transitions

public:
    // Constructeur
    Camera(int screenWidth, int screenHeight, int worldWidth, int worldHeight);    

    // Déplace la caméra vers une position spécifique (sans suivre une entité)
    void moveTo(int x, int y);

    // lerp vers une position et centre la caméra dessus
    void follow(int targetX, int targetY);

    // Convertit les coordonnées du monde en coordonnées de l'ecran
    Vector2f worldToScreen(Vector2f worldPosition)
    {
        return Vector2f(worldPosition.x - _view.x, worldPosition.y - _view.y);
    }

    /* Setters / Getters */
    void setLerpFactor(float factor);
    SDL_Rect getView() const;
    void setWorldBounds(int width, int height);

    

private:
    // Empêche la caméra de sortir des limites du monde
    void clampToBounds() {
        if (_view.x < 0) _view.x = 0;
        if (_view.y < 0) _view.y = 0;
        if (_view.x + _view.w > _worldWidth) _view.x = _worldWidth - _view.w;
        if (_view.y + _view.h > _worldHeight) _view.y = _worldHeight - _view.h;
    }
};