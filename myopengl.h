
#pragma once
#ifdef _MSC_VER
#pragma once
#endif
#ifndef MYOPENGL_H
#define MYOPENGL_H



#include <QtWidgets/qopenglwidget.h>
#include<QtGui/qopenglfunctions_3_3_compatibility.h>
#include<QtGui/qopenglfunctions_4_3_compatibility.h>
#include <QtCore/qtimer.h>
#include <string>
#include <fstream>//使用ifstream打开文件流，成功则存在，失败则不存在;
#include <sstream>
#include <iostream>
#include <vector>
#include<QtGui/QKeyEvent>
#include<QtWidgets/qwidget.h>
#include"GimReader.h"

#include<glm/gtc/matrix_transform.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"displaylistPrimitive.h"
//#include <QOpenGLFunctions>
//#include <QOpenGLBuffer>
#include<opencsg.h>

#define SIZE 500

extern int name;
//bool               spin = true;
//float              rot = 0.0f;
//std::ostringstream fpsStream;

class myopengl : public QOpenGLWidget//, protected QOpenGLFunctions_3_3_Compatibility
{
    Q_OBJECT
public:
    myopengl(QWidget* parent = 0);

    ~myopengl();

public slots:


public://对3个纯虚函数的重定义
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);


    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void wheelEvent(QWheelEvent* event);
    void clearPrimtives();
    void draw(int EntityId, GLfloat rX, GLfloat rY, GLfloat rZ, GLfloat X1, GLfloat Y1, GLfloat Z1);
    void draw1(int EntityId, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3);
    void draw2(int EntityId, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat RX2, GLfloat RY2, GLfloat RZ2);
    void drawboolEntity();
    void drawboolEntity1();
    void drawboolEntity2();

    void Axis();
    void drawDifference1(int EntityId1, int EntityId2, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3);
    void drawDifference2(int EntityId1, int EntityId2, GLfloat rX, GLfloat rY, GLfloat rZ, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat RX2, GLfloat RY2, GLfloat RZ2);
    void drawIntersection1(int EntityId1, int EntityId2, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3);
    void drawIntersection2(int EntityId1, int EntityId2, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat RX2, GLfloat RY2, GLfloat RZ2);
   
    void list1();
    void list2();
    void Cylinder(GLfloat R, GLfloat H);
    void Cuboid(GLfloat L, GLfloat W, GLfloat H);
    void Sphere(GLfloat radius);
    void RotationalEllipsoid(GLfloat RL, GLfloat WR, GLfloat H);
    void Table(GLfloat TL1, GLfloat TL2, GLfloat LL1, GLfloat LL2, GLfloat H);
    void OffsetRectangularTable(GLfloat TL, GLfloat TW, GLfloat LL, GLfloat LW, GLfloat H, GLfloat XOFF, GLfloat YOFF);
    void TruncatedCone(GLfloat TR, GLfloat BR, GLfloat H);
    void EccentricTruncatedCone(GLfloat TR, GLfloat BR, GLfloat H, GLfloat TOPXOFF, GLfloat TOPYOFF);
    void Ring(GLfloat R, GLfloat DR, GLfloat Rad);
    void Rings(GLfloat R, GLfloat DR, GLdouble Rad, GLdouble theta);
    void RectangularRing(GLfloat DR, GLfloat R, GLfloat L, GLfloat  W);
    void EllipticRing(GLfloat DR, GLfloat L, GLfloat  W);
    void CircularGasket(GLfloat IR, GLfloat OR, GLfloat  H, GLfloat Rad);
    void TableGasket(GLfloat TR, GLfloat OR, GLfloat IR, GLfloat  H, GLfloat Rad);
    void SquareGasket(GLfloat L1, GLfloat W1, GLfloat L2, GLfloat  W2, GLfloat H, GLfloat CT, GLfloat  R, GLfloat CL);
    void StretchedBody(QString Normal, QString  Array, GLfloat L);
    void PorcelainBushing(GLfloat H, GLfloat R1, GLfloat R2, GLfloat  R3, GLfloat N1);
    void ConePorcelainBushing(GLfloat H, GLfloat BR, GLfloat TR, GLfloat  BR1, GLfloat BR2, GLfloat TR1, GLfloat TR2, GLfloat N);
    void Insulator(int N, GLfloat D, int N1, GLfloat  H1, GLfloat R1, GLfloat R2, GLfloat R);
    void VTypeInsulator(GLfloat X, GLfloat AD, int N1, GLfloat  H1, GLfloat R, GLfloat R1, GLfloat R2, GLfloat FL, GLfloat AL);
    void IrregularCuboid(GLfloat L, GLfloat W, GLfloat H, GLfloat CL);
    void TerminalBlock(GLfloat L, GLfloat W, GLfloat T, GLfloat CL, GLfloat CS, GLfloat RS, GLfloat R1, int CN, int RN, GLfloat BL, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ);
    void TerminalBlock1(GLfloat   L, GLfloat   W, GLfloat   T, GLfloat  CL, GLfloat  CS, GLfloat  RS, GLfloat   R1, int  CN, int  RN, GLfloat  BL, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat rX2, GLfloat rY2, GLfloat rZ2);
    void TerminalBlock2(GLfloat L, GLfloat W, GLfloat T, GLfloat CL, GLfloat CS, GLfloat RS, GLfloat R1, int CN, int RN, GLfloat BL, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat rX2, GLfloat rY2, GLfloat rZ2, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat rX1, GLfloat rY1, GLfloat rZ1);
    void Wire(QString  StartVector, QString  EndVector, QString  FitCoordArray, QString  StartCoord, QString  EndCoord, GLfloat D, GLfloat Sag);
    void Cable(QString InflectionCoordArray, QString  StartCoord, QString  EndCoord, GLfloat D, GLfloat IRArray);
    void PointsCylinder(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat D, GLfloat IRArray);
    void RectangularFixedPlate(GLfloat L, GLfloat W, GLfloat T, GLfloat CS, GLfloat RS, int CN, int RN, int MH, GLfloat D, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ);
    void CircularFixedPlate(GLfloat L, GLfloat W, GLfloat T, GLfloat CS, GLfloat N, int MH, GLfloat D, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ);
    void processHits(GLint hits, GLuint selectBuffer[]);
   
public://声明变量


    GLfloat speed;
    GLfloat yaw;
    GLfloat pitch;
    GLfloat ScalefX;
    GLfloat ScalefY;
    GLfloat ScalefZ;
    QPoint prepoint;
    GLfloat m_rtri;                                 //控制三角形的角度
    QTimer* pTimer;

    GLboolean ispressed;
    GLint select_point;

    GLint viewport[4];
    GLint hits;
    // GLuint selectBuffer[SIZE];
    using  uint = unsigned   int;
    static   const   int  selectBufferSize = 100;
    std::vector<uint> selectBuffer = std::vector<uint>(selectBufferSize);
    std::vector<OpenCSG::Primitive*> primitives;

    float cameraSpeed = 0.5f;
    glm::mat4 modelview;
    glm::mat4 projection;
    glm::vec3 camerapos = glm::vec3(45.0f, 10.0f, 50.0f);
    //glm::vec3 camerapos = glm::vec3(0.0f, 0.0f, 20.0f);
    glm::vec3 camerafront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f);

};
#endif 
