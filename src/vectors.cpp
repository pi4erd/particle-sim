#include "vectors.hpp"

#include <cmath>

vec2::vec2() : x(0), y(0)
{
}

vec2::vec2(double a) : x(a), y(a)
{
}

vec2::vec2(double x, double y) : x(x), y(y)
{
}

vec2 vec2::normalized()
{
    if(length() == 0) return vec2(0, 0);
    return vec2(x, y) / length();
}

double vec2::length()
{
    return std::sqrt(x * x + y * y);
}

vec2 vec2::operator+(vec2 a)
{
    return vec2(x + a.x, y + a.y);
}

vec2 vec2::operator+=(vec2 a)
{
    x += a.x;
    y += a.y;
    return *this;
}

vec2 vec2::operator-(vec2 a)
{
    return vec2(x - a.x, y - a.y);
}

vec2 vec2::operator-=(vec2 a)
{
    x -= a.x;
    y -= a.y;
    return *this;
}

vec2 vec2::operator*(double a)
{
    return vec2(x * a, y * a);
}

vec2 vec2::operator*=(double a)
{
    x *= a;
    y *= a;
    return *this;
}

vec2 vec2::operator/(double a)
{
    return *this * (1 / a);
}

vec2 vec2::operator/=(double a)
{
    x /= a;
    y /= a;
    return *this;
}
