#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPaintEvent>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QComboBox>
#include <QSlider>
#include "background.h"
#include "plane.h"
#include "bullet.h"
#include "enemyplane.h"
#include "bomb.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initGame();  //启动游戏
    void updatePosition();// 更新坐标
    void planeFly();  // 判断键盘标志位以选择对应位置函数
    void enemyAppear();  // 控制敌机出场
    void destroyEnemy();  // 检测子弹与敌机的碰撞
    void restart();  // 重新开始游戏
    void setScoreToLabel(int label, int score);
    // 定义不同模式的按钮和标签状态
    void singleModel();
    void doubleModel();
    void readyModel();  // 主菜单
    void clear();  // 清屏
    void planeFlyWithMouse();  // 计算飞机随鼠标移动的方向

    BackGround background;// 背景图片对象
    Plane plane; // 飞机对象
    Plane plane2;  // 玩家2飞机对象
    QTimer timer;  // 定时器
    EnemyPlane enemies[ENEMY_NUM];  // 敌机对象数组
    Bomb bombs[BOMB_NUM];  // 爆炸对象数组
    int mouseX;  // 鼠标位置
    int mouseY;

    bool isSingle;  // 区分模式
    QLabel* labelDifficulty;  // 难度
    QPushButton* buttonSingle;  // 单人模式
    QPushButton* buttonDouble;  // 双人模式
    QLabel* labelScore1;  // 展示玩家一得分
    QLabel* labelScore2;  // 展示玩家二得分
    QLabel* labelSettlement;  // 结算页面
    QSlider* sliderDifficulty;  // 控制难度

    void paintEvent(QPaintEvent *event);// 绘图事件
    void mouseMoveEvent(QMouseEvent *event);// 鼠标移动事件
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);  // 键盘按下事件
    void keyReleaseEvent(QKeyEvent *event);  // 键盘释放事件

private:
    int enemyInatervalUpperLimit;  // 用户选择的难度
    int enemyInaterval;  // 敌机出场间隔,用于计时
    int score1;  // 玩家1得分
    int score2;  // 玩家2得分

public slots:

    void startDouble();
    void startSingle();
    void getInaterval();  // 获得用户所选难度
};

#endif // MAINWINDOW_H
