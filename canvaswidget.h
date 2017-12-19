#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtMath>
#include <iostream>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    CanvasWidget(QWidget *parent = 0);
    ~CanvasWidget();

private:

    uint32_t imageWidth  = rect().width(),
             imageHeight = rect().height();

    float Mproj[4][4] = {{0}};
    //float worldToCamera[4][4] = {{0}};
    float worldToCamera[4][4] = {{ 0.95424, 0.20371, -0.218924, 0},
                                 {0, 0.732087, 0.681211, 0},
                                 {0.299041, -0.650039, 0.698587, 0},
                                 {-0.553677, -3.920548, -62.68137, 1}};

//    float worldToCamera[4][4] =
//                    { {  0.718762,  0.615033, -0.324214, 0 },
//                      { -0.393732,  0.744416,  0.539277, 0 },
//                      {  0.573024, -0.259959,  0.777216, 0 },
//                      {  0.526967,  1.254234, -2.532150, 1 } };

    float angleOfView = 45;
    float near = 0.1;
    float far = 100;

    float theta = M_PI_4;
    float sint = qSin(theta);
    float cost = qCos(theta);

//    float vertices[8][3] = {    // swaped C<->D, G<->H
//        { 10, -10, -80},
//        { 10, -10, 0},
//        { 10,  10, 0},
//        { 10,  10, -80},
//        {-10, -10, -80},
//        {-10, -10, 0},
//        {-10,  10, 0},
//        {-10,  10, -80}
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


//    float vertices[8][3] = {    // swaped C<->D, G<->H
//        { 1, -1, -4},
//        { 1, -1, -3},
//        { 1,  1, -3},
//        { 1,  1, -4},
//        {-1, -1, -4},
//        {-1, -1, -3},
//        {-1,  1, -3},
//        {-1,  1, -4}
//    };

    float RotM[3][3] = {
            { cost,  sint, 0 },
            { -sint, cost, 0 },
            {     0,    0, 1 }};

    //int indexBuffer[12][2] = {{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }};
    //int indexBuffer[12][2] = {{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 }, { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }};

    //void setProjectionMatrix();
    void multPointMatrix(const float *in, float *out, const float (&M)[4][4] );
    void rotateVertex(float *in);
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    //void rotateCube();
};

#endif // CANVASWIDGET_H
