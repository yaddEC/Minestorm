#include <raylib.h>
#include "game.h"

int main(void)
{
    const int screenWidth = 640;
    const int screenHeight = 800;

    Game game = {0};
    gameInit(&game);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    Image background = LoadImage("assets/minestorm_background.png");
    Image foreground = LoadImage("assets/minestorm_foreground.png");
    Image ship = LoadImage("assets/assets.png");
    Texture2D textship = LoadTextureFromImage(ship);
    int width = textship.width / 4;
    int height = textship.height / 2;
    UnloadImage(ship);

    Rectangle source = {0.0f, 0.0f, (float)width, (float)height};

    Rectangle dest = {screenWidth / 2.0f, screenHeight / 2.0f, width / 3, height / 3};

    Vec origin = {(float)width / 6, (float)height / 6};

    Texture2D textback = LoadTextureFromImage(background);
    Texture2D textfore = LoadTextureFromImage(foreground);

    UnloadImage(background);
    UnloadImage(foreground);

    // Main game loop
    while (!WindowShouldClose())
    {
        dest.x = game.player.object.position.x;
        dest.y = game.player.object.position.y;
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(textback, 0, 0, WHITE);
        DrawText(TextFormat("ANGLE: %f", game.player.object.angle), 100, 130, 30, WHITE);
        DrawText(TextFormat("x: %f   y:%f", game.player.cot1.x, game.player.cot1.y), 100, 160, 30, WHITE);
        gameUpdateAndDraw(&game);
        DrawTexturePro(textship, source, dest, origin, (float)game.player.object.angle, RED);
        drawBorder(&game.player, textship, source, dest, origin, (float)game.player.object.angle, WHITE);
        DrawTriangleLines(game.player.cot1, game.player.cot2, game.player.cot3, WHITE);
        DrawTexture(textfore, 0, 0, WHITE);

        EndDrawing();
    }
    UnloadTexture(textback);
    UnloadTexture(textfore);
    UnloadTexture(textship);
    CloseWindow();

    return 0;
}