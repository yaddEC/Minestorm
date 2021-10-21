#pragma once

typedef struct Object
{   
    int life;
    int t;
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
    Vec hit1;
    Vec hit2;
    Vec hit3;
} Triangle;

typedef struct Game
{
    Triangle player[2];
    
    bool coop;
    
} Game;

void gameInit(Game *game);
void gameUpdateAndDraw(Game *game);
bool gameIsOver(Game *game);
void drawBorder(Triangle* player, Texture2D texture, Rectangle source, Rectangle dest, Vec origin, float rotation, Color tint);
int gameUI(Game *game);