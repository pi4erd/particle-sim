#pragma once

struct vec2 {
public:
    vec2();
    vec2(double a);
    vec2(double x, double y);

    double x, y;

    vec2 normalized();
    double length();

    vec2 operator+(vec2 a);
    vec2 operator+=(vec2 a);
    vec2 operator-(vec2 a);
    vec2 operator-=(vec2 a);

    vec2 operator*(double a);
    vec2 operator*=(double a);
    vec2 operator/(double a);
    vec2 operator/=(double a);
};