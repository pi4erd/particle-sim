#include "particle.hpp"
#include "setup.h"

#include <SDL2/SDL.h>

#define ATTRACTION_MULTIPLIER 10

void Particle::attract(Particle& other)
{
    vec2 h = (other.position - position);
    float l = h.length();
    if(l < 0.001) l = 0.1;
    velocity += h.normalized() / (l * l) * ATTRACTION_MULTIPLIER;
}

void Particle::repel(Particle &other)
{
    vec2 h = (other.position - position);
    float l = h.length();
    if(l < 0.001) l = 0.1;
    velocity -= h.normalized() / (l * l * l) * 25 * ATTRACTION_MULTIPLIER;
}

void Particle::update(float deltaTime)
{
    //velocity += vec2(0, 1) * deltaTime;
    position += velocity * deltaTime;

    // Add slow down over time
    velocity -= velocity * deltaTime * 0.1f;

    if(position.x > WINDOW_WIDTH) {
        position.x = WINDOW_WIDTH;
        velocity.x *= -0.9;
    }
    else if(position.x < 0) {
        position.x = 0;
        velocity.x *= -0.9;
    }
    if(position.y > WINDOW_HEIGHT) {
        position.y = WINDOW_HEIGHT;
        velocity.y *= -0.9;
    } 
    else if(position.y < 0) {
        position.y = 0;
        velocity.y *= -0.9;
    }
}

bool Particle::detectEdge()
{
    return position.x > WINDOW_WIDTH || position.x < 0 || position.y > WINDOW_HEIGHT || position.y < 0;
}
