#include <SDL2/SDL.h> 

#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

// Time passed since last frame
double timeElapsed;
// Time since game started
long timeSinceStart;

int main() {
    if(SDL_CreateWindowAndRenderer(600, 800, 0, &window, &renderer)) {
        printf("Error '%s' creating SDL window and renderer!\n", SDL_GetError());
        return 1;
    }

    timeSinceStart = SDL_GetTicks64();

    int isRunning = 1;
    while(isRunning) {
        timeElapsed = (SDL_GetTicks64() - timeSinceStart) / 1000.0;
        timeSinceStart = SDL_GetTicks64();

        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            if(ev.type == SDL_QUIT) {
                isRunning = 0;
            }
        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}
