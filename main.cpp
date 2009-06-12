#include <QApplication>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>

#include <cstdlib>
#include <ctime>
#include <exception>

#include "AmbSplash.qoh"

#include "AmbMainWindow.qoh"


int main(int argc, char* argv[])
{
    std::srand( std::time(NULL) );

    QApplication app(argc, argv);

    if (argc > 2)
    {
        QMessageBox::critical(NULL, "Invalid parameters.", "Invalid parameters given.");
        return 1;
    }
    else if (argc > 1 && !QFileInfo(QString(argv[1])).isFile())
    {
        QMessageBox::critical(NULL, "Invalid filename.", "Invalid filename given.");
        return 1;
    }

    QMainWindow* mainWindow = new AmbMainWindow(argc, argv);
    QDialog* splash = new AmbSplash();
    splash->exec();
    mainWindow->showMaximized();

    try
    {
        return app.exec();
    }
    catch (std::exception e)
    {
        printf("Exception: %s\n", e.what());
    }
    catch (...)
    {
        printf("Exception occurred\n");
    }

    return 0;
}
