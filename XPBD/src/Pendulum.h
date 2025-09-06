#include "Particle.h"
#include <random>

#pragma once

class Pendulum {
    public:
        int numBodies;
        Particle* bodies;
        double* rodLengths;

        Vec attachPoint;

        double gravity;

        double energy = 0;

        Pendulum(int n, double rodLength, Vec hingePoint, double gravityStrength);
        Pendulum(int n, Particle* particles, double* lengths, Vec hingePoint, double gravityStrength);

        ~Pendulum();

        void update(double dt);

        void updateRungeKutta(double dt);

        void render(SDL_Renderer* renderer);
};

double genRandomNumber(double min, double max);