#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

using namespace std;

// Screen dimension constants
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 480;

// The window's title
const char* gWindow_title = "SCP232: Planetary Ring Systems";

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

        double X0 = box1_X1 + box1_X2 / 2;
        double Y0 = box1_Y1 + box1_Y2 / 2;
        
        double dt = 0.5;
        
        const int NUM = 1000;
        double X[NUM];
        double Y[NUM];
        double VX[NUM];
        double VY[NUM];
        double AX[NUM];
        double AY[NUM];
        
        double GM = 10000;

        double angle = 0.0, r = 120, dr = 2;

        for (int i = 0; i < NUM; i++) {

            angle = angle + 2 * pi / 300;
            
            if(angle > 2*pi) {
                angle = angle - 2*pi;
                r = r + dr;
            }
            
            X[i] = r * cos(angle);
            Y[i] = r * sin(angle);

            double v = sqrt(GM / r);

            // tangential velocity for orbit
            VX[i] = -sin(angle) * v;
            VY[i] =  cos(angle) * v;
        }

        // Moon properties
        double moon_r = 206.0;
        double moon_angle = 0.0; 
        double moon_v = sqrt(GM / moon_r); 

        double moonX = moon_r * cos(moon_angle);
        double moonY = moon_r * sin(moon_angle);
        double moonVX = -sin(moon_angle) * moon_v;
        double moonVY = cos(moon_angle) * moon_v;

        // Main loop
        while (!quit) {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            
            // Clear the screen
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(gRenderer);

            // Draw the box frame
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0x00);
            SDL_RenderDrawRect(gRenderer, &frameRect1);
            SDL_RenderDrawRect(gRenderer, &frameRect2);

            // Draw the ring particles
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 200, 255);
            for (int j = 0; j < NUM; j++) {
                SDL_RenderDrawPoint(gRenderer,X0 + X[j],Y0 - Y[j]);
            }
            
            // Draw planet
            SDL_SetRenderDrawColor(gRenderer, 255, 235, 100, 255);
            for (int r = 0; r <= 10; r++) {
                for (int i = 0; i < N; i++) {
                    SDL_RenderDrawPoint(
                        gRenderer,
                        X0 + r * cos(2 * pi * i / N),
                        Y0 + r * sin(2 * pi * i / N)
                    );
                }
            }

            //  Draw Moon 
            SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255); // Light grey color
            int moon_radius_draw = 5; 
            for (int r = 0; r <= moon_radius_draw; r++) {
                for (int i = 0; i < N; i++) {
                    SDL_RenderDrawPoint(
                    gRenderer,
                    X0 + moonX + r * cos(2 * pi * i / N),
                    Y0 - (moonY + r * sin(2 * pi * i / N)) // Note the Y-axis flip to match your ring drawing
                    );
                }   
            }

//  Moon Position 
double moon_r_dist3 = pow(moonX * moonX + moonY * moonY, 1.5);
double moonAX = -(GM / moon_r_dist3) * moonX;
double moonAY = -(GM / moon_r_dist3) * moonY;

moonX += moonVX * dt;
moonY += moonVY * dt;
moonVX += moonAX * dt;
moonVY += moonAY * dt;
            
            //call equations to move billiard ball
            for (int i = 0; i < NUM; i++) {

                double moonGM = 200.0; 


   
            double r3_planet = pow(X[i]*X[i] + Y[i]*Y[i], 1.5);
            double AX_planet = -(GM / r3_planet) * X[i];
            double AY_planet = -(GM / r3_planet) * Y[i];

    
    
            double dx = X[i] - moonX;
            double dy = Y[i] - moonY;
            double dist_to_moon_sq = dx*dx + dy*dy;
            double r3_moon = pow(dist_to_moon_sq, 1.5);

    // Gravitational pull towards the moon
            double AX_moon = -(moonGM / r3_moon) * dx;
            double AY_moon = -(moonGM / r3_moon) * dy;

    //Acceleration 
            AX[i] = AX_planet + AX_moon;
            AY[i] = AY_planet + AY_moon;

    // Velocity and Position 
            VX[i] += AX[i] * dt;
            VY[i] += AY[i] * dt;
            X[i] += VX[i] * dt;
            Y[i] += VY[i] * dt;
}

            

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