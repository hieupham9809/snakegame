#ifndef SNAKE_H
#define SNAKE_H
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QTime>
#include <QVector>



class snake : public QWidget
{
public:
    snake(QWidget *parent = 0);
    const int ALL_DOTS = 900;
    const int B_WIDTH = 300;
    const int B_HEIDTH = 300;
    const int DELAY = 60;
    const int DOTS_SIZE = 10;
    const int DOTS_START = 3;
    const int RAND_POS = 29;

private:

   // int xValue[900];
    //int yValue[900];
    QVector<int> xValue;
    QVector<int> yValue;
    int timerID;
    int xFeed;
    int yFeed;
    int score = 0;

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);


private:
    bool leftDirection;
    bool rightDirection;
    bool upDirection;
    bool downDirection;
    bool inGame;

    void move();
    void draw();
    void check();
    void startGame();
    void randFeed();
    void gameOver(QPainter &);
    void drawScore(QPainter &);
};

#endif // SNAKE_H
