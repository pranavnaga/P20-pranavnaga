#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QList>
#include <QMainWindow>

//defined a class for scribble area (drawing area) for receive windowe
class SendScribbleArea;

class SendWindow : public QMainWindow
{
    Q_OBJECT

//function for receive window
public:
    SendWindow();

// The events that can be triggered, meant to be in the menu section at the header
// of the desktop, but is not implemented correctly so doesnt work
private slots:
    void about(); //DOESNT WORK NEEDS FIXING

private:
    //menus created for the menu section at the header
    void createActions();
    void createMenus();

    //what we are drawing on
    SendScribbleArea *sendscribbleArea;

    //menu widgets
    QMenu *optionMenu; //DOESNT WORK NEEDS FIXING
    QMenu *helpMenu;

    //actions that are meant to appear as a sublist to the menu widgets
    QAction *clearScreenAct; //OPTION MENU--->CLEAR SCREEN ACTION
    QAction *aboutAct; //FILE MENU--->ABOUT DRAWING ACTION (INFORMATIVE)
    QAction *aboutQtAct; //FILE MENU--->ABOUT QT ACTION (INFORMATIVE)
    //THESE NEED FIXING
};

#endif
