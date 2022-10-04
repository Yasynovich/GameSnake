#include "snake.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>

Game::Game()
{
    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT); //указываем размеры поля

    initGame();

}

void Game::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    if(m_inGame){
        check_apple();
        move();
        check_field();
    }

    this ->repaint();
}

void Game::keyPressEvent(QKeyEvent *e)
{
    int key = e -> key();
    if ( key == Qt::Key_Left && m_dir != Directions::right ){ m_dir = Directions::left;}
    if ( key == Qt::Key_Right && m_dir != Directions::left ){ m_dir = Directions::right;}
    if ( key == Qt::Key_Up && m_dir != Directions::down )   { m_dir = Directions::up;}
    if ( key == Qt::Key_Down && m_dir != Directions::up )   { m_dir = Directions::down;}

   /* switch (key){
    case Qt::Key_Left:
        qDebug() << "Key_Left";
        break;
    case Qt::Key_Right:
        qDebug() << "Key_Right";
        break;
    }*/
}

void Game::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    doDrawing();
}

void Game::doDrawing()
{
    QPainter qp(this);

    if(m_inGame){
        qp.setBrush(Qt::red);
        qp.drawRect(m_apple.x() * DOT_WIDTH ,m_apple.y() * DOT_HEIGHT, DOT_WIDTH , DOT_HEIGHT);

        for(int i = 0; i < m_dots.size(); ++i){
            if(i == 0){
                qp.setBrush(Qt::white);
                qp.drawRect(m_dots[i].x() * DOT_WIDTH ,m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH , DOT_HEIGHT);
            }else{
                qp.setBrush(Qt::green);
                qp.drawRect(m_dots[i].x() * DOT_WIDTH ,m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH , DOT_HEIGHT);
            }
        }

    }else{
       gameOver();
    }

}

void Game::localeApple()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    m_apple.rx() = qrand() % DOT_WIDTH;
    m_apple.ry() = qrand() % DOT_HEIGHT;
}

void Game::move()
{
    for(int i = m_dots.size()-1; i > 0 ; --i){
        m_dots[i] = m_dots[i - 1];
    }
    switch(m_dir){
        case left:  {m_dots[0].rx() -= 1;break;}
        case right: {m_dots[0].rx() += 1;break;}
        case up:    {m_dots[0].ry() -= 1;break;}
        case down:  {m_dots[0].ry() += 1;break;}
    }

}

void Game::check_field()
{
    if(m_dots.size() > 4){
        for(int i = 1; i < m_dots.size(); ++i){
            if(m_dots[0] == m_dots[i]){
               m_inGame = false;
            }
        }
    }

    if(m_dots[0].x() >= FIELD_WIDTH) { m_inGame = false;}
    if(m_dots[0].x() < 0)            { m_inGame = false;}
    if(m_dots[0].y() >= FIELD_HEIGHT){ m_inGame = false;}
    if(m_dots[0].y() < 0)            { m_inGame = false;}

    if(!m_inGame){
        killTimer(m_timerId);
    }

}

void Game::gameOver()
{
    QMessageBox msgb;
    msgb.setText("Game Over");
    msgb.exec();

    initGame();

}

void Game::check_apple()
{
    if (m_apple == m_dots[0]){
        m_dots.push_back(QPoint(0,0));
        localeApple();
    }

}

void Game::initGame(){
    m_inGame = true;
    m_dir = right;

    m_dots.resize(3); //начальная длина змейки

    for(int i= 0; i < m_dots.size(); ++i){   //начальное положение
        m_dots[i].rx() = m_dots.size() - i - 1;
        m_dots[i].ry() = 0;
    }

    localeApple();

    m_timerId = startTimer(DELAY);
}

