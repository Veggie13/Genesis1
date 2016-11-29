#include <QApplication>

#include "ChronoWindow.qoh"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget* mainWidget = new ChronoWindow();
    mainWidget->showMaximized();

    int result = app.exec();
    return result;
}
