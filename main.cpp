#include <raylib.h>
#include "ParticlesWorld.hpp"


int main()
{
    InitWindow(1000, 1000, "Falling Particles");
    SetTargetFPS(60);

    Particles::ParticlesWorld particlesWorld;

    while (!WindowShouldClose())
    {
        PollInputEvents();
        BeginDrawing();
        ClearBackground(BLACK);
        particlesWorld.Draw();
        particlesWorld.Update(GetFrameTime());
        EndDrawing();
    }

    CloseWindow();

    return 0;
}