#include <raylib.h>
#include "game.h"

int main(void)
{
    const int screenWidth = 640;
    const int screenHeight = 800;
    Game game = {0};

    int ui;
    InitWindow(screenWidth, screenHeight, "Minestorm");
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

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(textback, 0, 0, WHITE);
        ui = gameUI(&game);
        if (ui == 0)
        {
            DrawText(TextFormat("Mode solo : Appuyez sur F"), 100, 130, 30, WHITE);
            DrawText(TextFormat("Mode coop : Appuyez sur K"), 100,170, 30, WHITE);
        }
        else
        {
            ui = ui % 2;
            switch (ui)
            {
            case 0:
                DrawText(TextFormat("PAUSE"), 270, screenHeight / 2.0f, 30, WHITE);
                break;
            case 1:
                gameUpdateAndDraw(&game);

                dest.x = game.player[0].object.position.x;
                dest.y = game.player[0].object.position.y;
                DrawTexturePro(textship, source, dest, origin, (float)game.player[0].object.angle, RED);
                drawBorder(&game.player, textship, source, dest, origin, (float)game.player[0].object.angle, WHITE);
                DrawTriangleLines(game.player[0].cot1, game.player[0].cot2, game.player[0].cot3, WHITE);
                if(game.coop==true)
                {
                dest.x = game.player[1].object.position.x;
                dest.y = game.player[1].object.position.y;
                DrawTexturePro(textship, source, dest, origin, (float)game.player[1].object.angle, GREEN);
                drawBorder(&game.player, textship, source, dest, origin, (float)game.player[1].object.angle, WHITE);
                DrawTriangleLines(game.player[1].cot1, game.player[1].cot2, game.player[1].cot3, WHITE);

                }

                DrawText(TextFormat("x:%p, x2:%p",game.player[0],game.player[0] ), 100, 130, 30, WHITE);
                
                break;
            }
        }
        DrawTexture(textfore, 0, 0, WHITE);
        EndDrawing();
    }
    UnloadTexture(textback);
    UnloadTexture(textfore);
    UnloadTexture(textship);
    CloseWindow();
    return 0;
}