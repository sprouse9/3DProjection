#include "canvaswidget.h"
#include "vertexdata.h"

using namespace std;

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
{
//    worldToCamera[3][1] = -10;
//    worldToCamera[3][2] = -20;

    // set the basic projection matrix
    float scale = 1 / tan(angleOfView * 0.5 * M_PI / 180);
    Mproj[0][0] = scale;        // scale the x coordinates of the projected point
    Mproj[1][1] = scale;        // scale the y coordinates of the projected point
    Mproj[2][2] = -far / (far - near);          // used to remap z to [0,1]
    Mproj[3][2] = -far * near / (far - near);   // used to remap z [0,1]
    Mproj[2][3] = -1; // set w = -z
    Mproj[3][3] = 0;
}

CanvasWidget::~CanvasWidget()
{
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);

//    QRect r = rect().adjusted(10, 10, -10, -10);
//    painter.drawRoundedRect(r, 20, 10);
    //painter.save();

//    r.adjust(2, 2, -2, -2);
//    painter.setViewport(r);
//    r.moveTo(-r.width()/2, -r.height()/2);  // Set origin to center
//    painter.setWindow(r);
    //drawChart(&painter, r);

    float scale = 1;

    //int temp_cube[numVertices][2] = {{0}};
    //int numVertices = 8;

    unsigned char *buffer = new unsigned char[imageWidth * imageHeight];
    memset(buffer, 0x0, imageWidth * imageHeight);

    for (uint32_t i = 0; i < numVertices; ++i) {
        //cout << i<< ": (" << vertices[i][0] << ", " << vertices[i][1] <<", " << vertices[i][2] << ") ==> ";

        float vertCamera[3] = {0}, projectedVert[3] = {0};

        multPointMatrix( vertices[i], vertCamera, worldToCamera );
        multPointMatrix( vertCamera, projectedVert, Mproj );

        if (projectedVert[0] < -1 || projectedVert[0] > 1 || projectedVert[1] < -1 || projectedVert[1] > 1) continue;
        // convert to raster space and mark the position of the vertex in the image with a simple dot
        uint32_t x = std::min(imageWidth - 1, (uint32_t)((projectedVert[0] + 1) * 0.5 * imageWidth));
        uint32_t y = std::min(imageHeight - 1,(uint32_t)((1 - (projectedVert[1] + 1) * 0.5) * imageHeight));
        buffer[y * imageWidth + x] = 255;

//        temp_cube[i][0] = x;
//        temp_cube[i][1] = y;

        //cout << "(" << temp_cube[i][0] << ", " << temp_cube[i][1] << ")" << endl;

        painter.drawPoint(scale*x, scale*y);
        //rotateVertex( vertices[i] );

    }



    // Loop thru the indexBuffer to build the cube
    //for( int i = 0 ; i < 12 ; i++) {

        // draw a line from  indexBuffer[i][0] --> indexBuffer[i][1]
      //  int a = indexBuffer[i][0];  // from
       // int b = indexBuffer[i][1];  // to

        //painter.drawLine( scale*temp_cube[a][0], scale*temp_cube[a][1],
         //                   scale*temp_cube[b][0], scale*temp_cube[b][1]);
    //}

    //rotateCube();
    //painter.drawLine( 0,0, 100, -100);

    painter.drawText(10, 10, 100, 20, 0, QString::number(this->rect().width()) + ", " +
                                         QString::number(this->rect().height()) );
    //painter.restore();

}

//void CanvasWidget::rotateCube(float &temp_cube)
/*{
    float temp[3];

    // rotate the cube
    for(int i=0 ; i<8 ; i++) {
        temp[0] = temp_cube[i][0];
        temp[1] = temp_cube[i][1];
        temp[2] = temp_cube[i][2];

        for(int j=0 ; j<3 ; j++) {
            for(int k=0 ; k<3 ; k++)
                temp_cube[i][j] += temp[k] * RotM[k][j];
        }
    }*/

//    float RotM[3][3] = {
//            { cost,  sint, 0 },
//            { -sint, cost, 0 },
//            {     0,    0, 1 }};
//}

void CanvasWidget::rotateVertex( float *in )
{
    float temp[3];

    // rotate the vertice

        temp[0] = *(in+0);
        temp[1] = *(in+1);
        temp[2] = *(in+2);

        for(int j=0 ; j<3 ; j++) {
            for(int k=0 ; k<3 ; k++)
                *(in+j) += temp[k] * RotM[k][j];
        }

//    float RotM[3][3] = {
//            { cost,  sint, 0 },
//            { -sint, cost, 0 },
//            {     0,    0, 1 }};
}


//void CanvasWidget::setProjectionMatrix(const float &angleOfView, const float &near, const float &far)
//void CanvasWidget::setProjectionMatrix()
//{
//    // set the basic projection matrix
//    float scale = 1 / tan(angleOfView * 0.5 * M_PI / 180);
//    Mproj[0][0] = scale;        // scale the x coordinates of the projected point
//    Mproj[1][1] = scale;        // scale the y coordinates of the projected point
//    Mproj[2][2] = -far / (far - near);          // used to reMprojap z to [0,1]
//    Mproj[3][2] = -far * near / (far - near);   // used to reMprojap z [0,1]
//    Mproj[2][3] = -1; // set w = -z
//    Mproj[3][3] = 0;
//}

void CanvasWidget::multPointMatrix(const float *in, float *out, const float (&M)[4][4]) {
    // out = in * M;

//    *(out+0) = 9; *(out+1) = 29; out[2] = 59;

    *(out+0) = *(in+0) * M[0][0] + *(in+1) * M[1][0] + *(in+2) * M[2][0] + M[3][0];
    *(out+1) = *(in+0) * M[0][1] + *(in+1) * M[1][1] + *(in+2) * M[2][1] + M[3][1];
    *(out+2) = *(in+0) * M[0][2] + *(in+1) * M[1][2] + *(in+2) * M[2][2] + M[3][2];

    float w  = *(in+0) * M[0][3] + *(in+1) * M[1][3] + *(in+2) * M[2][3] + M[3][3];

    // normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
    if (w != 1) {
        *(out+0) /= w;
        *(out+1) /= w;
        *(out+2) /= w;
    }

    //cout << "out[]=" << "{" << *(out+0) << ", " << *(out+1) << endl;
}
