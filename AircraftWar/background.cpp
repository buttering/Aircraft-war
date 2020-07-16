#include <iostream>
#include "background.h"
#include "config.h"

BackGround::BackGround()
{
    BG1.load(BG_PATH);  //添加背景图片
    BG2.load(BG_PATH);

    BGy1 = -WIN_HEIGHT;  // 背景图初始坐标
    BGy2 = 0;

}
void BackGround::BGPan(){
    BGy1 += BG_SPEED;
    BGy2 += BG_SPEED;
    if(BGy1 >= 0){
        BGy1 = -WIN_HEIGHT;
    }

    if(BGy2 >= WIN_HEIGHT){
        BGy2 = 0;
    }
}
