#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include <QPixmap>
#include <QRect>

class EnemyPlane
{
public:
    EnemyPlane();
    void updatePisition();


    QPixmap enemy;  //敌机图片对象

    int x;
    int y;

    QRect rect;

    bool free;  //敌机状态
    int speed;  // 速度

};

#endif // ENEMYPLANE_H
