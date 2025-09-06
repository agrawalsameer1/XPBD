#include <iostream>
#include <cstdlib>
#include <math.h>

#pragma once

class Vec {
    public:
        double x;
        double y;

        Vec();
        Vec(double X, double Y);

        Vec& operator=(const Vec& other);

        double dist(Vec vec2);
        double dist(double x, double y);
};

Vec operator*(Vec vec1, double num);
Vec operator*(double num, Vec vec1);
Vec operator/(Vec vec1, double num);
Vec operator+(Vec vec1, Vec vec2);
Vec operator-(Vec vec1, Vec vec2);