#include <raylib.h>
#include <mathematics.h>
int main(void)
{
    const int screenWidth = 640;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    Image background = LoadImage("assets/minestorm_background.png");
    Image foreground = LoadImage("assets/minestorm_foreground.png");
    Texture2D textback = LoadTextureFromImage(background);
    Texture2D textfore = LoadTextureFromImage(foreground);
    UnloadImage(background);
    UnloadImage(foreground);

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(textback, 0, 0, WHITE);
        DrawTexture(textfore, 0, 0, WHITE);

        EndDrawing();
    }
    UnloadTexture(textback);
    UnloadTexture(textfore);
    CloseWindow();

    return 0;
}