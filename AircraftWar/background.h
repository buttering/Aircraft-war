#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QPixmap>

class BackGround
{
public:
    BackGround();

    void BGPan();  // 处理地图平移
    QPixmap BG1;  // 使用两张图片实现平滑移动
    QPixmap BG2;

    int BGy1;   //地图Y轴坐标
    int BGy2;
    bool isSu;

};

#endif // BACKGROUND_H
