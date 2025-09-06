#include "Vec.h"

Vec::Vec() {
    x = 0;
    y = 0;
}

Vec::Vec(double X, double Y) {
    x = X;
    y = Y;
}

double Vec::dist(Vec vec2) {
    return dist(vec2.x, vec2.y);
}

double Vec::dist(double X, double Y) {
    return sqrt((X - x)*(X - x) + (Y - y)*(Y - y));
}

Vec& Vec::operator=(const Vec& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    
    return *this;
}

Vec operator*(Vec vec1, double num) {
    Vec vec2 = Vec(vec1.x*num, vec1.y*num);
    return vec2;
}

Vec operator*(double num, Vec vec1) {
    Vec vec2 = Vec(vec1.x*num, vec1.y*num);
    return vec2;
}

Vec operator/(Vec vec1, double num) {
    Vec vec2 = Vec(vec1.x/num, vec1.y/num);
    return vec2;
}

Vec operator+(Vec vec1, Vec vec2) {
    Vec vec3 = Vec(vec1.x + vec2.x, vec1.y + vec2.y);
    return vec3;
}

Vec operator-(Vec vec1, Vec vec2) {
    Vec vec3 = vec2*-1;
    vec3 = vec3+vec1;
    return vec3;
}

