#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>

#include <cstdlib>
#include <ctime>
#include <exception>

#include "AmbienceApplication.h"
#include "AmbSplash.qoh"

#include "AmbMainWindow.qoh"


int main(int argc, char* argv[])
{
    std::srand( std::time(NULL) );

    AmbienceApplication app(argc, argv);

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

    AmbMainWindow* mainWindow = new AmbMainWindow(argc, argv);
#ifndef _DEBUG
    QDialog* splash = new AmbSplash();
    splash->exec();
#endif

    mainWindow->showMaximized();

    return app.exec();
}
