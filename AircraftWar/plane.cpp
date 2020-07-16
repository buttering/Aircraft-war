#include "plane.h"
#include "config.h"

Plane::Plane()
{

    plane.load(PLANE_PATH);
    planeX = WIN_WIDTH * 0.5 - plane.width() * 0.5;
    planeY = WIN_HEIGHT - plane.height();

    destoried = false;
    // 初始均未按下
    pressRight = false;
    pressLeft = false;
    pressUp = false;
    pressDown = false;
    pressSpace = false;

    launchInaterval = 0;  // 初始化子弹间隔
    speed = PLANE_SPEED;
}



void Plane::setPosition(int x, int y){
    planeX = x;
    planeY = y;
    rect.moveTo(planeX,planeY);
}

void Plane::load(int player){
    if(player == 1){
        plane.load(PLANE_PATH);
    }else if(player == 2){
        plane.load(PLANE_PATH2);
    }

    rect.setWidth(plane.width());
    rect.setHeight(plane.height());
    rect.moveTo(planeX,planeY);
}

void Plane::shoot(){
    if(destoried){// 被摧毁，不允许发射子弹
        return;
    }
    launchInaterval ++;
    if (launchInaterval < BULLET_INTERVAL){//判断如果记录数字 未达到发射间隔，直接return
        return;
    }

    launchInaterval = 0;//到达发射时间,重置发射时间间隔记录

    for(int i = 0; i < BULLET_NUM; i++){  //发射第一颗空闲的子弹，计算发射位置
        if(bullets[i].free){
            bullets[i].free = false;
            bullets[i].x = planeX + rect.width() * 0.5 - bullets[i].bullet.width() * 0.5;
            bullets[i].y = planeY;
            break;
        }
    }
}

void Plane::destory(){
    destoried = true;
    plane.load(BLANK_PATH);
}

void Plane::moveToLeft(){
    if(destoried){
        return;
    }
    int x = planeX - speed;
    if( x <= 0 ){
        x = 0;
    }
    setPosition(x, planeY);
}
void Plane::moveToRight(){
    if(destoried){
        return;
    }
    int x = planeX + speed;
    if( x >= WIN_WIDTH - rect.width() ){
        x = WIN_WIDTH - rect.width();
    }
    setPosition(x, planeY);
}
void Plane::moveToUp(){
    if(destoried){
        return;
    }
    int y = planeY - speed;
    if( y <= 0 ){
        y = 0;
    }
    setPosition(planeX, y);
}
void Plane::moveToDown(){
    if(destoried){
        return;
    }
    int y = planeY + speed;
    if( y >= WIN_HEIGHT - rect.height() ){
        y = WIN_HEIGHT - rect.height();
    }
    setPosition(planeX, y);
}
