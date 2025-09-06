#include "../include/SDL2/SDL.h"

#include "Vec.h"

#pragma once

void drawCircle(double x, double y, double r, SDL_Renderer* renderer);

class Particle {
    public:
        Vec pos;
        Vec prevPos;
        Vec v;

        double r;

        double mass;

        Vec kRVals[4] = {Vec(0, 0), Vec(0, 0), Vec(0, 0), Vec(0, 0)};
        double kVVals[4] = {0, 0, 0, 0};

        Particle();
        Particle(double X, double Y, double R, double vX = 0, double vY = 0);

        Particle& operator=(const Particle& other);

        void updatePosGravity(double gravity, double dt);

        void solveConstraint(double constraintX, double constraintY, double desLength, double dt, double alpha = 0);
        void solveConstraint(Particle& p2, double desLength, double dt, double alpha = 0);

        void updateVelocity(double dt);

        void render(SDL_Renderer* renderer);
};