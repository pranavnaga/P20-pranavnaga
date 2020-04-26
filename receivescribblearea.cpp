#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "receivescribblearea.h"

ReceiveScribbleArea::ReceiveScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    //the widget is tied to the top left even if user resizes
    setAttribute(Qt::WA_StaticContents);

    //default pen size, pen width and boolean value for scribbling is set when window first opens
    scribbling = false;
    myPenWidth = 5;
    myPenColor = Qt::black;
}

//fills the window is white (RGB is 255, 255, 255 for white)
//clear image fuction does not work
void ReceiveScribbleArea::clearImage() //NEEDS FIXING
{
    image.fill(qRgb(255, 255, 255));
    update();
}

//checks if the user input the left click of the mouse, then stores
//that input, boolean value for scribbling is now set true provided
//correct input is detected
void ReceiveScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

//when mouse if left clicked, drawline function happens,
//which draws a line from the last position to the current
void ReceiveScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

//variables are set, so that is user releases left click, drawing is stopped
void ReceiveScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

// QPainter provides functions to draw on the widget
// The QPaintEvent is sent to widgets that need to
// update themselves
void ReceiveScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Returns the rectangle that needs to be updated
    QRect dirtyRect = event->rect();

    // Draws the rectangle where the image needs to
    // be updated
    painter.drawImage(dirtyRect, image, dirtyRect);
}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
void ReceiveScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void ReceiveScribbleArea::drawLineTo(const QPoint &endPoint)
{
    //used to draw on the window
    QPainter painter(&image);

    //pen settings
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    //draw a line from the last registered point to the current
    painter.drawLine(lastPoint, endPoint);

    int rad = (myPenWidth / 2) + 2;

    //to update the scribbling space where we drew
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));

    //update the last position where we left off drawing
    lastPoint = endPoint;
}

//when the app is resized by user, create a new image using
//the changes made to the image
void ReceiveScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    //check if we need to redraw the image
    if (image->size() == newSize)
        return;

    //create a new image to display and fill it with white, when window is resized
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    //draw the image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}


