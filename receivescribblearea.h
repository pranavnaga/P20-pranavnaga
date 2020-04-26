#ifndef RECEIVESCRIBBLEAREA_H
#define RECEIVESCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

//defined a class for scribble area (drawing area) for receive window
class ReceiveScribbleArea : public QWidget
{

    Q_OBJECT

public:
    ReceiveScribbleArea(QWidget *parent = 0);

public slots:

    // a clear image function that doesnt work
    void clearImage(); //DOESNT WORK NEEDS FIXING

//move press, move, and release event for drawing lines
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    // updates the scribble area where we are painting
    void paintEvent(QPaintEvent *event) override;

    //when the window is resized, it enlarges the drawing area as well
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);

    //made true or false depending on if the user is drawing or not
    bool scribbling;

    //for pen colour and width, set as default so user cannot change it
    int myPenWidth;
    QColor myPenColor;

    // stores the image being drawn
    QImage image;

    // stores the location at the current mouse event
    QPoint lastPoint;
};

#endif
