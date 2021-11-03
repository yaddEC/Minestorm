#include <stdio.h>
#include <raylib.h>

#include "game.h"

static int pause = 0;
void playerInit(Triangle *player, int pos)
{
    player->object.position.x = 640 / 2.f + pos*2;
    player->object.position.y = 800 / 2 ;
    player->object.angle = 0;
    player->object.t = 1;
    player->cot1.x = player->object.position.x;
    player->cot1.y = player->object.position.y - 25;
    player->cot2.x = player->object.position.x - 20;
    player->cot2.y = player->object.position.y + 22.5;
    player->cot3.x = player->object.position.x + 16;
    player->cot3.y = player->object.position.y + 22.5;
    player->object.life = 3;
    player->bulletCount = 0;
}

void ennemyInit(Mine1 *ennemy)
{
    float x = GetRandomValue(40,600);
    float y = GetRandomValue(40,685);

    while (y == 400)
    {
        y = GetRandomValue(40,685);
    }

    ennemy->object.position.x = x;
    ennemy->object.position.y = y;
    ennemy->hitbox[0].cot1.x = ennemy->object.position.x;
    ennemy->hitbox[0].cot1.y = ennemy->object.position.y - 44;
    ennemy->hitbox[0].cot2.x = ennemy->object.position.x - 14;
    ennemy->hitbox[0].cot2.y = ennemy->object.position.y + 5;
    ennemy->hitbox[0].cot3.x = ennemy->object.position.x + 14;
    ennemy->hitbox[0].cot3.y = ennemy->object.position.y + 5;
    
    ennemy->hitbox[1].cot1.x = ennemy->object.position.x - 14;
    ennemy->hitbox[1].cot1.y = ennemy->object.position.y + 5;
    ennemy->hitbox[1].cot2.x = ennemy->object.position.x - 43;
    ennemy->hitbox[1].cot2.y = ennemy->object.position.y + 43;
    ennemy->hitbox[1].cot3.x = ennemy->object.position.x ;
    ennemy->hitbox[1].cot3.y = ennemy->object.position.y +32;

     ennemy->hitbox[2].cot1.x = ennemy->object.position.x + 14;
    ennemy->hitbox[2].cot1.y = ennemy->object.position.y + 5;
    ennemy->hitbox[2].cot2.x = ennemy->object.position.x ;
    ennemy->hitbox[2].cot2.y = ennemy->object.position.y +32;
    ennemy->hitbox[2].cot3.x = ennemy->object.position.x +43;
    ennemy->hitbox[2].cot3.y = ennemy->object.position.y +43;

    ennemy->hitbox[3].cot1.x = ennemy->object.position.x - 14;;
    ennemy->hitbox[3].cot1.y = ennemy->object.position.y + 5;
    ennemy->hitbox[3].cot2.x = ennemy->object.position.x + 14;
    ennemy->hitbox[3].cot2.y = ennemy->object.position.y + 5;
    ennemy->hitbox[3].cot3.x = ennemy->object.position.x ;
    ennemy->hitbox[3].cot3.y =  ennemy->object.position.y +32;

    ennemy->object.angle = GetRandomValue(0,360);
    ennemy->object.dir.x = GetRandomValue(0,360);
    ennemy->object.life = 1;




}

void gameInit(Game *game)
{
    if (game->coop == false)
    {
        playerInit(&game->player[0], 0);
    }
    else
    {
        playerInit(&game->player[0], -15);
        playerInit(&game->player[1], 15);
    }

    int i = 0;
    while(i<35){
    ennemyInit(&game->ennemy[i]);
    i=i+7;
    }
    

}

void addBullet(Triangle *player, Vec bulletPos)
{
    Bullet bullet = {0};
    bullet.delay = 50;
    bullet.object.position = bulletPos;
    bullet.object.angle = player->object.angle;
    bullet.object.life = 1;

    for (int i = 0; i < 6; i++)
    {
        if (player->bullets[i].object.life == 0)
        {
            player->bulletCount += 1;
            player->bullets[i] = bullet;
            break;
        }
    }
}

