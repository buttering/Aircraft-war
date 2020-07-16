#include "mainwindow.h"
#include "background.h"
#include "config.h"
#include "enemyplane.h"
#include <QWidget>
#include <QPainter>
#include <QtDebug>
#include <ctime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(WIN_WIDTH,WIN_HEIGHT);  // 初始化窗口，设置长宽
    setWindowTitle("Aircraft War");  // 设置标题
    score1 = 0;
    score2 = 0;
    isSingle = true;
    enemyInatervalUpperLimit = ENEMY_INTERVAL_MIN;
    timer.setInterval(REFRESH_INTERVAL);  // 设置刷新间隔为10ms
    setMouseTracking(true);  // 设定鼠标不需要点击即可触发移动事件
    plane.load(1);  // 为两机载入图片
    plane2.load(2);
    srand((unsigned int)time(NULL));

    buttonSingle = new QPushButton("Single Player");
    buttonDouble = new QPushButton("Double Player");
    sliderDifficulty = new QSlider();
    labelScore1 = new QLabel;
    labelScore2 = new QLabel;
    labelSettlement = new QLabel;
    labelDifficulty = new QLabel;


    labelSettlement->setText("WELCOME TO PLAY AIRCRAFTWAR!\n");
    QFont font;
    font.setPixelSize(20);
    labelSettlement->setFont(font);
    labelSettlement->setStyleSheet("color:blue;");
    sliderDifficulty->setOrientation(Qt::Horizontal);
    sliderDifficulty->setMinimum(ENEMY_INTERVAL_MIN);
    sliderDifficulty->setMaximum(ENEMY_INTERVAL_MAX);
    sliderDifficulty->setTickInterval(5);  // 设置刻度间隔
    sliderDifficulty->setTickPosition(QSlider::TicksAbove);  // 刻度在上方
    labelDifficulty->setText(QString::number(enemyInatervalUpperLimit));

    QHBoxLayout* layoutDifficulty = new QHBoxLayout;
    layoutDifficulty->addWidget(labelDifficulty);
    layoutDifficulty->addWidget(sliderDifficulty);

    QVBoxLayout* layoutButton = new QVBoxLayout;
    layoutButton->addStretch();
    layoutButton->addWidget(labelSettlement);
    layoutButton->addLayout(layoutDifficulty);
    layoutButton->addWidget(buttonSingle);
    layoutButton->addWidget(buttonDouble);
    layoutButton->addWidget(labelScore1);
    layoutButton->addWidget(labelScore2);
    setLayout(layoutButton);

    connect(buttonSingle,SIGNAL(clicked(bool)),this,SLOT(startSingle()));
    connect(buttonDouble,SIGNAL(clicked(bool)),this,SLOT(startDouble()));
    connect(sliderDifficulty,SIGNAL(valueChanged(int)),this,SLOT(getInaterval()));
    connect(&timer,&QTimer::timeout,[=](){  // 全局时钟
            // 敌机出场
            enemyAppear();
            // 判断方向键标志
            planeFlyWithMouse();
            planeFly();
            // 更新游戏中元素的坐标
            updatePosition();
            // 重新绘制图片
            update();  // 会唤起paintEvent函数
            // 碰撞检测
            destroyEnemy();
        });
}

MainWindow::~MainWindow()
{

}

void MainWindow::initGame(){

    enemyInaterval = 0;  // 初始化敌机出场间隔
    timer.start();


}

void MainWindow::updatePosition(){  // 控制每个对象的updatePosition（）的调用
    background.BGPan();  // 更新背景坐标
    for(int i = 0; i < BULLET_NUM; i++){// 如果子弹状态为非空闲.计算新位置
        if(!plane.bullets[i].free){
            plane.bullets[i].updatePosition();  // 更新子弹坐标
        }
        if(!plane2.bullets[i].free){
            plane2.bullets[i].updatePosition();
        }
    }
    for(int i = 0; i < ENEMY_NUM; i ++){  // 更新非空闲的敌机位置
        if(!enemies[i].free){
            enemies[i].updatePisition();
        }
    }
    for(int i = 0; i < BOMB_NUM; i++){  // 更新爆炸画面
        if(bombs[i].free == false){
            bombs[i].update();
        }
    }
}

void MainWindow::startSingle(){
    isSingle = true;
    singleModel();
    initGame();
}

void MainWindow::startDouble(){
    isSingle = false;
    doubleModel();
    initGame();
}

