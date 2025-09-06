#include "../include/SDL2/SDL.h"

#pragma once

class Trailpoint {
    public:
        double R = 255;
        double G = 255;
        double B = 255;

        double x;
        double y;

        Trailpoint(double x, double y);

        void updateColor(double updateVal);

        void render(SDL_Renderer* renderer);
};