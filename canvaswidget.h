#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <QThread>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    CanvasWidget(QWidget *parent = 0);
    ~CanvasWidget();

private:

    float theta = M_PI_4;
    float sint = qSin(theta);
    float cost = qCos(theta);

    //float *cube;

    // create matrix
    float cube[8][3] = {
        {-100.0, -100.0, -10.0},
        { 100.0, -100.0, -10.0},
        { 100.0,  100.0, -10.0},
        {-100.0,  100.0, -10.0},

        {-100.0, -100.0, -210.0},
        { 100.0, -100.0, -210.0},
        { 100.0,  100.0, -210.0},
        {-100.0,  100.0, -210.0}
    };

    float RotM[3][3] = {
            { cost,  sint, 0 },
            { -sint, cost, 0 },
            {     0,    0, 1 }};

    int indexBuffer[12][2] = {{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }};

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void rotateCube();
};

#endif // CANVASWIDGET_H
