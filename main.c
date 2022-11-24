#include <SDL2/SDL.h> 

#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

// Time passed since last frame
double timeElapsed;
// Time since game started
long timeSinceStart;

// Put game logic code in here
// e.g. player or enemy movement
void update() {

}

// Draw sprites here
void draw() {

}

int main() {
    if(SDL_CreateWindowAndRenderer(600, 800, 0, &window, &renderer)) {
        printf("Error '%s' creating SDL window and renderer!\n", SDL_GetError());
        return 1;
    }

    timeSinceStart = SDL_GetTicks64();

    int isRunning = 1;
    while(isRunning) {
        // Ok so SDL_GetTicks64 returns the time (in milliseconds) since the program started
        // (SDL_GetTicks64() - timeSinceStart) gets the difference in milliseconds between frames.
        // Then we divide this by 1000.0, getting a double that is the time in seconds instead
        // This makes things a bit easier having the time as a decimal in seconds.
        timeElapsed = (SDL_GetTicks64() - timeSinceStart) / 1000.0;
        timeSinceStart = SDL_GetTicks64();

        // SDL_PollEvent returns 0 if there are no events
        // If it returns 1 there is an event and the 'ev' variable is filled with the event data.
        // An example of an event is 'SDL_QUIT' indiciating the 'X' button on the window was pressed.
        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            if(ev.type == SDL_QUIT) {
                isRunning = 0;
            }
        }

        update();
        draw();

        SDL_RenderPresent(renderer);
    }

    return 0;
}
