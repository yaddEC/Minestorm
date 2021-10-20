#include <stdio.h>
#include <raylib.h>
#include "game.h"

static int t = 1;
void playerInit(Triangle *player)
{
    player->object.position.x = 640 / 2.f;
    player->object.position.y = 800 / 2;
    player->object.angle = 0;
    player->cot1.x = player->object.position.x;
    player->cot1.y = player->object.position.y - 25;

    player->cot2.x = player->object.position.x - 20;
    ;
    player->cot2.y = player->object.position.y + 22.5;

    player->cot3.x = player->object.position.x + 16;
    player->cot3.y = player->object.position.y + 22.5;
}

void gameInit(Game *game)
{
    *game = (Game){0};
    playerInit(&game->player);
}

void drawBorder(Triangle *player, Texture2D texture, Rectangle source, Rectangle dest, Vec origin, float rotation, Color tint)
{
    Rectangle change = dest;
    if (player->object.position.x <= 85)
    {
        change.x = 515 + (player->object.position.x);
        DrawTexturePro(texture, source, change, origin, (float)player->object.angle, RED);
    }
    if (player->object.position.x >= 555)
    {
        change.x = player->object.position.x - 515;
        DrawTexturePro(texture, source, change, origin, (float)player->object.angle, RED);
    }

    if (player->object.position.y < 85)
    {
        change.y = 645 + (player->object.position.y);
        DrawTexturePro(texture, source, change, origin, (float)player->object.angle, RED);
    }
    if (player->object.position.y > 685)
    {
        change.y = player->object.position.y - 645;
        DrawTexturePro(texture, source, change, origin, (float)player->object.angle, RED);
    }
}

void playerUpdate(Triangle *player, Game *game)
{
    float xVec = sin(degToRad(player->object.angle));
    float yVec = cos(degToRad(player->object.angle));
    float magnitude = sqrt(xVec * xVec + yVec * yVec);
    float uVecX = xVec / magnitude;
    float uVecY = yVec / magnitude;

//mettre en fonction rotation autour d'un point
    player->cot1.x=yVec*( player->object.position.x - player->object.position.x) - xVec * ((player->object.position.y-25)-player->object.position.y) + player->object.position.x;
    player->cot1.y=xVec*( player->object.position.x - player->object.position.x) + yVec * ((player->object.position.y-25)-player->object.position.y) + player->object.position.y;

    player->cot2.x=yVec*((player->object.position.x - 20) - player->object.position.x) - xVec * ((player->object.position.y + 22.5)-player->object.position.y) + player->object.position.x;
    player->cot2.y=xVec *((player->object.position.x - 20) - player->object.position.x) + yVec * ((player->object.position.y + 22.5)-player->object.position.y) + player->object.position.y;

    player->cot3.x=yVec*((player->object.position.x + 16)- player->object.position.x) - xVec * ((player->object.position.y + 22.5)-player->object.position.y) + player->object.position.x;
    player->cot3.y=xVec *((player->object.position.x + 16) - player->object.position.x) + yVec * ((player->object.position.y + 22.5)-player->object.position.y) + player->object.position.y;

if(player->object.position.x<40)
{
        player->object.position.x = 555;
}
if(player->object.position.x>600)
{
        player->object.position.x = 85;
}

if(player->object.position.y<40)
{
        player->object.position.y = 685;
}
if(player->object.position.y>685)
{
        player->object.position.y = 40;
}
    if (IsKeyDown(KEY_LEFT))
    {
        player->object.angle -= 2.5;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player->object.angle += 2.5;
    }
    if (IsKeyDown(KEY_UP))
    {
        if (t < 55)
        {
            t++;
            t++;
        }
        player->object.position.x += (uVecX * (t / 10));
        player->object.position.y -= (uVecY * (t / 10));
        player->object.dir.x = uVecX;
        player->object.dir.y = uVecY;
    }
    else
    {
        if (t > 0)
        {
            t--;
        }

        player->object.position.x += (player->object.dir.x * (t / 10));
        player->object.position.y -= (player->object.dir.y * (t / 10));
    }
}

void gameUpdateAndDraw(Game *game)
{
    playerUpdate(&game->player, game);
}