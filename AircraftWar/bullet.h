#ifndef BULLET_H
#define BULLET_H
#include <QPixmap>
#include <QRect>

class Bullet
{
public:
    Bullet();

    void updatePosition();

    QPixmap bullet;
    int x;
    int y;

    int panSpeed;//子弹移动速度

    bool free; //子弹是否闲置

    QRect rect;
};

#endif // BULLET_H
