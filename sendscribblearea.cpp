#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "sendscribblearea.h"

SendScribbleArea::SendScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    //ties the window to the top left even if resized by user
    setAttribute(Qt::WA_StaticContents);

    //defualt values for when window opens
    scribbling = false;
    myPenWidth = 5;
    myPenColor = Qt::black;
}

//colours window with RGB colour white
void SendScribbleArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    update();
}

//mouse event for when the user input is left click
void SendScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

//when mouse is left clicked and moved, drawing event occurs
void SendScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

//if left click is released by user, drawing is stopped, and variables are set for that
void SendScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

//updates QPaintEvent
void SendScribbleArea::paintEvent(QPaintEvent *event)
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
void SendScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void SendScribbleArea::drawLineTo(const QPoint &endPoint)
{
    //to draw on the widget
    QPainter painter(&image);

    //pen settings
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    //draws a line from the last registered point to the current
    painter.drawLine(lastPoint, endPoint);

    int rad = (myPenWidth / 2) + 2;

    // Call to update the rectangular space where we drew
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));

    // Update the last position where we left off drawing
    lastPoint = endPoint;
}

// When the app is resized create a new image using
// the changes made to the image
void SendScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    // Check if we need to redraw the image
    if (image->size() == newSize)
        return;

    // Create a new image to display and fill it with white
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    // Draw the image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}




