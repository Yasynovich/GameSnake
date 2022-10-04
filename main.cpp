#include <snake.h>
#include <QApplication>
#include <QIcon>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QIcon icon("C:/Users/NidLeo/projects/QT-Projects/Snake_project/Snake.png");
    app.setWindowIcon(icon);

    Game game;
    game.show();

    return app.exec();
}
