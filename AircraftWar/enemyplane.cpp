#include "enemyplane.h"
#include "config.h"
EnemyPlane::EnemyPlane()
{
    enemy.load(ENEMY_PATH);
    // 设置敌机默认状态
    x = 0;
    y = 0;


    free = true;
    speed = ENEMY_SPEED;

    rect.setWidth(enemy.width());
    rect.setHeight(enemy.height());
    rect.moveTo(x, y);

}

void EnemyPlane::updatePisition(){
    if(free){  // 空闲状态不计算敌机坐标
        return;
    }

    y += speed;
    rect.moveTo(x, y);

    if(y >= WIN_HEIGHT + rect.height()){  // 离开边界，释放敌机
        free = true;
    }
}

