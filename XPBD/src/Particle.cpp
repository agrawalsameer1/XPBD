#include "Particle.h"

void drawCircle(double x, double y, double r, SDL_Renderer* renderer) {
    for (float w = 0; w < r * 2; w++) {
        for (float h = 0; h < r * 2; h++) {
            float dx = r - w; // horizontal offset
            float dy = r - h; // vertical offset
            if ((dx*dx + dy*dy) <= (r * r)) {
                SDL_RenderDrawPointF(renderer, x + dx, y + dy);
            }
        }
    }
}

Particle::Particle() {
    pos = Vec();

    prevPos = Vec();
    prevPos = pos;

    v = Vec();

    r = 8;

    mass = r*r;
}

Particle::Particle(double X, double Y, double R, double vX, double vY) {
    pos = Vec(X, Y);
    prevPos = Vec(X, Y);
    v = Vec(vX, vY);

    r = R;

    mass = r;//*r;
}

Particle& Particle::operator=(const Particle& other) {
    if (this != &other) {
        pos = other.pos;
        prevPos = other.prevPos;
        v = other.v;

        r = other.r;

        mass = other.mass;
    }

    return *this;
}

void Particle::updatePosGravity(double gravity, double dt) {
    v = Vec(0, gravity*dt) + v;

    prevPos = pos;
    pos = (v*dt) + pos;
}

void Particle::solveConstraint(double constraintX, double constraintY, double desLength, double dt, double alpha) {
    Vec constraintVec = Vec(constraintX, constraintY);
    
    double dist = pos.dist(constraintVec);
    double distDif = dist-desLength;

    Vec delta = Vec(0, 0);

    double w = 1/mass;
    double lambda = (distDif)/(w + (alpha/(dt*dt)));

    if (constraintVec.x != pos.x || constraintVec.y != pos.y) {
        delta = lambda*w*((constraintVec-pos)/dist);
    }
    
    pos = pos + delta;
}

void Particle::solveConstraint(Particle& p2, double desLength, double dt, double alpha) {
    Vec constraintVec = p2.pos;
    
    double dist = pos.dist(constraintVec);
    double distDif = dist-desLength;

    Vec delta1 = Vec(0, 0);
    Vec delta2 = Vec(0, 0);

    double w = 1/mass;
    double w2 = 1/p2.mass;

    double lambda = (distDif)/(w + w2 + (alpha/(dt*dt)));

    if (constraintVec.x != pos.x || constraintVec.y != pos.y) {
        delta1 = lambda*w*((constraintVec-pos)/dist);
        delta2 = -1*lambda*w2*((constraintVec-pos)/dist);
    }
    
    pos = pos + delta1;
    p2.pos = p2.pos + delta2;
}

void Particle::updateVelocity(double dt) {
    double damping = 0;
    v = ((pos-prevPos)/(dt)) * (1-damping);
}

void Particle::render(SDL_Renderer* renderer) {
    drawCircle(pos.x, pos.y, r, renderer);
}



