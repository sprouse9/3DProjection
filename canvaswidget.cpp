#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{


}

CanvasWidget::~CanvasWidget()
{

}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    QRect r = rect().adjusted(10, 10, -10, -10);
    painter.drawRoundedRect(r, 20, 10);
    //painter.save();

    r.adjust(2, 2, -2, -2);
    painter.setViewport(r);
    r.moveTo(-r.width()/2, -r.height()/2);  // Set origin to center
    painter.setWindow(r);
    //drawChart(&painter, r);

    float scale = 10.0;
{
//    painter.drawLine( scale*cube[0][0]/-cube[0][2], scale*cube[0][1]/cube[0][2],    scale*cube[1][0]/-cube[1][2], scale*cube[1][1]/cube[1][2] );
//    painter.drawLine( scale*cube[1][0]/-cube[1][2], scale*cube[1][1]/cube[1][2],    scale*cube[2][0]/-cube[2][2], scale*cube[2][1]/cube[2][2] );
//    painter.drawLine( scale*cube[2][0]/-cube[2][2], scale*cube[2][1]/cube[2][2],    scale*cube[3][0]/-cube[3][2], scale*cube[3][1]/cube[3][2] );
//    painter.drawLine( scale*cube[3][0]/-cube[3][2], scale*cube[3][1]/cube[3][2],    scale*cube[0][0]/-cube[0][2], scale*cube[0][1]/cube[0][2] );

//    painter.drawLine( scale*cube[4][0]/-cube[4][2], scale*cube[4][1]/cube[4][2],    scale*cube[5][0]/-cube[5][2], scale*cube[5][1]/cube[5][2] );
//    painter.drawLine( scale*cube[5][0]/-cube[5][2], scale*cube[5][1]/cube[5][2],    scale*cube[6][0]/-cube[6][2], scale*cube[6][1]/cube[6][2] );
//    painter.drawLine( scale*cube[6][0]/-cube[6][2], scale*cube[6][1]/cube[6][2],    scale*cube[7][0]/-cube[7][2], scale*cube[7][1]/cube[7][2] );
//    painter.drawLine( scale*cube[7][0]/-cube[7][2], scale*cube[7][1]/cube[7][2],    scale*cube[4][0]/-cube[4][2], scale*cube[4][1]/cube[4][2] );

//    painter.drawLine( scale*cube[0][0]/-cube[0][2], scale*cube[0][1]/cube[0][2],    scale*cube[4][0]/-cube[4][2], scale*cube[4][1]/cube[4][2] );
//    painter.drawLine( scale*cube[1][0]/-cube[1][2], scale*cube[1][1]/cube[1][2],    scale*cube[5][0]/-cube[5][2], scale*cube[5][1]/cube[5][2] );
//    painter.drawLine( scale*cube[2][0]/-cube[2][2], scale*cube[2][1]/cube[2][2],    scale*cube[6][0]/-cube[6][2], scale*cube[6][1]/cube[6][2] );
//    painter.drawLine( scale*cube[3][0]/-cube[3][2], scale*cube[3][1]/cube[3][2],    scale*cube[7][0]/-cube[7][2], scale*cube[7][1]/cube[7][2] );
}
    // Loop thru the indexBuffer to build the cube
    for( int i = 0 ; i < 12 ; i++) {

        // draw a line from
        // indexBuffer[i][0] --> indexBuffer[i][1]
        int a = indexBuffer[i][0];  // from
        int b = indexBuffer[i][1];  // to

//        cube[a][0];     // x-coord
//        cube[a][1];     // y-coord
//        cube[a][2];     // z-coord

        painter.drawLine(   scale*cube[a][0] / -cube[a][2], scale*cube[a][1] / cube[a][2],
                            scale*cube[b][0] / -cube[b][2], scale*cube[b][1] / cube[b][2]
                        );
    }


    rotateCube();


    painter.drawText(10, 10, 100, 20, 0, QString::number(this->rect().center().x()) + ", " +
                                         QString::number(this->rect().center().y()) );
    //painter.restore();
}

void CanvasWidget::rotateCube()
{
    //float temp[8][3];
    float temp[3];

    // rotate the cube

    for(int i=0 ; i<8 ; i++) {
        temp[0] = cube[i][0];
        temp[1] = cube[i][1];
        temp[2] = cube[i][2];

        for(int j=0 ; j<3 ; j++) {
            for(int k=0 ; k<3 ; k++)
                cube[i][j] += temp[k] * RotM[k][j];
        }
    }

//    float RotM[3][3] = {
//            { cost,  sint, 0 },
//            { -sint, cost, 0 },
//            {     0,    0, 1 }};

}
