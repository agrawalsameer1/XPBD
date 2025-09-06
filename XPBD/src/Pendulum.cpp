#include "Pendulum.h"

double genRandomNumber(double min, double max) {
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

Pendulum::Pendulum(int n, double rodLength, Vec hingePoint, double gravityStrength) {
    numBodies = n;

    rodLengths = new double[numBodies];

    bodies = new Particle[numBodies];

    attachPoint = hingePoint;

    gravity = gravityStrength;

    double mass = 4;

    for (int i = 0; i < numBodies; i++) {
        rodLengths[i] = rodLength;
    }

    double curAngle = genRandomNumber(40, 50) * ((M_PI)/180);
    bodies[0] = Particle(attachPoint.x + rodLengths[0]*cos(curAngle), attachPoint.y + rodLengths[0]*sin(curAngle), mass);//*numBodies, 0, 0);

    for (int i = 1; i < numBodies; i++) {
        curAngle = genRandomNumber(0, 180) * ((M_PI)/180);
        bodies[i] = Particle(bodies[i-1].pos.x + rodLengths[i]*cos(curAngle), bodies[i-1].pos.y + rodLengths[i]*sin(curAngle), mass);//*(numBodies - i), 0, 0);
    }

    energy = 0;
    double totalLength = 0;

    for (int i = 0; i < numBodies; i++) {
        totalLength += rodLengths[i];

        energy += (0.5*bodies[i].mass * bodies[i].v.dist(Vec(0, 0))*bodies[i].v.dist(Vec(0, 0)));
        energy += bodies[i].mass * (gravity) * ((attachPoint.y + totalLength) - bodies[i].pos.y);
    }
}

Pendulum::Pendulum(int n, Particle* particles, double* lengths, Vec hingePoint, double gravityStrength) {
    numBodies = n;

    bodies = new Particle[numBodies];

    rodLengths = new double[numBodies];

    gravity = gravityStrength;

    attachPoint = hingePoint;

    double totalLength = 0;

    for (int i = 0; i < numBodies; i++) {
        bodies[i] = particles[i];

        rodLengths[i] = lengths[i];

        totalLength += rodLengths[i];

        energy += (0.5*bodies[i].mass * bodies[i].v.dist(Vec(0, 0))*bodies[i].v.dist(Vec(0, 0)));
        energy += bodies[i].mass * (gravity) * ((attachPoint.y + totalLength) - bodies[i].pos.y);
    }
}

Pendulum::~Pendulum() {
    delete[] bodies;
    delete[] rodLengths;
}

void Pendulum::update(double dt) {
    double alpha = 0;
    for (int i = 0; i < numBodies; i++) {
        bodies[i].updatePosGravity(gravity, dt);
    }

    bodies[0].solveConstraint(attachPoint.x, attachPoint.y, rodLengths[0], dt, alpha);
    for (int i = 1; i < numBodies; i++) {
        bodies[i].solveConstraint(bodies[i-1], rodLengths[i], dt, alpha);
    }

    for (int i = 0; i < numBodies; i++) {
        bodies[i].updateVelocity(dt);
    }

    energy = 0;
    double totalLength = 0;

    for (int i = 0; i < numBodies; i++) {
        totalLength += rodLengths[i];

        energy += (0.5*bodies[i].mass * bodies[i].v.dist(Vec(0, 0))*bodies[i].v.dist(Vec(0, 0)));
        energy += bodies[i].mass * (gravity) * ((attachPoint.y + totalLength) - bodies[i].pos.y);
    }
}

void Pendulum::updateRungeKutta(double dt) {
    Vec startingPositions[numBodies];

    for (int i = 0; i < numBodies; i++) {
        startingPositions[i] = bodies[i].pos;
    }

    update(dt);

    for (int i = 0; i < numBodies; i++) {
        bodies[i].kRVals[0] = bodies[i].v;
    }

    for (int i = 0; i < numBodies; i++) {
        bodies[i].pos = startingPositions[i] + bodies[i].kRVals[0]*dt/2;
    }

    update(dt);

    for (int i = 0; i < numBodies; i++) {
        bodies[i].kRVals[1] = bodies[i].v;
    }

    for (int i = 0; i < numBodies; i++) {
        bodies[i].pos = startingPositions[i] + bodies[i].kRVals[1]*dt/2;
    }

    update(dt);

    for (int i = 0; i < numBodies; i++) {
        bodies[i].kRVals[2] = bodies[i].v;
    }

    for (int i = 0; i < numBodies; i++) {
        bodies[i].pos = startingPositions[i] + bodies[i].kRVals[2]*dt;
    }

    update(dt);

    for (int i = 0; i < numBodies; i++) {
        bodies[i].kRVals[3] = bodies[i].v;
    }

    for (int i = 0; i < numBodies; i++) {
        bodies[i].v = (bodies[i].kRVals[0] + 2*bodies[i].kRVals[1] + 2*bodies[i].kRVals[2] + bodies[i].kRVals[3])/6;
        bodies[i].prevPos = startingPositions[i];
        bodies[i].pos = bodies[i].v*dt;
    }

    energy = 0;
    double totalLength = 0;

    for (int i = 0; i < numBodies; i++) {
        totalLength += rodLengths[i];

        energy += (0.5*bodies[i].mass * bodies[i].v.dist(Vec(0, 0))*bodies[i].v.dist(Vec(0, 0)));
        energy += bodies[i].mass * (gravity) * ((attachPoint.y + totalLength) - bodies[i].pos.y);
    }
}

void Pendulum::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    bodies[0].render(renderer);
    SDL_RenderDrawLineF(renderer, bodies[0].pos.x, bodies[0].pos.y, attachPoint.x, attachPoint.y);

    for (int i = 1; i < numBodies; i++) {
        bodies[i].render(renderer);
        SDL_RenderDrawLineF(renderer, bodies[i].pos.x, bodies[i].pos.y, bodies[i-1].pos.x, bodies[i-1].pos.y);
    }
}

