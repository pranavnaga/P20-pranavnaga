#include <QtWidgets>

#include "receivewindow.h"
#include "receivescribblearea.h"

//ReceiveWindow
ReceiveWindow::ReceiveWindow()
{
    //makes the scribbling area widget on the window
    receivescribbleArea = new ReceiveScribbleArea;
    setCentralWidget(receivescribbleArea);

    //creates actions and menus
    createActions();
    createMenus();

    //sets window title
    setWindowTitle(tr("Receive Window"));

    //size of the window
    resize(500, 500);
}

//Open an ABOUT dialogue
void ReceiveWindow::about() //NEEDS FIXING
{
    //window title and text to display on the ABOUT dialogue
    QMessageBox::about(this, tr("About Scribble"), //NEEDS FIXING
            tr("<p>The <b>Scribble</b> example is awesome</p>"));
}

// Define menu actions that call functions
void ReceiveWindow::createActions()
{

    // Create clear screen action and tie to ReceiveWindow::clearImage()
    clearScreenAct = new QAction(tr("&Clear Screen"), this); //NEEDS FIXING
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            receivescribbleArea, SLOT(clearImage()));

    // Create ABOUT action and tie to ReceiveWindow::about()
    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    // Create about QT action and tie to ReceiveWindow::aboutQt()
    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

//creates the menubar
void ReceiveWindow::createMenus() //NEEDS FIXING
{

    // Attach all actions to Options
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    // Attach all actions to Help
    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

}

