#pragma once

#include "vectors.hpp"

struct Particle {
public:
    vec2 position;
    vec2 velocity;

    void attract(Particle& other);
    void repel(Particle& other);
    void update(float deltaTime);
private:
    bool detectEdge();
};
