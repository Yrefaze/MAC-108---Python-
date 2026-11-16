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
        
        int XB0 = box2_X1 + box2_X2 / 4;
        int YB0 = box2_Y1 + box2_Y2 / 4 * 3;
        
        // Ring
        const int NUM = 6000;
        double X[NUM],Y[NUM];
        double VX[NUM],VY[NUM];
        double GM = 10000;
        const int NP = 1000;           // Number of physics steps
        double dt = 0.8;              // Overall speed
        double dtp = dt / NP;         // Tiny accurate step

        double angle = 0.0, r = 122, dr = 1;

        const int NB = 10;
        int bin[NB],rbmin = 116,rbmax = 146,rbstep = (rbmax - rbmin)/NB;
        
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

        
        // Moon1 properties
        double moon_r = 210.0;
        double moon_angle = 0.0;
        double moon_v = sqrt(GM / moon_r);

        double moonX = moon_r * cos(moon_angle);
        double moonY = moon_r * sin(moon_angle);
        double moonVX = -sin(moon_angle) * moon_v;
        double moonVY = cos(moon_angle) * moon_v;
        
        
        // Moon2 properties
        double moon2_r = 83.0;
        double moon2_angle = pi / 2.0;
        double moon2_v = sqrt(GM / moon2_r);
        
        double moon2X = moon2_r * cos(moon2_angle);
        double moon2Y = moon2_r * sin(moon2_angle);
        double moon2VX = -sin(moon2_angle) * moon2_v;
        double moon2VY =  cos(moon2_angle) * moon2_v;
        
        
        // Main loop
        while (!quit) {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            
            for(int i = 0; i < NB; i ++ ) {
                bin[i] = 0; // set = 0
            }
            
            for(int i = 0; i < NUM; i ++ ) { // calculate distribution
                double rdist = sqrt(X[i] * X[i] + Y[i] * Y[i]);
                int j = static_cast<int>((rdist - rbmin) / rbstep);
                // cout << rdist << " " << j << "\n";
                bin[j] ++;
            }
                
        // Clear the screen
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);

        // Draw the box frame
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0x00);
        SDL_RenderDrawRect(gRenderer, &frameRect1);
        SDL_RenderDrawRect(gRenderer, &frameRect2);

        // bin structure
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0x00);
        for(int i = 0; i < NB; i ++ ) { // calculate distribution
            SDL_Rect frameBin = {XB0 + rbmin + i * rbstep * 2, YB0 - bin[i] / 10, 2 * rbstep, bin[i] / 10};
            SDL_RenderDrawRect(gRenderer, &frameBin);
        }
        
        // Draw the ring particles
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 200, 255);
        for (int j = 0; j < NUM; j += 3)
            SDL_RenderDrawPoint(gRenderer,(int)(X0 + X[j]), (int)(Y0 - Y[j]) // integer rounding
        );
            
        // Draw planet
        SDL_SetRenderDrawColor(gRenderer, 255, 235, 100, 255);
        for (int r = 0; r <= 10; r++) {
            for (int i = 0; i < N; i++) {
                SDL_RenderDrawPoint(
                    gRenderer,X0 + r * cos(2 * pi * i / N),Y0 + r * sin(2 * pi * i / N)
                );
            }
        }
            
        // Draw Moon1
            SDL_SetRenderDrawColor(gRenderer, 200, 200, 200, 255);
        int moon_radius_draw = 5;
        for (int r = 0; r <= moon_radius_draw; r++) {
            for (int i = 0; i < N; i++) {
                SDL_RenderDrawPoint(
                    gRenderer,(int)(X0 + moonX + r * cos(2 * pi * i / N)),(int)(Y0 - (moonY + r * sin(2 * pi * i / N)))
                );
            }
        }

        // Draw Moon2
        SDL_SetRenderDrawColor(gRenderer, 150, 200, 255, 255);
        for (int r = 0; r <= moon_radius_draw; r++) {
            for (int i = 0; i < N; i++) {
                SDL_RenderDrawPoint(
                    gRenderer,(int)(X0 + moon2X + r * cos(2 * pi * i / N)),(int)(Y0 - (moon2Y + r * sin(2 * pi * i / N)))
                );
            }
        }





for (int step = 0; step < NP; step++) {

    // A. CALCULATE MOON PHYSICS
    double m_dist_sq = moonX * moonX + moonY * moonY;
    double m_dist = sqrt(m_dist_sq);
    // Gravity acceleration from the star
    double m_ax = -(GM / (m_dist_sq * m_dist)) * moonX;
    double m_ay = -(GM / (m_dist_sq * m_dist)) * moonY;

    // Update Moon Velocity then Position
    moonVX += m_ax * dtp;
    moonVY += m_ay * dtp;
    moonX += moonVX * dtp;
    moonY += moonVY * dtp;
    
    // inner moon orbit
    double m2_dist_sq=moon2X*moon2X+moon2Y*moon2Y;
    double m2_dist=sqrt(m2_dist_sq);

    double m2_ax=-(GM/(m2_dist_sq*m2_dist))*moon2X;
    double m2_ay=-(GM/(m2_dist_sq*m2_dist))*moon2Y;

    moon2VX+=m2_ax*dtp;
    moon2VY+=m2_ay*dtp;
    moon2X+=moon2VX*dtp;
    moon2Y+=moon2VY*dtp;


    // B. CALCULATE PARTICLE PHYSICS (Now inside the step loop!)
    for (int i = 0; i < NUM; i++) {
        // 1. Planet Gravity
        double p_dist_sq = X[i] * X[i] + Y[i] * Y[i];
        double inv_r3 = 1.0 / (p_dist_sq * sqrt(p_dist_sq));
        double p_ax = -GM * inv_r3 * X[i];
        double p_ay = -GM * inv_r3 * Y[i];

        // 2. Moon Gravity
        double dx = X[i] - moonX;
        double dy = Y[i] - moonY;
        double dist_m_sq = dx * dx + dy * dy;
        double dist_m = sqrt(dist_m_sq);
        double moonGM = 5.0;
        double inv_r31 = 1.0 / (dist_m_sq * sqrt(dist_m_sq));
        double m_ax_p = -(moonGM * inv_r31 * dx);
        double m_ay_p = -(moonGM * inv_r31 * dy);

        // inner moon gravity
        double dx2=X[i]-moon2X;
        double dy2=Y[i]-moon2Y;

        double dist2_sq = dx2*dx2+dy2*dy2+0.01;
        double dist2 = sqrt(dist2_sq);
        double inv_r32 = 1.0 / (dist2_sq * sqrt(dist2_sq));
        double m2_ax_p = -(moonGM * inv_r32 * dx2);
        double m2_ay_p = -(moonGM * inv_r32 * dy2);
        
        // 3. Update Particle Velocity then Position
        X[i] += VX[i] * dtp + 0.5 * (p_ax + m_ax_p) * dtp * dtp;
        Y[i] += VY[i] * dtp + 0.5 * (p_ay + m_ay_p) * dtp * dtp;
        VX[i] += (p_ax + m_ax_p) * dtp;
        VY[i] += (p_ay + m_ay_p) * dtp;
    }
}


            static int frame = 0;
            frame++;

            if (frame % 2 == 0) {
                // render only every 2 frames
            }

            // Update the screen
            SDL_RenderPresent(gRenderer);

            // Delay frame rate
            SDL_Delay(0);
        }
    }

    
    gCLOSE();

    return 0;
}