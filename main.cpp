#include "sendwindow.h"
#include "receivewindow.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    //main application
    QApplication app(argc, argv);

    //send window declaration and show
    SendWindow swindow;
    swindow.show();

    //receive window declaration and show
    ReceiveWindow rwindow;
    rwindow.show();

    //display the 2 windows
    return app.exec();
}
