#include <raylib.h>
#include "game.h"

int main(void)
{
    const int screenWidth = 640;
    const int screenHeight = 800;
    float inutile;
    Game game = {0};
    int ui;
    InitWindow(screenWidth, screenHeight, "Minestorm");
    SetTargetFPS(120);
    Image background = LoadImage("assets/minestorm_background.png");
    Image foreground = LoadImage("assets/minestorm_foreground.png");
    Image assets = LoadImage("assets/assets.png");
    Image assetmine = LoadImage("assets/assetsmine.png");
    Texture2D textship = LoadTextureFromImage(assets);
    Texture2D textmine1 = LoadTextureFromImage(assetmine);
    int width = textship.width / 4;
    int height = textship.height / 2;

    
    Rectangle source = {0.0f, 0.0f, (float)width, (float)height};
    Rectangle source2 = {0.0f, 0.0f, (float)textmine1.width, (float)textmine1.height};
    Rectangle source22 = {0.0f, 0.0f, (float)textmine1.width, (float)textmine1.height};
    Rectangle source23 = {0.0f, 0.0f, (float)textmine1.width, (float)textmine1.height};

    Rectangle dest = {screenWidth / 2.0f, screenHeight / 2.0f, width / 3, height / 3};
    Rectangle dest2 = {screenWidth * 2.0f, (screenHeight * 2.0f), (width / 3) / 2, (height / 3) / 2};
    Rectangle dest3 = {screenWidth / 2.0f, screenHeight / 2.0f, (width / 3) / 3, (height / 3) / 3};

    Vec origin = {(float)width / 6, (float)height / 6};
    Vec origin2 = {((float)width / 6) / 2, ((float)height / 6) / 2};
    Vec origin3 = {((float)width / 6) / 3, ((float)height / 6) / 3};
    Texture2D textback = LoadTextureFromImage(background);
    Texture2D textfore = LoadTextureFromImage(foreground);
   
    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(textback, 0, 0, WHITE);
        ui = gameUI(&game);
        if (ui == 0)
        {
            DrawText(TextFormat("SINGLEPLAYER: PRESS F"), 100, 130, 30, WHITE);
            DrawText(TextFormat("MULTIPLAYER : PRESS K"), 100, 170, 30, WHITE);
            DrawText(TextFormat("QUIT : PRESS ESCAPE"), 100, 210, 30, WHITE);
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

                isGameOver(&game);
                gameUpdateAndDraw(&game);
               
                if (game.coop == true)
                {
                    if (game.player[0].object.life > 0)
                    {
                        DrawText(TextFormat("life: %d", game.player[0].object.life), 70, 70, 20, ORANGE);
                    }
                    else
                    {
                        DrawText(TextFormat("life: 0"), 70, 70, 20, ORANGE);
                    }

                    dest.x = game.player[0].object.position.x;
                    dest.y = game.player[0].object.position.y;

                    if (game.player[1].object.life > 0)
                    {
                        DrawText(TextFormat("life: %d", game.player[1].object.life), 520, 70, 20, BLUE);
                    }
                    else
                    {
                        DrawText(TextFormat("life: 0"), 520, 70, 20, BLUE);
                    }
                    if (game.player[0].invincibilityFrame < 0)
                    {
                        DrawTexturePro(textship, source, dest, origin, (float)game.player[0].object.angle, BLUE);
                    }
                    else
                    {
                        if (game.player[0].invincibilityFrame % 3 == 0)
                        {
                            DrawTexturePro(textship, source, dest, origin, (float)game.player[0].object.angle, BLUE);
                        }
                    }

                    drawBorder(&game.player[0], textship, source, dest, origin, (float)game.player[0].object.angle, BLUE);

                    dest.x = game.player[1].object.position.x;
                    dest.y = game.player[1].object.position.y;

                    if (game.player[1].invincibilityFrame < 0)
                    {
                        DrawTexturePro(textship, source, dest, origin, (float)game.player[1].object.angle, ORANGE);
                    }
                    else
                    {
                        if (game.player[1].invincibilityFrame % 3 == 0)
                        {
                            DrawTexturePro(textship, source, dest, origin, (float)game.player[1].object.angle, ORANGE);
                        }
                    }
                    drawBorder(&game.player[1], textship, source, dest, origin, (float)game.player[1].object.angle, ORANGE);
                }
                else
                {
                    dest.x = game.player[0].object.position.x;
                    dest.y = game.player[0].object.position.y;

                    if (game.player[0].object.life > 0)
                    {
                        DrawText(TextFormat("life: %d", game.player[0].object.life), 70, 70, 20, YELLOW);
                    }
                    else
                    {
                        DrawText(TextFormat("life: 0"), 70, 70, 20, YELLOW);
                    }
                    if (game.player[0].invincibilityFrame < 0)
                    {
                        DrawTexturePro(textship, source, dest, origin, (float)game.player[0].object.angle, YELLOW);
                    }
                    else
                    {
                        if (game.player[0].invincibilityFrame % 3 == 0)
                        {
                            DrawTexturePro(textship, source, dest, origin, (float)game.player[0].object.angle, YELLOW);
                        }
                    }
                    drawBorder(&game.player[0], textship, source, dest, origin, (float)game.player[0].object.angle, YELLOW);
                }

                for (int i = 0; i < 35; i++)
                {

                    if (game.ennemy[i].object.life > 0)
                    {
                        if (game.ennemy[i].size == 1)
                        {
                            dest.x = game.ennemy[i].object.position.x;
                            dest.y = game.ennemy[i].object.position.y;

                            DrawTexturePro(textmine1, source2, dest, origin, (float)game.ennemy[i].object.angle, WHITE);
                        }
                        else if (game.ennemy[i].size == 2)
                        {

                            dest2.x = game.ennemy[i].object.position.x;
                            dest2.y = game.ennemy[i].object.position.y;

                            DrawTexturePro(textmine1, source22, dest2, origin2, (float)game.ennemy[i].object.angle, WHITE);
                        }
                        else if (game.ennemy[i].size == 3)
                        {

                            dest3.x = game.ennemy[i].object.position.x;
                            dest3.y = game.ennemy[i].object.position.y;

                            DrawTexturePro(textmine1, source23, dest3, origin3, (float)game.ennemy[i].object.angle, WHITE);
                        }
                    }
                }

                break;
            }
        }
        DrawTexture(textfore, 0, 0, WHITE);
        EndDrawing();
    }
    UnloadTexture(textback);
    UnloadTexture(textfore);
    UnloadTexture(textship);
    UnloadTexture(textmine1);
    UnloadImage(background);
    UnloadImage(foreground);
    UnloadImage(assets);
    UnloadImage(assetmine);
    CloseWindow();
    return 0;
}