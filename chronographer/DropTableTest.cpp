#include <QApplication>

#include "Character.h"
#include "IntProperty.h"
#include "Session.h"
#include "Test.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Ui::TestUi test;
    QWidget* mainWidget = new QWidget();
    test.setupUi( mainWidget );

    Character bob("Bob");
    IntProperty prop("HP");

    Session session;

    QVariant var;
    var.setValue( (void*)prop.Instantiate( &session, &bob ) );

    test.tableWidget->model()->setData( test.tableWidget->model()->index(0, 0), var, Qt::UserRole );

    mainWidget->show();

    return app.exec();
}

