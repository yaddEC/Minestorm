#include <raylib.h>
#include "game.h"

void projetOrtho(Vec A, Vec B, Vec C, Vec *K, Vec *Bp, Vec *Mem)
{
    float a1 = (B.y - A.y) / (B.x - A.x);
    float b1 = C.y - (a1 * C.x);
    float a2 = (Bp->y - K->y) / (Bp->x - K->x);
    float b2 = Bp->y - (a2 * Bp->x);
    float x = (b2 - b1) / (a1 - a2);
    float y = a2 * x + b2;
    Mem->x = x;
    Mem->y = y;
}

void rangeCreator(Vec A, Vec B, Vec C, Vec *K, Vec *Bp)
{
    Vec AK;
    Vec AB;
    Vec KBp;
    AB = negate(B, A);
    AK.x = AB.x * 2;
    AK.y = AB.y * 2;
    KBp.y = AK.y;
    KBp.x = -(AK.y * AK.y) / AK.x;
    K->x = B.x + AB.x;
    K->y = B.y + AB.y;
    Bp->x = KBp.x + K->x;
    Bp->y = KBp.y + K->y;
    projetOrtho(A, B, C, K, Bp, Bp);
}

float minFinder(float k1, float k2, float k3)
{
   

    if (k1 < k2 && k1 < k3)
    {
        return k1;
    }
    if (k2 < k1 && k2 < k3)
    {
        return k2;
    }
    if (k3 < k2 && k3 < k1)
    {
        return k3;
    }
}

bool colTriangle(Vec A1, Vec B1, Vec C1, Vec A2, Vec B2, Vec C2)
{
    Vec K;
    Vec Bp;
    Vec Kpb;
    Vec Mem;
    Vec Memo;
    Vec Mem2;
    Vec Memo2;
    Vec Mem3;
    Vec Memo3;

    float k1;
    float k2;
    float k3;
    float kmin;

    rangeCreator(A1, B1, C1, &K, &Bp);
    DrawLine(A1.x, A1.y, K.x, K.y, ORANGE);
    DrawLine(C1.x, C1.y, Bp.x, Bp.y, ORANGE);
    projetOrtho(A1, B1, A2, &K, &Bp, &Mem);

    Kpb = negate(Bp, K);
    Memo = negate(Mem, Bp);

    k1 = Kpb.x / Memo.x;
    DrawLine(Mem.x, Mem.y, A2.x, A2.y, RED);
    projetOrtho(A1, B1, B2, &K, &Bp, &Mem2);
    Memo2 = negate(Mem2, Bp);
    k2 = Kpb.x / Memo2.x;
    DrawLine(Mem2.x, Mem2.y, B2.x, B2.y, RED);
    projetOrtho(A1, B1, C2, &K, &Bp, &Mem3);
    Memo3 = negate(Mem3, Bp);
    k3 = Kpb.x / Memo3.x;
    DrawLine(Mem3.x, Mem3.y, C2.x, C2.y, RED);
    kmin = minFinder(k1, k2, k3);
    kmin = sqrt(kmin * kmin);

    DrawText(TextFormat("k1 : %f,k2 : %f,k3 : %f,kmin : %f", k1, k2, k3, kmin), 75, 300, 20, WHITE);
    if (kmin >= 1)
    {
        return true;
    }
    return false;
}

Vec negate(Vec lhs, Vec rhs)
{
    Vec ret;
    ret.x = lhs.x - rhs.x;
    ret.y = lhs.y - rhs.y;
    return ret;
}

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
    Vec test;
    Vec test2;

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
            DrawText(TextFormat("Mode coop : Appuyez sur K"), 100, 170, 30, WHITE);
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

                if (game.coop == true)
                {
                    dest.x = game.player[0].object.position.x;
                    dest.y = game.player[0].object.position.y;
                    if (colTriangle(game.player[0].cot1, game.player[0].cot2, game.player[0].cot3, game.player[1].cot1, game.player[1].cot2, game.player[1].cot3) == true)
                    {

                        DrawTexturePro(textship, source, dest, origin, (float)game.player[0].object.angle, YELLOW);
                    }
                    else
                    {

                        DrawTexturePro(textship, source, dest, origin, (float)game.player[0].object.angle, RED);
                    }

                    drawBorder(&game.player[0], textship, source, dest, origin, (float)game.player[0].object.angle, RED);
                    DrawTriangleLines(game.player[0].cot1, game.player[0].cot2, game.player[0].cot3, WHITE);
                    dest.x = game.player[1].object.position.x;
                    dest.y = game.player[1].object.position.y;
                    DrawTexturePro(textship, source, dest, origin, (float)game.player[1].object.angle, GREEN);
                    drawBorder(&game.player[1], textship, source, dest, origin, (float)game.player[1].object.angle, GREEN);
                    DrawTriangleLines(game.player[1].cot1, game.player[1].cot2, game.player[1].cot3, WHITE);
                    rangeCreator(game.player[0].cot1, game.player[0].cot2, game.player[1].cot1, &test, &test2);
                    DrawLine(test.x, test.y, test2.x, test2.y, WHITE);
                }
                else
                {
                    dest.x = game.player[0].object.position.x;
                    dest.y = game.player[0].object.position.y;
                    DrawTexturePro(textship, source, dest, origin, (float)game.player[0].object.angle, WHITE);
                    drawBorder(&game.player[0], textship, source, dest, origin, (float)game.player[0].object.angle, WHITE);
                    DrawTriangleLines(game.player[0].cot1, game.player[0].cot2, game.player[0].cot3, WHITE);
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
    CloseWindow();
    return 0;
}