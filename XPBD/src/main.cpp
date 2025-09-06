#include <iostream>
#include "Pendulum.h"
#include "Trailpoint.h"
#include "TextBox.h"
#include <math.h>
#include <deque>
#include "../include/stb_image/stb_image_write.h"
#include "../include/stb_image/stb_image.h"

// Window size
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
#define FRAME_RATE 100

Vec calcUV(Vec a, Vec b, Vec c, Vec d, Vec p) {
    Vec v0 = b-a;
    Vec v1 = d-a;

    Vec vp = p-a;

    double det = 1/(v0.x*v1.y - v0.y*v1.x);

    Vec uv = Vec();

    uv.x = v1.y*vp.x + -1*v1.x*vp.y;
    uv.y = -1*v0.y*vp.x + v0.x*vp.y;

    uv = uv*det;

    return uv;
}

/*int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("XPBD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    double rodLengths = 130;

    Vec attachPoint = Vec(500, 3);
    double gravity = 130;

    int numBodies = 3;

    double frameRate = 200;
    double iterations = 50000;
    double dtSmall = 1/(frameRate*iterations);

    bool quit = false;
    bool pause = false;
    SDL_Event e;

    Textbox t = Textbox("Energy", 18, WINDOW_WIDTH*2/3, WINDOW_HEIGHT-40, WINDOW_WIDTH*1/3, 30);

    int frameCtr = 0;

    system("rm -r images");
    system("mkdir images");

    Pendulum p = Pendulum(numBodies, rodLengths, attachPoint, gravity);

    std::deque<Trailpoint> trailPoints;
    int maxTrailPoints = 1300;

    // Until user presses x button
    while (!quit){
        Uint64 start = SDL_GetPerformanceCounter(); // Count milliseconds since frame
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){ // If user presses x button, quit
                quit = true;
            }
        }

        SDL_RenderClear(renderer);

        for (int i = 0; i < iterations; i++) {
            p.update(dtSmall);
        }

        if (frameCtr % 120 == 0) {
            std::cout << p.energy << "\n";
        }

       t.updateValue(p.energy/1000.);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        trailPoints.push_back(Trailpoint(p.bodies[p.numBodies-1].pos.x, p.bodies[p.numBodies-1].pos.y));

        if (trailPoints.size() > maxTrailPoints) {
            trailPoints.pop_front();
        }
        
       for (int i = 0; i < trailPoints.size(); i++) {
            trailPoints[i].updateColor(0.2);
            trailPoints[i].render(renderer);
        }

        p.render(renderer);

        t.render(renderer, window);

        Uint8* pixels = new (std::nothrow) unsigned char[WINDOW_WIDTH * WINDOW_HEIGHT*4];
        SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ABGR8888, pixels, WINDOW_WIDTH*4);
        std::string name = "images/hello" + std::to_string(frameCtr) + ".png";
        const char* hey = name.c_str();
        stbi_write_png(hey, WINDOW_WIDTH, WINDOW_HEIGHT, 4, pixels, WINDOW_WIDTH*4);
        delete[] pixels;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        SDL_RenderPresent(renderer); 
        SDL_UpdateWindowSurface(window);

        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        SDL_Delay(floor(1000./frameRate - elapsedMS));

        frameCtr++;
    }

    system("cd images");
    system("ffmpeg -r 200 -i images/hello%01d.png -vcodec mpeg4 -y -vb 80M movie.mp4");
    system("rm -r images");

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}*/
 
