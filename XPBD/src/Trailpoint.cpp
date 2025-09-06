#include "Trailpoint.h"

Trailpoint::Trailpoint(double X, double Y) {
    x = X;
    y = Y;

    R = 255;
    G = 255;
    B = 255;
}

void Trailpoint::updateColor(double updateVal) {
    R -= updateVal;
    G -= updateVal;
    B -= updateVal;
}

void Trailpoint::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, R, G, B, 255);
    SDL_RenderDrawPointF(renderer, x, y);
}