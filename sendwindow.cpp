#include <QtWidgets>

#include "sendwindow.h"
#include "sendscribblearea.h"

// SendWindow
SendWindow::SendWindow()
{
    //scribble area widget for the send window
    sendscribbleArea = new SendScribbleArea;
    setCentralWidget(sendscribbleArea);

    // Create actions and menus
    createActions();
    createMenus();

    //sets title of window
    setWindowTitle(tr("Send Window"));

    //size of the send window
    resize(500, 500);
}

// Open an ABOUT dialog
void SendWindow::about() //NEEDS FIXING
{
    // Window title and text to display
    QMessageBox::about(this, tr("About Scribble"), //NEEDS FIXING
            tr("<p>The <b>Scribble</b> example is awesome</p>"));
}

// Define menu actions that call functions
void SendWindow::createActions()
{

    // Create clear screen action and tie to SendWindow::clearImage()
    clearScreenAct = new QAction(tr("&Clear Screen"), this); //NEEDS FIXING
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            sendscribbleArea, SLOT(clearImage()));

    // Create ABOUT action and tie to SendWindow::about()
    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    // Create about QT action and tie to SendWindow::aboutQt()
    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

//creates the menubar
void SendWindow::createMenus()
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

