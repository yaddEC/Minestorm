#pragma once

typedef struct Object
{
    Vec position;
    float angle;
    float vel;
    float dirx;
    float diry;

} Object;

typedef struct Game
{
    Object player;

    int life;
} Game;

void gameInit(Game *game);
void gameUpdateAndDraw(Game *game);
bool gameIsOver(Game *game);