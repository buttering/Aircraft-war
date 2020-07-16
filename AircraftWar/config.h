#ifndef CONFIG_H
#define CONFIG_H
#define WIN_WIDTH 900  // 窗口宽度
#define WIN_HEIGHT 900  // 窗口高度
#define REFRESH_INTERVAL 10// 刷新间隔
#define BLANK_PATH "://recource/blank.png"

#define BG_SPEED 1 // 背景平移速度
#define BG_PATH "://recource/background-big.jpg"

#define PLANE_PATH ":/recource/plane1.png"
#define PLANE_PATH2 "://recource/plane2.png"
#define PLANE_SPEED 2

#define BULLET_PATH "://recource/bullet.png"
#define BULLET_SPEED 5
#define BULLET_INTERVAL 20 // 发射子弹间隔
#define BULLET_NUM 15

#define ENEMY_PATH "://recource/enemy.png"
#define ENEMY_SPEED 4
#define ENEMY_NUM 20
#define ENEMY_INTERVAL_MIN 20  // 敌机出场间隔
#define ENEMY_INTERVAL_MAX 100

#define BOMB_PATH ":/recource/bomb-%1.png"
#define BOMB_NUM 20
#define BOMB_MAX 6
#define BOMB_INTERVAL 5

#define JUDGE_SQUARE 15  // 判断鼠标位置用于移动飞机的阈值
#endif // CONFIG_H