void remBullet(Triangle *player, Bullet *bullet)
{
    player->bulletCount--;
    bullet->object.life = 0;
}


void bulletUpdate(Bullet *bullet)
{
    if (bullet->object.life > 0)
    {
        float xVec = sin(degToRad(bullet->object.angle));
        float yVec = cos(degToRad(bullet->object.angle));

        bullet->object.position.x += xVec * 6;
        bullet->object.position.y -= yVec * 6;

        if (bullet->object.position.x < 40)
        {
            bullet->object.position.x = 555;
        }
        if (bullet->object.position.x > 600)
        {
            bullet->object.position.x = 85;
        }

        if (bullet->object.position.y < 40)
        {
            bullet->object.position.y = 685;
        }
        if (bullet->object.position.y > 685)
        {
            bullet->object.position.y = 40;
        }
        DrawCircle(bullet->object.position.x, bullet->object.position.y, 3, YELLOW);
        bullet->delay -= 1;
        if (bullet->delay < 0)
        {
            bullet->object.life = 0;
        }
    }
}

void drawBorder(Triangle *player, Texture2D texture, Rectangle source, Rectangle dest, Vec origin, float rotation, Color tint)
{
    Rectangle change = dest;
    if (player->object.position.x <= 85)
    {
        change.x = 515 + (player->object.position.x);
        DrawTexturePro(texture, source, change, origin, (float)player->object.angle, tint);
    }
    if (player->object.position.x >= 555)
    {
        change.x = player->object.position.x - 515;
        DrawTexturePro(texture, source, change, origin, (float)player->object.angle, tint);
    }
    if (player->object.position.y < 85)
    {
        change.y = 645 + (player->object.position.y);
        DrawTexturePro(texture, source, change, origin, (float)player->object.angle, tint);
    }
    if (player->object.position.y > 685)
    {
        change.y = player->object.position.y - 645;
        DrawTexturePro(texture, source, change, origin, (float)player->object.angle, tint);
    }
}

void rotateTriangle(Triangle *triangle)
{

    triangle->cot1 = rotateVec(triangle->hit1, triangle->object.position, triangle->object.angle);
    triangle->cot2 = rotateVec(triangle->hit2, triangle->object.position, triangle->object.angle);
    triangle->cot3 = rotateVec(triangle->hit3, triangle->object.position, triangle->object.angle);
}

void rotateTriangleMine(Triangle *triangle, Vec pos, float angle)
{

    triangle->cot1 = rotateVec(triangle->hit1,pos, angle);
    triangle->cot2 = rotateVec(triangle->hit2,pos, angle);
    triangle->cot3 = rotateVec(triangle->hit3,pos, angle);
}

