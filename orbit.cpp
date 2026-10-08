#include <iostream>
#include <SDL2/SDL.h>
#include <cmath> 

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Planetary Orbit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event ev;

    float angle = 0.0f;
    float radius = 200.0f;
    float speed = 0.01f; 

    while (running) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) running = false;
        }

        // 
        angle += speed;

        // position
        int x = (WIDTH / 2) + static_cast<int>(radius * cos(angle));
        int y = (HEIGHT / 2) + static_cast<int>(radius * sin(angle));

        // 2. Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Sun
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
        SDL_Rect sun = {WIDTH/2 - 10, HEIGHT/2 - 10, 20, 20};
        SDL_RenderFillRect(renderer, &sun);

        // Particle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
        SDL_Rect particle = {x, y, 5, 5}; 
        SDL_RenderFillRect(renderer, &particle);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

