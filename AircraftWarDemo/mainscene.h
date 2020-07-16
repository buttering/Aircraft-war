#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "map.h"
#include <QWidget>
#include <QTimer>

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = 0);
    ~MainScene();
    void initScene();
    QTimer m_Timer;

    //启动游戏  用于启动定时器对象
        void playGame();
        //更新坐标
        void updatePosition();
        //绘图事件
        void paintEvent(QPaintEvent *event);

        //地图对象
        Map m_map;

};

#endif // MAINSCENE_H
