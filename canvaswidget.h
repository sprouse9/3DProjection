#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <iostream>

//#include "vertexdata.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    CanvasWidget(QWidget *parent = 0);
    ~CanvasWidget();

private:

    //float M[4][4];
    uint32_t imageWidth  = 320,
             imageHeight = 240;

    float Mproj[4][4] = {{0}};
    float worldToCamera[4][4] = {{0}};
    float angleOfView = 90;
    float near = 0.1;
    float far = 200;

    float theta = M_PI_4;
    float sint = qSin(theta);
    float cost = qCos(theta);

//    float cube[8][3] = {    // swaped C<->D, G<->H
//        { 1, -1, -4},
//        { 1, -1, -3},
//        { 1,  1, -3},
//        { 1,  1, -4},
//        {-1, -1, -4},
//        {-1, -1, -3},
//        {-1,  1, -3},
//        {-1,  1, -4}
//    };

//    float vertices[8][3] = {
//        {-100.0, -100.0,  100.0},
//        { 100.0, -100.0,  100.0},
//        { 100.0,  100.0,  100.0},
//        {-100.0,  100.0,  100.0},

//        {-100.0, -100.0,  -100.0},
//        { 100.0, -100.0,  -100.0},
//        { 100.0,  100.0,  -100.0},
//        {-100.0,  100.0,  -100.0}
//    };


    float vertices[8][3] = {    // swaped C<->D, G<->H
        { 1, -1, -4},
        { 1, -1, -3},
        { 1,  1, -3},
        { 1,  1, -4},
        {-1, -1, -4},
        {-1, -1, -3},
        {-1,  1, -3},
        {-1,  1, -4}
    };

    float RotM[3][3] = {
            { cost,  sint, 0 },
            { -sint, cost, 0 },
            {     0,    0, 1 }};

    //int indexBuffer[12][2] = {{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }};
    int indexBuffer[12][2] = {{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }};

    //void setProjectionMatrix();
    void multPointMatrix(const float *in, float *out, const float (&M)[4][4] );
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    //void rotateCube();
};

#endif // CANVASWIDGET_H
