#pragma once

struct vec2 {
public:
    vec2();
    vec2(float a);
    vec2(float x, float y);

    float x, y;

    vec2 normalized();
    float length();

    vec2 operator+(vec2 a);
    vec2 operator+=(vec2 a);
    vec2 operator-(vec2 a);
    vec2 operator-=(vec2 a);

    vec2 operator*(float a);
    vec2 operator*=(float a);
    vec2 operator/(float a);
    vec2 operator/=(float a);
};