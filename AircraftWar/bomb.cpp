#include "bomb.h"
#include "config.h"
#include <QString>

Bomb::Bomb()
{
    // 初始化摧毁数组
    for(int i = 1; i <= BOMB_MAX; i++){
        QString str = QString(BOMB_PATH).arg(i);
        pixVec.push_back(QPixmap(str));
    }

    x = 0;
    y = 0;

    free = true;
    // 从下标0开始播放
    index = 0;

    recoder = 0;
}

void Bomb::update(){
    if(free){
        // 不需渲染
        return;
    }
    recoder ++;
    if(recoder < BOMB_INTERVAL){
        return;
    }
    recoder = 0;

    index ++;

    if(index > BOMB_MAX - 1){  // 播放完毕
        index = 0;
        free = true;
    }
}
