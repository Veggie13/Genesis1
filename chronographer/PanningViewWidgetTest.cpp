#include <QApplication>
#include <QColor>
#include <QPushButton>

#include "PanningViewWidget.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget* mainWidget = new QWidget();
    mainWidget->resize(1000, 300);
    PanningViewWidget* pan = new PanningViewWidget(mainWidget);
    pan->setGeometry( 10, 10, 800, 30 );
    pan->setAutoFillBackground(true);
    pan->setBackgroundRole( QPalette::WindowText );
    pan->SetViewContents( new QPushButton( "Heyoooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooddd" ) );
    mainWidget->show();

    int result = app.exec();
    return result;
}