void MainWindow::getInaterval(){
    enemyInatervalUpperLimit = sliderDifficulty->value();
    labelDifficulty->setText(QString::number(enemyInatervalUpperLimit));
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    // qDebug() << 123131;

    painter.drawPixmap(0,background.BGy1,background.BG1);  // 绘制背景1 参数（x,y,Qpixmap对象)
    painter.drawPixmap(0,background.BGy2,background.BG2);  // 绘制背景2
    painter.drawPixmap(plane.planeX,plane.planeY,plane.plane);  // 绘制飞机

    for(int i = 0; i < BULLET_NUM; i++){
        if(!plane.bullets[i].free){
            painter.drawPixmap(plane.bullets[i].x, plane.bullets[i].y, plane.bullets[i].bullet);  // 绘制子弹
        }
    }
    for(int i = 0; i < ENEMY_NUM; i++){
        if(!enemies[i].free){
            painter.drawPixmap(enemies[i].x, enemies[i].y, enemies[i].enemy);  // 绘制敌机
        }
    }

    if( !isSingle ){
        painter.drawPixmap(plane2.planeX,plane2.planeY,plane2.plane);  // 绘制飞机2
        for(int i = 0; i < BULLET_NUM; i++){
            if(!plane2.bullets[i].free){
                painter.drawPixmap(plane2.bullets[i].x,plane2.bullets[i].y,plane2.bullets[i].bullet);  // 绘制飞机2的子弹
            }
        }
    }

    for(int i = 0; i < BOMB_NUM; i++){
        if(bombs[i].free == false){
            painter.drawPixmap(bombs[i].x,bombs[i].y,bombs[i].pixVec[bombs[i].index]);
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){  // 鼠标移动事件
    mouseX = event->x();  // 鼠标位置
    mouseY = event->y();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    plane2.pressSpace = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    plane2.pressSpace = false;
}

void MainWindow::keyPressEvent(QKeyEvent *event){  // 键盘按下事件
    switch (event->key()) {
    case Qt::Key_Right:  // 右箭头
        plane.pressRight = true;
        break;
    case Qt::Key_Left:  // 左箭头
        plane.pressLeft = true;
        break;
    case Qt::Key_Up:  // 上箭头
        plane.pressUp = true;
        break;
    case Qt::Key_Down:  // 下箭头
        plane.pressDown = true;
        break;
    case Qt::Key_Space:
        plane.pressSpace = true;      // 使飞机射出子弹
        break;
//    case Qt::Key_W:
//        plane2.pressUp = true;
//        break;
//    case Qt::Key_A:
//        plane2.pressLeft = true;
//        break;
//    case Qt::Key_S:
//        plane2.pressDown = true;
//        break;
//    case Qt::Key_D:
//        plane2.pressRight = true;
//        break;
//    case Qt::Key_Space:
//        plane2.pressSpace = true;
//        break;
    default:
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){  // 方向键释放，修改标志位
    switch (event->key()) {
    case Qt::Key_Right:  // 右箭头
        plane.pressRight = false;
        break;
    case Qt::Key_Left:  // 左箭头
        plane.pressLeft = false;
        break;
    case Qt::Key_Up:  // 上箭头
        plane.pressUp = false;
        break;
    case Qt::Key_Down:  // 下箭头
        plane.pressDown = false;
        break;
    case Qt::Key_Space:
        plane.pressSpace = false;
        break;
//    case Qt::Key_W:
//        plane2.pressUp = false;
//        break;
//    case Qt::Key_A:
//        plane2.pressLeft = false;
//        break;
//    case Qt::Key_S:
//        plane2.pressDown = false;
//        break;
//    case Qt::Key_D:
//        plane2.pressRight = false;
//        break;
//    case Qt::Key_Space:
//        plane2.pressSpace = false;
//        break;
    default:
        break;
    }
}

void MainWindow::planeFly(){
    if(plane.pressRight){
        plane.moveToRight();
    }
    if(plane.pressLeft){
        plane.moveToLeft();
    }
    if(plane.pressUp){
        plane.moveToUp();
    }
    if(plane.pressDown){
        plane.moveToDown();
    }
    if(plane.pressSpace){
        plane.shoot();
    }
    if(plane2.pressRight){
        plane2.moveToRight();
    }
    if(plane2.pressLeft){
        plane2.moveToLeft();
    }
    if(plane2.pressUp){
        plane2.moveToUp();
    }
    if(plane2.pressDown){
        plane2.moveToDown();
    }
    if(plane2.pressSpace){
        plane2.shoot();
    }
}

void MainWindow::planeFlyWithMouse(){
    int pX = plane2.planeX + plane.rect.width() * 0.5;  // 飞机中心点的位置
    int pY = plane2.planeY + plane.rect.height() * 0.5;
    // 以飞机当前位置设立一个九宫格，根据鼠标在九宫格的相对位置进行位移
    if( (mouseX-pX) < -JUDGE_SQUARE ){  // 左侧
        if ( (mouseY-pY) < -JUDGE_SQUARE ){  //左上
            plane2.pressLeft = true;
            plane2.pressUp = true;

            plane2.pressRight = false;
            plane2.pressDown = false;
            // qDebug() << "left up";
        }else if( (mouseY-pY) > JUDGE_SQUARE ){  // 左下
            plane2.pressLeft = true;
            plane2.pressDown = true;

            plane2.pressRight = false;
            plane2.pressUp = false;
            // qDebug() << "left down";
        }else{  // 左
            plane2.pressLeft = true;

            plane2.pressDown = false;
            plane2.pressUp = false;
            plane2.pressRight = false;
            // qDebug() << "left";
        }
    }else if( (mouseX-pX) > JUDGE_SQUARE ){  // 右侧
        if ( (mouseY-pY) < -JUDGE_SQUARE ){  // 右上
            plane2.pressRight = true;
            plane2.pressUp = true;

            plane2.pressLeft = false;
            plane2.pressDown = false;
        }else if( (mouseY-pY) > JUDGE_SQUARE ){  // 右下
            plane2.pressRight = true;
            plane2.pressDown = true;

            plane2.pressUp = false;
            plane2.pressLeft = false;
        }else{  // 右
            plane2.pressRight = true;

            plane2.pressLeft = false;
            plane2.pressDown = false;
            plane2.pressUp = false;
        }
    }else{  // 中间
        if ( (mouseY-pY) < -JUDGE_SQUARE ){  // 上
            plane2.pressUp = true;

            plane2.pressLeft = false;
            plane2.pressDown = false;
            plane2.pressRight = false;

        }else if( (mouseY-pY) > JUDGE_SQUARE ){  // 下
            plane2.pressDown = true;

            plane2.pressLeft = false;
            plane2.pressRight = false;
            plane2.pressUp = false;
        }else{  // 不动
            plane2.pressLeft = false;
            plane2.pressRight = false;
            plane2.pressUp = false;
            plane2.pressDown = false;
        }
    }
//    if(x <= 0){
//        x = 0;
//    }
//    if(x >= WIN_WIDTH - plane2.rect.width()){
//        x = WIN_WIDTH - plane2.rect.width();
//    }
//    if(y <= 0){
//        y = 0;
//    }
//    if(y >= WIN_HEIGHT - plane2.rect.height()){
//        y = WIN_HEIGHT - plane2.rect.height();
//    }

//    plane2.setPosition(plane2.planeX,plane.planeY);
}


void MainWindow::enemyAppear(){
    enemyInaterval ++;
    if( enemyInaterval < (ENEMY_INTERVAL_MAX + ENEMY_INTERVAL_MIN - enemyInatervalUpperLimit) ){
        return;  // 未到出场时间，退出
    }
    enemyInaterval = 0;
    for( int i = 0; i < ENEMY_NUM; i++ ){
        if( enemies[i].free ){  // 让第一个空闲的敌机登场
            enemies[i].free = false;
            enemies[i].x = rand() % (WIN_WIDTH - enemies[i].rect.width());
            enemies[i].y = -enemies[i].rect.height();
            break;
        }
    }
}

void MainWindow::destroyEnemy(){
    for(int i = 0; i < ENEMY_NUM; i++){  // 遍历所有非空闲的敌机
        if(enemies[i].free){
            continue;
        }

        for(int j = 0; j < BULLET_NUM; j++){  // 遍历所有非空闲的子弹
            if(plane.bullets[j].free){
                continue;
            }

            // 对于非空闲的子弹和敌机，如果矩形框相交，敌机被摧毁，移除子弹
            if( enemies[i].rect.intersects(plane.bullets[j].rect)){
                enemies[i].free = true;
                plane.bullets[j].free = true;
                score1 += 1;
                setScoreToLabel(1,score1);
                // 播放爆炸效果，使用第一个空闲的爆炸对象
                for(int k = 0; k < BOMB_NUM; k++){
                    if(bombs[k].free){
                        bombs[k].free = false;
                        bombs[k].x = enemies[i].x;  // 在被摧毁的敌机上释放爆炸效果
                        bombs[k].y = enemies[i].y;
                        break;
                    }
                }
            }
        }
        for( int j = 0; j < BULLET_NUM; j++ ){
            if(plane2.bullets[j].free){
                continue;
            }
            if( enemies[i].rect.intersects(plane2.bullets[j].rect)){
                enemies[i].free = true;
                plane2.bullets[j].free = true;
                score2 += 1;
                setScoreToLabel(2,score2);
                for(int k = 0; k < BOMB_NUM; k++){
                    if(bombs[k].free){
                        bombs[k].free = false;
                        bombs[k].x = enemies[i].x;  // 在被摧毁的敌机上释放爆炸效果
                        bombs[k].y = enemies[i].y;
                        break;
                    }
                }
            }
        }

        if( enemies[i].rect.intersects(plane.rect) ){  // 敌机与飞机相交，失败
            plane.destory();
        }
        if( enemies[i].rect.intersects(plane2.rect) ){
            plane2.destory();
        }

      }

    // 判断两机是否均被摧毁
    if (plane.destoried && plane2.destoried){
        readyModel();
        clear();
    }

}

void MainWindow::singleModel(){
    score1 = 0;
    setScoreToLabel(1,score1);
    labelScore2->setText("");
    labelDifficulty->setText("");
    plane.destoried = false;
    plane2.destoried = true;
    plane.plane.load(PLANE_PATH);
    sliderDifficulty->setEnabled(false);
    sliderDifficulty->setVisible(false);
    buttonSingle->setEnabled(false);
    buttonDouble->setEnabled(false);
    buttonSingle->setVisible(false);
    buttonDouble->setVisible(false);
    labelSettlement->setText("");

    QString scoreStr1= tr("Player 1 score:");
    scoreStr1.append(QString::number(score1));
    labelScore1->setText(scoreStr1);
}

void MainWindow::doubleModel(){
    score1 = 0;
    score2 = 0;
    setScoreToLabel(1,score1);
    setScoreToLabel(2,score2);
    labelDifficulty->setText("");
    plane.destoried = false;
    plane2.destoried = false;
    plane.plane.load(PLANE_PATH);
    plane2.plane.load(PLANE_PATH2);
    sliderDifficulty->setEnabled(false);
    sliderDifficulty->setVisible(false);
    buttonSingle->setEnabled(false);
    buttonDouble->setEnabled(false);
    buttonSingle->setVisible(false);
    buttonDouble->setVisible(false);
    labelSettlement->setText("");

    QString scoreStr1 = tr("Player 1 score:");
    QString scoreStr2 = tr("Player 2 score:");
    scoreStr1.append(QString::number(score1));
    scoreStr2.append(QString::number(score2));
    labelScore1->setText(scoreStr1);
    labelScore2->setText(scoreStr2);
}

void MainWindow::readyModel(){
    timer.stop();
    labelSettlement->setText("GAME OVER!\n");
    QFont font;
    font.setPixelSize(20);
    labelSettlement->setFont(font);
    labelSettlement->setStyleSheet("color:red;");
    labelDifficulty->setText(QString::number(enemyInatervalUpperLimit));
    sliderDifficulty->setEnabled(true);
    sliderDifficulty->setVisible(true);
    buttonSingle->setEnabled(true);
    buttonDouble->setEnabled(true);
    buttonSingle->setVisible(true);
    buttonDouble->setVisible(true);
}

void MainWindow::clear(){  // 清楚所有敌机和子弹
    for( int i = 0; i < ENEMY_NUM; i++ ){
        enemies[i].free = true;

    }
    for( int i = 0; i < BULLET_NUM; i++ ){
        plane.bullets[i].free = true;
    }
}

void MainWindow::setScoreToLabel(int label, int score){  // 更新计分板
    QString str1 = tr("Player 1 score:");
    QString str2 = tr("Player 2 score:");

    if(label == 1){
        str1.append(QString::number(score));
        labelScore1->setText(str1);
    }else if(label == 2){
        str2.append(QString::number(score));
        labelScore2->setText(str2);
    }
}

