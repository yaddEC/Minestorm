#include <stdio.h>
#include <raylib.h>
#include "game.h"

void ObjectInit(Object *object)
{
    object->position.x = 640 / 2.f;
    object->position.y = 800 / 2;
    object->angle = 0;
    object->vel = 1;

}

void gameInit(Game *game)
{
    *game = (Game){0};

    ObjectInit(&game->player);
}

void playerUpdate(Object *player, Game *game)
{
    float xVec = sin(degToRad(player->angle));
    float yVec = cos(degToRad(player->angle));
    float magnitude = sqrt(xVec * xVec + yVec * yVec);
    float unitVecX = xVec / magnitude;
    float unitVecY = yVec / magnitude;

    if (IsKeyDown(KEY_LEFT))
    {
        player->angle -= 2;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player->angle += 2;
    }
    if (IsKeyDown(KEY_UP))
    {
        if (player->vel < 50)
        {
            player->vel ++;
            player->vel ++;
        }
        

        player->position.x += (unitVecX * (player->vel / 10));

        player->position.y -= (unitVecY * (player->vel / 10));
        player->dirx = unitVecX ;
        player->diry = unitVecY ;

    }
    else
    {
        if (player->vel > 0)
        {
            player->vel--;
        }

      

        player->position.x += (player->dirx * (player->vel / 10));

        player->position.y -= (player->diry* (player->vel / 10));


    }
}

void gameUpdateAndDraw(Game *game)
{
    playerUpdate(&game->player, game);
}