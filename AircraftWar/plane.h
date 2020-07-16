#ifndef PLANE_H
#define PLANE_H
#include <QPixmap>
#include <QRect>
#include "bullet.h"
#include "config.h"

class Plane
{
public:
    Plane();  // 构造函数
    void load(int player);  // 载入图片
    void shoot(); // 控制子弹出现
    void setPosition(int x, int y);
    void destory();  // 被摧毁
    // 控制方向
    void moveToRight();
    void moveToLeft();
    void moveToUp();
    void moveToDown();


    QPixmap plane;  // 飞机图片对象

    int planeX;
    int planeY;
    int speed;  // 飞机移动速度
    int launchInaterval;  // 发射间隔
    bool destoried;  // 是否被摧毁

    // 使用标志位区分键盘放下和松开事件
    bool pressRight;
    bool pressLeft;
    bool pressUp;
    bool pressDown;
    bool pressSpace;

    QRect rect;  // 飞机的矩形边框


    Bullet bullets[BULLET_NUM]; //弹匣
};

#endif // PLANE_H