void ennemyUpdate(Mine1 *ennemy)
{
    
  
    
    
    if (ennemy->object.life > 0)
    {
    ennemy->hitbox[0].hit1.x = ennemy->object.position.x;
    ennemy->hitbox[0].hit1.y = ennemy->object.position.y - 44;
    ennemy->hitbox[0].hit2.x = ennemy->object.position.x - 14;
    ennemy->hitbox[0].hit2.y = ennemy->object.position.y + 5;
    ennemy->hitbox[0].hit3.x = ennemy->object.position.x + 14;
    ennemy->hitbox[0].hit3.y = ennemy->object.position.y + 5;   
    ennemy->hitbox[1].hit1.x = ennemy->object.position.x - 14;
    ennemy->hitbox[1].hit1.y = ennemy->object.position.y + 5;
    ennemy->hitbox[1].hit2.x = ennemy->object.position.x - 43;
    ennemy->hitbox[1].hit2.y = ennemy->object.position.y + 43;
    ennemy->hitbox[1].hit3.x = ennemy->object.position.x ;
    ennemy->hitbox[1].hit3.y = ennemy->object.position.y +32;
    ennemy->hitbox[2].hit1.x = ennemy->object.position.x + 14;
    ennemy->hitbox[2].hit1.y = ennemy->object.position.y + 5;
    ennemy->hitbox[2].hit2.x = ennemy->object.position.x ;
    ennemy->hitbox[2].hit2.y = ennemy->object.position.y +32;
    ennemy->hitbox[2].hit3.x = ennemy->object.position.x +43;
    ennemy->hitbox[2].hit3.y = ennemy->object.position.y +43;
    ennemy->hitbox[3].hit1.x = ennemy->object.position.x - 14;;
    ennemy->hitbox[3].hit1.y = ennemy->object.position.y + 5;
    ennemy->hitbox[3].hit2.x = ennemy->object.position.x + 14;
    ennemy->hitbox[3].hit2.y = ennemy->object.position.y + 5;
    ennemy->hitbox[3].hit3.x = ennemy->object.position.x ;
    ennemy->hitbox[3].hit3.y =  ennemy->object.position.y +32;

    rotateTriangleMine(&ennemy->hitbox[0],ennemy->object.position,ennemy->object.angle);
    rotateTriangleMine(&ennemy->hitbox[1],ennemy->object.position,ennemy->object.angle);
    rotateTriangleMine(&ennemy->hitbox[2],ennemy->object.position,ennemy->object.angle);
    rotateTriangleMine(&ennemy->hitbox[3],ennemy->object.position,ennemy->object.angle);

        ennemy->object.angle++;

    

        float xVec = sin(degToRad(ennemy->object.dir.x));
        float yVec = cos(degToRad(ennemy->object.dir.x));

        ennemy->object.position.x += xVec * 2;
        ennemy->object.position.y -= yVec * 2;

        if (ennemy->object.position.x < 40)
        {
            ennemy->object.position.x = 555;
        }
        if (ennemy->object.position.x > 600)
        {
            ennemy->object.position.x = 85;
        }

        if (ennemy->object.position.y < 40)
        {
            ennemy->object.position.y = 685;
        }
        if (ennemy->object.position.y > 685)
        {
            ennemy->object.position.y = 40;
        }
      
    }
}



void playerUpdate(Triangle *player, Game *game, int left, int right, int up, int shoot)
{
    float xVec = sin(degToRad(player->object.angle));
    float yVec = cos(degToRad(player->object.angle));

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
    if (IsKeyPressed(shoot) && player->bulletCount < 6)
    {
        addBullet(player, player->cot1);
    }
    if (IsKeyDown(left))
    {
        player->object.angle -= 1.75;
    }
    if (IsKeyDown(right))
    {
        player->object.angle += 1.75;
    }
    if (IsKeyDown(up))
    {
        if (player->object.t < 80)
        {
            player->object.t++;
            player->object.t++;
        }
        player->object.position.x += (xVec * (player->object.t / 20));
        player->object.position.y -= (yVec * (player->object.t / 20));
        player->object.dir.x = xVec;
        player->object.dir.y = yVec;
    }
    else
    {
        if (player->object.t > 0)
        {
            player->object.t--;
        }

        player->object.position.x += (player->object.dir.x * (player->object.t / 20));
        player->object.position.y -= (player->object.dir.y * (player->object.t / 20));
    }

    for (int i = 5; i > 0; i--)
    {

        bulletUpdate(&player->bullets[i]);
        if (player->bullets[i].object.life == 0)
        {

            remBullet(player, &player->bullets[i]);
        }
    }
}

void gameUpdateAndDraw(Game *game)
{

    playerUpdate(&game->player[0], game, KEY_D, KEY_G, KEY_R, KEY_F);
    
    for(int i=0; i<35;i++){
    ennemyUpdate(&game->ennemy[i]);
    }
    if (game->coop == true)
    {
        playerUpdate(&game->player[1], game, KEY_J, KEY_L, KEY_I, KEY_K);
        //coll(player1, player2)
        //coll(player2, player1)
        //loop coll (player 1, mine[i])
        //loop coll (player 2, mine[i])
    }
    else
    {
        //loop coll (player 1, mine[i])
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