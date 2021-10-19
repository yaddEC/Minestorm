#include <stdio.h>
#include <raylib.h>
#include "game.h"

static int t = 1;
void ObjectInit(Object *object)
{
    object->position.x = 640 / 2.f;
    object->position.y = 800 / 2;
    object->angle = 0;
}

void gameInit(Game *game)
{
    *game = (Game){0};
    ObjectInit(&game->player);
}

void drawBorder(Object *player, Texture2D texture, Rectangle source, Rectangle dest, Vec origin, float rotation, Color tint){
    Rectangle change = dest;
    if(player->position.x<=85)
{
    change.x = 515+(player->position.x) ;
    DrawTexturePro(texture, source, change, origin, (float)player->angle, WHITE);
    
}
if(player->position.x>=555)
{
    change.x = player->position.x-515;
    DrawTexturePro(texture, source, change, origin, (float)player->angle, WHITE);
}

if(player->position.y<85)
{
    change.y = 645+(player->position.y);
    DrawTexturePro(texture, source, change, origin, (float)player->angle, WHITE);
}
if(player->position.y>685)
{
    change.y = player->position.y-645;
    DrawTexturePro(texture, source, change, origin, (float)player->angle, WHITE);
}
}

void playerUpdate(Object *player, Game *game)
{
    float xVec = sin(degToRad(player->angle));
    float yVec = cos(degToRad(player->angle));
    float magnitude = sqrt(xVec * xVec + yVec * yVec);
    float unitVecX = xVec / magnitude;
    float unitVecY = yVec / magnitude;
    
if(player->position.x<40)
{
    player->position.x=555;
}
if(player->position.x>600)
{
    player->position.x=85;
}

if(player->position.y<40)
{
    player->position.y=685;
}
if(player->position.y>685)
{
    player->position.y=40;
}
    if (IsKeyDown(KEY_LEFT))
    {
        player->angle -= 2.5;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player->angle += 2.5;
    }
    if (IsKeyDown(KEY_UP))
    {
        if (t < 55)
        {
            t++;
            t++;
        }
        player->position.x += (unitVecX * (t / 10));
        player->position.y -= (unitVecY * (t / 10));
        player->vel.x = unitVecX;
        player->vel.y = unitVecY;
    }
    else
    {
        if (t > 0)
        {
            t--;
        }

        player->position.x += (player->vel.x * (t / 10));
        player->position.y -= (player->vel.y * (t / 10));
    }
}

void gameUpdateAndDraw(Game *game)
{
    playerUpdate(&game->player, game);
}