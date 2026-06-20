#include <raylib.h>

int main()
{
    InitWindow(1000, 1000, "Falling Particles");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        PollInputEvents();
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}