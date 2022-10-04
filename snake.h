#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QPainter>


class Game : public QWidget{

public:
    Game();

protected:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void paintEvent(QPaintEvent* event) override;

private:

    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;   // длина и ширина клетки
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20; //количество клеток
    static const int DELAY = 120;

    void doDrawing();
    void localeApple();
    void move();
    void check_field();
    void gameOver();
    void check_apple();

    int m_timerId;

    QPoint m_apple; //информация о яблоке

    enum Directions {
        left, right, up, down  //направления змейки
    };

    Directions m_dir;

    bool m_inGame;
    QVector<QPoint> m_dots; //точки змейки


    void initGame();
};
#endif // SNAKE_H
