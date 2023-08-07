// CUSTOM INCLUDES
#include "particle.hpp"
#include "setup.h"

// STANDARD INCLUDES
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <fmt/core.h>

// SDL2
#include <SDL2/SDL.h>
#include <SDL_ttf.h>


// GLOBALS
bool close = false;
std::vector<Particle> particles;


float randfloat() {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

float randfloat(float max) {
    return randfloat() * max;
}

float randfloat(float min, float max) {
    return randfloat(max - min) + min;
}

void spawn_particle(float x, float y) {
    Particle p;
    p.position.x = x;
    p.position.y = y;

    p.velocity = vec2(randfloat(-100, 100), randfloat(-100, 100));

    particles.push_back(p);
}

void event_handler(SDL_Event& event) {
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            close = true;
            break;
            
        case SDL_MOUSEBUTTONDOWN:
            break;

        default:
            break;
        }
    }
}

int main() {
    SDL_Renderer* renderer;
    SDL_Window* window;

    // Initialize
    srand (static_cast <unsigned> (time(0)));

    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Particle Simulation");
    TTF_Init();

    TTF_Font* arial = TTF_OpenFont("resources/fonts/arial.ttf", 32);

    float deltaTime = 0;

    // Main loop
    while(!close) {
        uint32_t start = SDL_GetTicks();

        SDL_Event event;

        float entropy = 0;
        float energy = 0;

        // Event loop
        event_handler(event);

        int mx, my;

        if(SDL_GetMouseState(&mx, &my) & SDL_BUTTON_LMASK) {
            spawn_particle(mx, my);
            SDL_Delay(1000 / 240.0f);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        
        // Draw here

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(auto &i : particles) {
            for(auto &j : particles) {
                if(&j == &i) continue;
                
                entropy += (i.velocity - j.velocity).length();

                i.attract(j);
                i.repel(j);
            }
        }

        for(auto &i : particles) {
            i.update(deltaTime);

            energy += 1 + i.velocity.length() * i.velocity.length() / 2;

            SDL_RenderDrawPoint(renderer, i.position.x, i.position.y);
        }

        entropy /= particles.size() * particles.size();

        std::string entropy_str = fmt::format("Entropy: {}", entropy);
        std::string energy_str = fmt::format("Energy: {}", energy);
        std::string particles_str = fmt::format("Particles: {}", particles.size());
        SDL_Surface* surfaceEntropy = TTF_RenderText_Solid(arial, entropy_str.c_str(), {255, 255, 255});
        SDL_Surface* surfaceEnergy = TTF_RenderText_Solid(arial, energy_str.c_str(), {255, 255, 255});
        SDL_Surface* surfaceParticles = TTF_RenderText_Solid(arial, particles_str.c_str(), {255, 255, 255});

        SDL_Texture* entropyMsg = SDL_CreateTextureFromSurface(renderer, surfaceEntropy);
        SDL_Texture* energyMsg = SDL_CreateTextureFromSurface(renderer, surfaceEnergy);
        SDL_Texture* particlesMsg = SDL_CreateTextureFromSurface(renderer, surfaceParticles);

        SDL_Rect entropy_rect;
        entropy_rect.x = 10;
        entropy_rect.y = 10;
        entropy_rect.w = 250;
        entropy_rect.h = 32;

        SDL_Rect energy_rect;
        energy_rect.x = 10;
        energy_rect.y = 52;
        energy_rect.w = 200;
        energy_rect.h = 32;

        SDL_Rect particles_rect;
        particles_rect.x = 10;
        particles_rect.y = 94;
        particles_rect.w = 200;
        particles_rect.h = 32;

        TTF_SizeText(arial, entropy_str.c_str(), &entropy_rect.w, &entropy_rect.h);
        TTF_SizeText(arial, energy_str.c_str(), &energy_rect.w, &energy_rect.h);
        TTF_SizeText(arial, particles_str.c_str(), &particles_rect.w, &particles_rect.h);

        SDL_RenderCopy(renderer, entropyMsg, nullptr, &entropy_rect);
        SDL_RenderCopy(renderer, energyMsg, nullptr, &energy_rect);
        SDL_RenderCopy(renderer, particlesMsg, nullptr, &particles_rect);

        SDL_RenderPresent(renderer);

        SDL_FreeSurface(surfaceEntropy);
        SDL_FreeSurface(surfaceEnergy);
        SDL_FreeSurface(surfaceParticles);
        SDL_DestroyTexture(entropyMsg);
        SDL_DestroyTexture(energyMsg);
        SDL_DestroyTexture(particlesMsg);

        //SDL_Delay(1000 / 240.0f);

        uint32_t end = SDL_GetTicks();

        deltaTime = (end - start) / 1000.0f;
    }

    // Cleanup afterwards
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}