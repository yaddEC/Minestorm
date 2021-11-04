#pragma once

typedef struct Object
{
    int life;
    int t;
    Vec position;
    float angle;
    Vec dir;
} Object;

typedef struct Bullet
{
    Object object;
    int delay;
} Bullet;

typedef struct Triangle
{
    Object object;
    int bulletCount;
    int invincibilityFrame;
    Bullet bullets[6];
    Vec cot1;
    Vec cot2;
    Vec cot3;
    Vec hit1;
    Vec hit2;
    Vec hit3;
} Triangle;

typedef struct Mine1
{
    Object object;
    Triangle hitbox[4];
    float size;
} Mine1;

typedef struct Game
{
    Triangle player[2];
    Mine1 ennemy[35];
    bool coop;

} Game;

void gameInit(Game *game, bool coop);
bool noMineLeft(Game *game);
void gameUpdateAndDraw(Game *game);
void isGameOver(Game *game);
void drawBorder(Triangle *player, Texture2D texture, Rectangle source, Rectangle dest, Vec origin, float rotation, Color tint);
int gameUI(Game *game);