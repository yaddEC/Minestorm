#pragma once

typedef struct Object
{
    Vec position;
    float angle;
    Vec vel;
} Object;

typedef struct Game
{
    Object player;

    int life;
} Game;

void gameInit(Game *game);
void gameUpdateAndDraw(Game *game);
bool gameIsOver(Game *game);
void drawBorder(Object *player, Texture2D texture, Rectangle source, Rectangle dest, Vec origin, float rotation, Color tint);