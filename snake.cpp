#include "snake.h"

snake::snake(QWidget *parent) :QWidget(parent)
{
    this->resize(B_WIDTH, B_HEIDTH);
    this->setWindowTitle("Snake Game");
    this->setStyleSheet("background-color:black;");


    startGame();
}
void snake::startGame(){
    //int dots = 3;
    inGame = true;
    xValue.append(150);
    yValue.append(150);
    xFeed = 180; yFeed = 150;

    rightDirection = true;
    leftDirection = false;
    upDirection = false;
    downDirection = false;

    for (int i = 1; i < DOTS_START; i++){
        xValue.append(xValue[i - 1] - DOTS_SIZE);
        yValue.append(yValue[i - 1]);
    }
    /*QPainter qp1(this);
    for (int i = 0; i < DOTS_START; i++){
        qp1.setBrush(QBrush("red"));
        qp1.drawRect(xValue[i] - DOTS_SIZE, yValue[i] - DOTS_SIZE,xValue[i], yValue[i] );
    }
*/
    draw();
    timerID = startTimer(DELAY);
}

void snake::keyPressEvent(QKeyEvent *e){
    int key = e->key();
    if (key == Qt::Key_Left && (!rightDirection)){
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }
     if (key == Qt::Key_Right && (!leftDirection)){
         rightDirection = true;
         upDirection = false;
         downDirection = false;
     }

     if (key == Qt::Key_Up && (!downDirection)){
         upDirection = true;
         rightDirection = false;
         leftDirection = false;
     }

     if (key == Qt::Key_Down && (!upDirection)){
         downDirection = true;
         rightDirection = false;
         leftDirection = false;
     }

}

void snake::move(){
    for (int i = xValue.size() - 1; i > 0; i--){
        xValue[i] = xValue[i - 1];
        yValue[i] = yValue[i - 1];
    }
    if (inGame && rightDirection){
        xValue[0] += DOTS_SIZE;
    }

    if (inGame && leftDirection){
        xValue[0] -= DOTS_SIZE;
    }

    if (inGame && upDirection){
         yValue[0] -= DOTS_SIZE;
    }

    if (inGame && downDirection){
        yValue[0] += DOTS_SIZE;
    }
}

void snake::check(){
    for (int i = 1; i < xValue.size() - 1; i++){
        if (xValue[i] == xValue[0] && yValue[i] == yValue[0])
            inGame = false;
    }
    
    if (xValue[0] < 0 || xValue[0] > B_WIDTH || yValue[0] < 0 || yValue[0] > B_HEIDTH)
        inGame = false;
    if (xValue[0] == xFeed && yValue[0] == yFeed){
        randFeed();
        score += 10;
        xValue.append(0); yValue.append(0);
    }
    if (inGame == false){
        killTimer(timerID);

    }
}

void snake::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);

    draw();

}

void snake::draw(){
    QPainter qp2(this);
    if(inGame){
        for (int i = 0; i < xValue.size() - 1; i++){
            qp2.setBrush(QBrush("red"));
            qp2.drawRect(xValue[i], yValue[i],DOTS_SIZE, DOTS_SIZE);
        }
        qp2.setBrush(QBrush("yellow"));
        qp2.drawRect(xFeed, yFeed, DOTS_SIZE, DOTS_SIZE);
        drawScore(qp2);
    }else {
        gameOver(qp2);
    }
}
void snake::randFeed(){
    QTime time = QTime::currentTime();
        qsrand((uint) time.msec());
        int r = qrand() % RAND_POS;
        xFeed = (r * DOTS_SIZE);
        r = qrand() % RAND_POS;
        yFeed = (r * DOTS_SIZE);
}
void snake::gameOver(QPainter &qp){

    QString message2;
    message2.QString::number(score);
   // QString message1 = "Game over" + message2;
        QFont font("Courier", 15, QFont::DemiBold);
        //qp.setPen(QPen(QBrush("white"), 1));

       // QFontMetrics fm(font);

      //  int textWidth = fm.width(message2);
       qp.setFont(font);
        int h = height();
        int w = width();

        qp.setPen(QPen(QBrush("white"), 1));
        qp.translate(QPoint(w/2, h/2));
        qp.drawText(50, 0, message2);
       // qp.drawText(150, 165, message2);
}
void snake::drawScore(QPainter &qp){
    QString message = QString::number(score);

        QFont font("Courier", 15, QFont::DemiBold);
        //QFontMetrics fm(font);

        //int textWidth = fm.width(message);
        qp.setFont(font);


        qp.setPen(QPen(QBrush("white"), 1));
        //qp.translate(QPoint(w/2, h/2));
        qp.drawText(10, 15, message);
}
void snake::timerEvent(QTimerEvent *e){
    Q_UNUSED(e);

            check();
            move();
            draw();
            repaint();
}
void snake::endvg();