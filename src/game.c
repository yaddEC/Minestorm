#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include "game.h"

static int pause = 0;

void playerInit(Triangle *player, int pos)
{
    player->object.position.x = 640 / 2.f + pos;
    player->object.position.y = 800 / 2 + pos;
    player->object.angle = 0;
    player->object.t= 1;
    player->cot1.x = player->object.position.x;
    player->cot1.y = player->object.position.y - 25;
    player->cot2.x = player->object.position.x - 20;
    player->cot2.y = player->object.position.y + 22.5;
    player->cot3.x = player->object.position.x + 16;
    player->cot3.y = player->object.position.y + 22.5;
}

void gameInit(Game *game)
{


    if(game->coop==false){
    playerInit(&game->player[0],0);
    }
    else
    {
        playerInit(&game->player[0],-15);
        playerInit(&game->player[1],15);
    } 
    
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

void rotateTriangle(Triangle *triangle)
{

    triangle->cot1 = rotateVec(triangle->hit1, triangle->object.position, triangle->object.angle);
    triangle->cot2 = rotateVec(triangle->hit2, triangle->object.position, triangle->object.angle);
    triangle->cot3 = rotateVec(triangle->hit3, triangle->object.position, triangle->object.angle);
}

void playerUpdate(Triangle *player, Game *game, int left,int right,int up)
{
    float xVec = sin(degToRad(player->object.angle));
    float yVec = cos(degToRad(player->object.angle));
    float magnitude = sqrt(xVec * xVec + yVec * yVec);
    float uVecX = xVec / magnitude;
    float uVecY = yVec / magnitude;

    player->hit1.x = player->object.position.x;
    player->hit1.y = player->object.position.y - 25;
    player->hit2.x = player->object.position.x - 20;
    player->hit2.y = player->object.position.y + 22.5;
    player->hit3.x = player->object.position.x + 16;
    player->hit3.y = player->object.position.y + 22.5;

    rotateTriangle(player);

    if (player->object.position.x < 40)
    {
        player->object.position.x = 555;
    }
    if (player->object.position.x > 600)
    {
        player->object.position.x = 85;
    }

    if (player->object.position.y < 40)
    {
        player->object.position.y = 685;
    }
    if (player->object.position.y > 685)
    {
        player->object.position.y = 40;
    }
    if (IsKeyDown(left))
    {
        player->object.angle -= 2.5;
    }
    if (IsKeyDown(right))
    {
        player->object.angle += 2.5;
    }
    if (IsKeyDown(up))
    {
        if (player->object.t < 55)
        {
            player->object.t++;
            player->object.t++;
        }
        player->object.position.x += (uVecX * (player->object.t / 10));
        player->object.position.y -= (uVecY * (player->object.t / 10));
        player->object.dir.x = uVecX;
        player->object.dir.y = uVecY;
    }
    else
    {
        if (player->object.t > 0)
        {
            player->object.t--;
        }

        player->object.position.x += (player->object.dir.x * (player->object.t / 10));
        player->object.position.y -= (player->object.dir.y * (player->object.t / 10));
    }
}

void gameUpdateAndDraw(Game *game)
{

    playerUpdate(&game->player[0], game,KEY_D,KEY_G,KEY_R);
    if(game->coop==true)
    {
    playerUpdate(&game->player[1], game,KEY_J,KEY_L,KEY_I);
    }
}

int gameUI(Game *game)
{

    if (pause == 0)
    {
        
        if (IsKeyPressed(KEY_F))
        {
            pause++;
            game->coop = false;
             gameInit(game);
        }

        if (IsKeyPressed(KEY_K))
        {
            pause++;
            game->coop = true;
            gameInit(game);
        }
    }

    else if (IsKeyPressed(KEY_SPACE))
    {
        pause++;
    }
    return pause;
}