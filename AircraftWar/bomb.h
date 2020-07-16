#ifndef BOMB_H
#define BOMB_H
#include <QPixmap>
#include <QVector>
#include <config.h>

class Bomb
{
public:
    Bomb();

    void update(); //更新信息（播放图片下标、播放间隔）

    QVector<QPixmap> pixVec;//爆炸资源数组

    int x;
    int y;

    bool free;

    int recoder;

    int index;
};

#endif // BOMB_H
