#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H
#include <QList>
#include <QMainWindow>

//defined a class for scribble area (drawing area) for receive window
class ReceiveScribbleArea;

//a class for the receive window
class ReceiveWindow : public QMainWindow
{

    Q_OBJECT

//function for receive window
public:
    ReceiveWindow();

// The events that can be triggered, meant to be in the menu section at the header
// of the desktop, but is not implemented correctly so doesnt work
private slots:
    void about(); //DOESNT WORK NEEDS FIXING

private:
    //menus created for the menu section at the header
    void createActions(); //DOESNT WORK NEEDS FIXING
    void createMenus();

    //what we are drawing on
    ReceiveScribbleArea *receivescribbleArea;

    //menu widgets
    QMenu *optionMenu; //NEED FIXING
    QMenu *helpMenu;

    //actions that are meant to appear as a sublist to the menu widgets
    QAction *clearScreenAct; //OPTION MENU--->CLEAR SCREEN ACTION
    QAction *aboutAct; //FILE MENU--->ABOUT DRAWING ACTION (INFORMATIVE)
    QAction *aboutQtAct; //FILE MENU--->ABOUT QT ACTION (INFORMATIVE)
    //THESE NEED FIXING
};

#endif
