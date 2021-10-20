#pragma once

typedef struct Object
{
    Vec position;
    float angle;
    Vec dir;
} Object;

typedef struct Triangle
{
    Object object;
    Vec cot1;
    Vec cot2;
    Vec cot3;
} Triangle;

typedef struct Game
{
    Triangle player;
    int life;
} Game;

void gameInit(Game *game);
void gameUpdateAndDraw(Game *game);
bool gameIsOver(Game *game);
void drawBorder(Triangle* player, Texture2D texture, Rectangle source, Rectangle dest, Vec origin, float rotation, Color tint);