#include <SDL2/SDL.h> 

#include <stdio.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800

#define PLAYER_WIDTH 24
#define PLAYER_HEIGHT 24

#define PLAYER_MOVEMENT_SPEED 400

SDL_Window* window;
SDL_Renderer* renderer;

// Time passed since last frame
double timeElapsed;
// Time since game started
long timeSinceStart;

// This is a struct that represents a co-ordinate pair
// What the typedef does is define 'alias' for our struct.
// This just means that our struct has two names now, 'struct Position' and 'pos_t'
// When using typedef it is customary to add a '_t' on the end of the type. 
typedef struct Position {
    double x, y;
} pos_t;

// Let's store player data in a struct,
// this allows all player data to be grouped in one place
struct Player {
    pos_t pos;
    int lives;
};
struct Player player;

struct Enemy {
    pos_t pos;
};

const unsigned char* keysPressed;

// Put game logic code in here
// e.g. player or enemy movement
void update() {
    // It is important that we multiply by timeElapsed,
    // as the game will not always run at the same framerate.
    
    // If we just added say 100 to the player's X coordinate each frame
    // the player would move slower or faster depending on how many times
    // a second update() runs (tied to the framerate)

    // By multiplying with the time we ensure that the player moves at a constant speed

    if(keysPressed[SDL_SCANCODE_W]) {
        player.pos.y -= PLAYER_MOVEMENT_SPEED * timeElapsed;
    }

    if(keysPressed[SDL_SCANCODE_S]) {
        player.pos.y += PLAYER_MOVEMENT_SPEED * timeElapsed;
    }

    if(keysPressed[SDL_SCANCODE_A]) {
        player.pos.x -= PLAYER_MOVEMENT_SPEED * timeElapsed;
    }

    if(keysPressed[SDL_SCANCODE_D]) {
        player.pos.x += PLAYER_MOVEMENT_SPEED * timeElapsed;
    }
}

// Draw sprites here
void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // SDL has its own 'SDL_Rect' structure to represent a rectangle that gets drawn on screen
    // Lets convert the position of the player into an SDL_Rect
    SDL_Rect playerRect = {
        player.pos.x - PLAYER_WIDTH / 2,
        player.pos.y - PLAYER_HEIGHT / 2,
        PLAYER_WIDTH,
        PLAYER_HEIGHT
    };

    // Everything in SDL is honestly named quite well, read the names of the functions
    // and figure out what they do
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);
}

// By putting this in a function, first of all the code is cleaner as each logical task has its own function
// Second of all the code can be reused, as we may want to reset the Player struct when they die.
void player_init() {
    player.pos.x = SCREEN_WIDTH / 2;
    player.pos.y = SCREEN_HEIGHT - 50 - PLAYER_HEIGHT;

    player.lives = 3;
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    if(SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer)) {
        printf("Error '%s' creating SDL window and renderer!\n", SDL_GetError());
        return 1;
    }

    timeSinceStart = SDL_GetTicks64();

    player_init();

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

        // Each frame we get an array which indicates if each keyboard key is pressed or not
        keysPressed = SDL_GetKeyboardState(NULL);

        update();
        draw();

        SDL_RenderPresent(renderer);
    }

    return 0;
}
