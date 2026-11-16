#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

using namespace std;

// Screen dimension constants
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 480;

// The window's title
const char* gWindow_title = "SCP232: SDL2 Template";

// Create the window
SDL_Window* gWindow = NULL;

// Creates a renderer to render our graphics
SDL_Renderer* gRenderer = NULL;

bool gINIT() {
    bool success = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << "\n";
        success = false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow(gWindow_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL) {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
            success = false;
        } else {
            // Creates a renderer to render our images
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

            if (gRenderer == NULL) {
                cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
                success = false;
            }
        }
    }

    return success;
}

void gCLOSE() {
    // Destroy renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL
    SDL_Quit();
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (gINIT()) {
        bool quit = false;
        SDL_Event e;

        const int N = 100;
        const double pi = 4 * atan(1.0);

        int margin = 3;
        int box1_X1 = margin, box1_Y1 = margin, box1_X2 = SCREEN_WIDTH / 2 - 2 * margin, box1_Y2 = SCREEN_HEIGHT - 2 * margin;
        SDL_Rect frameRect1 = {box1_X1, box1_Y1, box1_X2, box1_Y2};
        int box2_X1 = SCREEN_WIDTH / 2, box2_Y1 = margin, box2_X2 = SCREEN_WIDTH / 2 - margin, box2_Y2 = SCREEN_HEIGHT - 2 * margin;
        SDL_Rect frameRect2 = {box2_X1, box2_Y1, box2_X2, box2_Y2};

        double X0 = box1_X1 + box1_X2 / 2, Y0 = box1_Y1 + box1_Y2 / 2;
        double dt = 0.01;
        double R = 10, X, Y, VX, VY;

        //acceleration uninitialized
        double AX, AY; 

        // Set initial positions and velocities (VX, VY unused now but kept)
        X = 100.0;
        Y = 0.0;
        VX = 0; // launches particle vertically 
        VY = 100.0;

       

        double GM = 10000;
        

        

        // Main loop
        while (!quit) {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            // Draw planet
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

            for (int r = 0; r <= R; r++) {
                for (int i = 0; i < N; i++) {
                    SDL_RenderDrawPoint(
                        gRenderer,
                        X0 + r * cos(2 * pi * i / N),
                        Y0 + r * sin(2 * pi * i / N)
                    );
                }
            }


            //equation
            double r3 = pow(X*X + Y*Y, 3/2); 
    
            AX = - (GM/r3)*X;
            AY = - (GM/r3)*Y;

            // Clear the screen
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(gRenderer);

            // Draw the box frame
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0x00);
            SDL_RenderDrawRect(gRenderer, &frameRect1);
            SDL_RenderDrawRect(gRenderer, &frameRect2);

            // Draw the billiard ball
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
            for (int i = 0; i < N; i++) {
                SDL_RenderDrawPoint(gRenderer,
                    X0 + X + R * cos(2 * pi / N * i),
                    Y0 - Y + R * sin(2 * pi / N * i));
            }

            //call equations to move billiard ball 
            X = X + VX*dt;
            Y = Y + VY* dt;
            
            VX = VX + AX*dt;
            VY = VY + AY*dt;

            // Update the screen
            SDL_RenderPresent(gRenderer);

            // Delay frame rate = 120 fps
            SDL_Delay(1000 / 120);
        }
    }

    // Free resources and close SDL
    gCLOSE();

    return 0;
}