int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("XPBD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    double rodLengths = 50;

    Vec attachPoint = Vec(320, 5);
    double gravity = 130;

    int numBodies = 2;

    double squareSize = genRandomNumber(40, 190);

    double velocityBounds = 400;

    double xVelocity = genRandomNumber(-velocityBounds, velocityBounds);
    double yVelocity = genRandomNumber(-velocityBounds, velocityBounds);

    double xVelocity2 = genRandomNumber(-velocityBounds, velocityBounds);
    double yVelocity2 = genRandomNumber(-velocityBounds, velocityBounds);

    double xVelocity3 = genRandomNumber(-velocityBounds, velocityBounds);
    double yVelocity3 = genRandomNumber(-velocityBounds, velocityBounds);

    double xVelocity4 = genRandomNumber(-velocityBounds, velocityBounds);
    double yVelocity4 = genRandomNumber(-velocityBounds, velocityBounds);

    double angle = genRandomNumber(0, 90) * ((M_PI)/180);

    //Pendulum p = Pendulum(numBodies, rodLengths, attachPoint, gravity);

    Particle ball1 = Particle(200, 200, sqrt(squareSize)/4.0, xVelocity4, yVelocity4);
    Particle ball2 = Particle(ball1.pos.x+squareSize*cos(angle), ball1.pos.y+squareSize*sin(angle), sqrt(squareSize)/4.0, xVelocity, yVelocity);
    Particle ball3 = Particle(ball2.pos.x-squareSize*sin(angle), ball2.pos.y+squareSize*cos(angle), sqrt(squareSize)/4.0, xVelocity2, yVelocity2);
    Particle ball4 = Particle(ball3.pos.x-squareSize*cos(angle), ball3.pos.y-squareSize*sin(angle), sqrt(squareSize)/4.0, xVelocity3, yVelocity3);

    double frameRate = 60;
    double iterations = 50;
    double dtSmall = 1/(frameRate*iterations);

    bool quit = false;
    bool pause = false;
    SDL_Event e;

    int pausedXcoord = -1;
    int pausedYcoord = -1;

    std::deque<Trailpoint> trailPoints;
    int maxTrailPoints = 3000;

    int frameCtr = 0;
    
    system("rm -r images");
    system("mkdir images");

    // Until user presses x button
    while (!quit){
        Uint64 start = SDL_GetPerformanceCounter(); // Count milliseconds since frame
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){ // If user presses x button, quit
                quit = true;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                Uint8* pixels = new (std::nothrow) unsigned char[WINDOW_WIDTH * WINDOW_HEIGHT*4];
                SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ABGR8888, pixels, WINDOW_WIDTH*4);

                int xCoord = -1;
                int yCoord = -1;
            
                SDL_GetMouseState(&xCoord, &yCoord);

                if (pixels[yCoord*WINDOW_WIDTH*4 + xCoord*4+2] == 255) {
                    if (!pause) {
                        SDL_GetMouseState(&pausedXcoord, &pausedYcoord);
                    }

                    pause = true;
                }
            }

            if (e.type == SDL_MOUSEBUTTONUP) {
                if (pause) {
                    int xCoord = -1;
                    int yCoord = -1;

                    SDL_GetMouseState(&xCoord, &yCoord);

                    xCoord = std::min(xCoord, WINDOW_WIDTH);
                    yCoord = std::min(yCoord, WINDOW_HEIGHT);

                    Vec p = Vec(pausedXcoord, pausedYcoord);

                    Vec velocity = (Vec(xCoord - pausedXcoord, yCoord - pausedYcoord)) * 4;

                    Vec uv = calcUV(ball1.pos, ball2.pos, ball3.pos, ball4.pos, p);

                    //uv = Vec(0.5, 0.5);

                    double wA = (1-uv.x) * (1-uv.y);
                    double wB = uv.x*(1-uv.y);
                    double wC = uv.x*uv.y;
                    double wD = (1-uv.x)*(uv.y);

                    ball1.v = ball1.v + wA*velocity;
                    ball2.v = ball2.v + wB*velocity;
                    ball3.v = ball3.v + wC*velocity;
                    ball4.v = ball4.v + wD*velocity;
                }
                pause = false;
            }
        }

        SDL_RenderClear(renderer);

        if (!pause) {
            for (int i = 0; i < iterations; i++) {
                ball1.updatePosGravity(gravity, dtSmall);
                ball2.updatePosGravity(gravity, dtSmall);
                ball3.updatePosGravity(gravity, dtSmall);
                ball4.updatePosGravity(gravity, dtSmall);

                ball1.solveConstraint(ball2, squareSize, dtSmall, 0.00001);
                ball2.solveConstraint(ball3, squareSize, dtSmall, 0.00001);
                ball3.solveConstraint(ball4, squareSize, dtSmall, 0.00001);
                ball4.solveConstraint(ball1, squareSize, dtSmall, 0.00001);
                ball1.solveConstraint(ball3, squareSize*sqrt(2), dtSmall, 0.00001);
                //ball2.solveConstraint(ball4, squareSize*sqrt(2), dtSmall, 0.00001);

                ball1.updateVelocity(dtSmall);
                ball2.updateVelocity(dtSmall);
                ball3.updateVelocity(dtSmall);
                ball4.updateVelocity(dtSmall);

                //p.update(dtSmall);

                double damping = 1;

                if (ball1.pos.x < 10) {
                    if (ball1.v.x < 0) {
                        ball1.v.x = -damping*ball1.v.x;
                    }
                    
                }
                
                else if (ball1.pos.x > WINDOW_WIDTH - 10) {
                    if (ball1.v.x > 0) {
                        ball1.v.x = -damping*ball1.v.x;
                    }
                }

                if (ball1.pos.y < 10) {
                    if (ball1.v.y < 0) {
                        ball1.v.y = -damping*ball1.v.y;
                    }
                    
                }
                
                else if (ball1.pos.y > WINDOW_HEIGHT - 10) {
                    if (ball1.v.y > 0) {
                        ball1.v.y = -damping*ball1.v.y;
                    }
                }

                if (ball2.pos.x < 10) {
                    if (ball2.v.x < 0) {
                        ball2.v.x = -damping*ball2.v.x;
                    }
                    
                }
                
                else if (ball2.pos.x > WINDOW_WIDTH - 10) {
                    if (ball2.v.x > 0) {
                        ball2.v.x = -damping*ball2.v.x;
                    }
                }

                if (ball2.pos.y < 10) {
                    if (ball2.v.y < 0) {
                        ball2.v.y = -damping*ball2.v.y;
                    }
                    
                }
                
                else if (ball2.pos.y > WINDOW_HEIGHT - 10) {
                    if (ball2.v.y > 0) {
                        ball2.v.y = -damping*ball2.v.y;
                    }
                }

                if (ball3.pos.x < 10) {
                    if (ball3.v.x < 0) {
                        ball3.v.x = -damping*ball3.v.x;
                    }
                    
                }
                
                else if (ball3.pos.x > WINDOW_WIDTH - 10) {
                    if (ball3.v.x > 0) {
                        ball3.v.x = -damping*ball3.v.x;
                    }
                }

                if (ball3.pos.y < 10) {
                    if (ball3.v.y < 0) {
                        ball3.v.y = -damping*ball3.v.y;
                    }
                    
                }
                
                else if (ball3.pos.y > WINDOW_HEIGHT - 10) {
                    if (ball3.v.y > 0) {
                        ball3.v.y = -damping*ball3.v.y;
                    }
                }

                if (ball4.pos.x < 10) {
                    if (ball4.v.x < 0) {
                        ball4.v.x = -damping*ball4.v.x;
                    }
                    
                }
                
                else if (ball4.pos.x > WINDOW_WIDTH - 10) {
                    if (ball4.v.x > 0) {
                        ball4.v.x = -damping*ball4.v.x;
                    }
                }

                if (ball4.pos.y < 10) {
                    if (ball4.v.y < 0) {
                        ball4.v.y = -damping*ball4.v.y;
                    }
                    
                }
                
                else if (ball4.pos.y > WINDOW_HEIGHT - 10) {
                    if (ball4.v.y > 0) {
                        ball4.v.y = -damping*ball4.v.y;
                    }
                }
            }
        }
        

        /*trailPoints.push_back(Trailpoint(p.bodies[p.numBodies-1].pos.x, p.bodies[p.numBodies-1].pos.y));

        if (trailPoints.size() > maxTrailPoints) {
            trailPoints.pop_front();
        }
        
       for (int i = 0; i < trailPoints.size(); i++) {
            trailPoints[i].updateColor(0.1);
            trailPoints[i].render(renderer);
        }*/

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderDrawLineF(renderer, ball1.pos.x, ball1.pos.y, ball2.pos.x, ball2.pos.y);
        SDL_RenderDrawLineF(renderer, ball2.pos.x, ball2.pos.y, ball3.pos.x, ball3.pos.y);
        SDL_RenderDrawLineF(renderer, ball3.pos.x, ball3.pos.y, ball4.pos.x, ball4.pos.y);
        SDL_RenderDrawLineF(renderer, ball4.pos.x, ball4.pos.y, ball1.pos.x, ball1.pos.y);

        Uint8* pixels = new (std::nothrow) unsigned char[WINDOW_WIDTH * WINDOW_HEIGHT*4];
        SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ABGR8888, pixels, WINDOW_WIDTH*4);

        int cnt = 0;
        std::vector<SDL_Rect> drawnRects;

        for (int i = 0; i < WINDOW_HEIGHT; i++) {
            cnt = 0;

            for (int j = 0; j < (WINDOW_WIDTH-1) * 4; j += 4) {
                if (pixels[i*WINDOW_WIDTH*4 + j+2] == 255 && pixels[i*WINDOW_WIDTH*4 + (j+4)+2] != 255) {
                    cnt += 1;
                }

                else {
                    if (cnt % 2 == 1) {
                        SDL_Rect rect;
                        rect.x = j/4;
                        rect.y = i;
                        rect.w = 1;
                        rect.h = 1;

                        drawnRects.push_back(rect);
                    }
                }
            }

            if (cnt != 1) {
                for (int k = 0; k < drawnRects.size(); k++) {
                    SDL_RenderDrawRect(renderer, &drawnRects[k]);
                }
            }

            drawnRects.clear();
        }

        SDL_SetRenderDrawColor(renderer, 254, 0, 0, 255);

        int xCoord = -1;
        int yCoord = -1;
    
        SDL_GetMouseState(&xCoord, &yCoord);

        if (pause) {
            SDL_RenderDrawLine(renderer, xCoord, yCoord, pausedXcoord, pausedYcoord);
            drawCircle(pausedXcoord, pausedYcoord, 4, renderer);
        }
        

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        SDL_RenderPresent(renderer); 
        SDL_UpdateWindowSurface(window);

        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        SDL_Delay(floor(1000./frameRate - elapsedMS));

        frameCtr++;
    }

    system("cd images");
    system("ffmpeg -r 60 -i images/hello%01d.png -vcodec mpeg4 -y -vb 80M movie.mp4");
    system("rm -r images");

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}