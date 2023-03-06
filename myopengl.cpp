#ifdef WIN32  
#pragma execution_character_set("utf-8")
//#pragma comment(lib,"glew32sd.lib") 
#endif

#include<Windows.h>
#include<GL/glew.h>
#include<GL/glut.h>

//#include <stdlib.h>
#include "myopengl.h"
#include<QtGui/qevent.h>
#include<cmath>
#include <QtCore/QDebug.h>
#include <QtCore/qtimer.h>
#include<ctime>
#include <string.h>
#include "ModFile.h"
#include<cmath>
#include<opencsg.h>
#include <iostream>
#include <QtGui/QVector3D>
#include"Qt8.h"
using namespace std;
#define  PI 3.1415926
#define e 10

int name;
myopengl::myopengl(QWidget* parent) :QOpenGLWidget(parent)
{

    setFocusPolicy(Qt::StrongFocus);//键盘焦点，鼠标单击触发键盘事件

    pTimer = new QTimer(this); //创建一个定时器
    //将定时器的计时信号与updateGL()绑定
    connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
    pTimer->start(10);//以10ms为一个计时周期



     //变量初始化
    speed = 1.0f;
    yaw = -90.0f;
    pitch = 0.0f;
    m_rtri = 4.0f;
    hits = 0;
    ispressed = false;
    select_point = 0;
    ScalefX = 0.00095;
    ScalefY = 0.00095;
    ScalefZ = 0.00095;
    //ScalefX = 0.001;
    //ScalefY = 0.001;
    //ScalefZ = 0.001;

}
myopengl::~myopengl()
{

}
//设置OpenGL渲染环境，定义显示列表等。该函数只在第一次调用resizeGL()或paintGL()前被自动调用一次。
void myopengl::initializeGL()
{

    glShadeModel(GL_FLAT);//设置阴影平滑模式 
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);//改变窗口的背景颜色 
    int err = glewInit();
    if (GLEW_OK != err) {
        // problem: glewInit failed, something is seriously wrong
        std::cerr << "GLEW Error: " << glewGetErrorString(err) << std::endl;

    }
    //glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);






    //glClearDepth(1.0);//设置深度缓存 
   //glEnable(GL_DEPTH_TEST);
   //glDepthFunc(GL_EQUAL);
   // QSurfaceFormat format;

  //
  // glDepthFunc(GL_LESS);//设置深度测试类型 
    //glShadeModel(GL_SMOOTH);
   //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//进行透视校正 





}
//设置OpenGL的视口、投影等。每次部件改变大小时都会自动调用该函数。
void myopengl::resizeGL(int w, int h)
{
    viewport[0] = 0;
    viewport[1] = 0;
    viewport[2] = w;
    viewport[3] = h;

    glViewport(0, 0, w, h);

}
//渲染OpenGL场景。每当部件需要更新时都会调用该函数。
void myopengl::paintGL()
{
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0, 2.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //glGetIntegerv(GL_VIEWPORT, viewport);//获取当前视口坐标参数
    int renderMode;
    glGetIntegerv(GL_RENDER_MODE, &renderMode);

    if (renderMode != GL_SELECT) {

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat x = GLfloat(viewport[2]) / GLfloat(viewport[3]);
        projection = glm::perspective(45.0f, x, 0.1f, 100.0f);
        glLoadMatrixf(value_ptr(projection));


    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    modelview = glm::lookAt(camerapos, camerapos + camerafront, cameraup);
    glLoadMatrixf(glm::value_ptr(modelview));


    //---------------------绘图代码------------------------------------------------------

    glRotatef(m_rtri, 0.0, 1.0, 0.0);
    glPushMatrix();

    glScalef(ScalefX, ScalefY, ScalefZ);
   // Axis();
   
    //list1();
    //list2();
   
    
    //没选中
    //if (hits == 0) {
        // 只画简单图
        //if (flag1 == 1) {
            list1();
   
    glDisable(GL_POLYGON_OFFSET_FILL);


    glPopMatrix();



}

void myopengl::keyPressEvent(QKeyEvent* event)
{

    if (event->key() == Qt::Key_A)
    {
        camerapos -= glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeed;

    }
    else if (event->key() == Qt::Key_D)
    {
        camerapos += glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeed;

    }
    else if (event->key() == Qt::Key_W)
    {
        camerapos += cameraSpeed * cameraup;

    }
    else if (event->key() == Qt::Key_S)
    {
        camerapos -= cameraSpeed * cameraup;

    }
    else if (event->key() == Qt::Key_Q)
    {
        m_rtri += 5;
    }
    else if (event->key() == Qt::Key_Left) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        yaw -= 1;
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camerafront = glm::normalize(front);
    }
    else if (event->key() == Qt::Key_Right) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        yaw += 1;
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camerafront = glm::normalize(front);

    }
    else if (event->key() == Qt::Key_Up) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        pitch -= 1;
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camerafront = glm::normalize(front);
    }
    else if (event->key() == Qt::Key_Down) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        pitch += 1;
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camerafront = glm::normalize(front);
    }
    update();
}
void myopengl::wheelEvent(QWheelEvent* event)
{
    if (event->delta() > 0) {
        camerapos += cameraSpeed * camerafront;
    }
    else {
        camerapos -= cameraSpeed * camerafront;
    }

    update();
}
void myopengl::clearPrimtives()
{
    for (std::vector<OpenCSG::Primitive*>::const_iterator i = primitives.begin(); i != primitives.end(); ++i) {
        OpenCSG::DisplayListPrimitive* p =
            static_cast<OpenCSG::DisplayListPrimitive*>(*i);
        glDeleteLists(1, p->getDisplayListId());
        delete p;
    }

    primitives.clear();
}
void myopengl::drawboolEntity()
{
    glPushMatrix();
    for (int i = 0; i < gimModFileList.size(); i++) {
        ModFile modFile = gimModFileList[i];
        if (modFile.gettransformMatrix1().isEmpty())
        {
            QString  vs2 = modFile.gettransformMatrix2();
            QStringList vs2splits = vs2.split(",");
            float mat2[16];
            for (int i = 0; i < 16; i++)
            {
                mat2[i] = (vs2splits[i]).toFloat();
            }
            //获取旋转角度
            float RX3 = (atan2(mat2[9], mat2[10])) * PI / 180;
            float RY3 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
            float RZ3 = (atan2(mat2[4], mat2[0])) * PI / 180;
            ////获取坐标
            float X3 = mat2[12];
            float Y3 = mat2[13];
            float Z3 = mat2[14];
            for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
                if (!simpleEntity.getGraphicElement().isNull()) {
                    if (simpleEntity.getVisible() == ("true")) {
                        if (simpleEntity.getGraphicElement().nodeName() == ("TerminalBlock")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高
                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();
                            float T = (n.attribute("T")).toFloat();
                            float CL = (n.attribute("CL")).toFloat();
                            float CS = (n.attribute("CS")).toFloat();
                            float RS = (n.attribute("RS")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float CN = (n.attribute("CN")).toFloat();
                            float RN = (n.attribute("RN")).toFloat();
                            float BL = (n.attribute("BL")).toFloat();
                            //                  
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glColor4f(R, G, B, A);
                            TerminalBlock1(L, W, T, CL, CS, RS, R1, CN, RN, BL, X, Y, Z, rX, rY, rZ, X3, Y3, Z3, RX3, RY3, RZ3);
                            glPopMatrix();
                        }
                        //if (simpleEntity.getGraphicElement().nodeName() == ("Rectangular fixed plate")) {
                        //    QDomElement n = simpleEntity.getGraphicElement().toElement();
                        //    QString  vs = simpleEntity.getTransformMatrix();
                        //    QStringList splits = vs.split(",");
                        //    float mat[16];
                        //    for (int i = 0; i < 16; i++)
                        //    {
                        //        mat[i] = (splits[i]).toFloat();
                        //    }
                        //    //获取旋转角度
                        //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
                        //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                        //    //获取坐标
                        //    float X = mat[12];
                        //    float Y = mat[13];
                        //    float Z = mat[14];
                        //    //获取颜色
                        //    float R = (float)simpleEntity.getR() / 255;
                        //    float G = (float)simpleEntity.getG() / 255;
                        //    float B = (float)simpleEntity.getB() / 255;
                        //    float A = (float)simpleEntity.getA() / 255;
                        //    //获取长宽高
                        //    float L = (n.attribute("L")).toFloat();
                        //    float W = (n.attribute("W")).toFloat();
                        //    float T = (n.attribute("T")).toFloat();
                        //    float CS = (n.attribute("CS")).toFloat();
                        //    float RS = (n.attribute("RS")).toFloat();
                        //    float CN = (n.attribute("CN")).toFloat();
                        //    float RN = (n.attribute("RN")).toFloat();
                        //    float MH = (n.attribute("MH")).toFloat();
                        //    float D = (n.attribute("D")).toFloat();
                        //    //
                        //    glPushMatrix();
                        //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        //    glColor4f(R, G, B, A);
                        //    RectangularFixedPlate(L, W, T, CS, RS, CN, RN, MH, D, X, Y, Z, rX, rY, rZ);
                        //    glPopMatrix();
                        //}
                        //if (simpleEntity.getGraphicElement().nodeName() == ("Circular fixed plate")) {
                        //    QDomElement n = simpleEntity.getGraphicElement().toElement();
                        //    QString  vs = simpleEntity.getTransformMatrix();
                        //    QStringList splits = vs.split(",");
                        //    float mat[16];
                        //    for (int i = 0; i < 16; i++)
                        //    {
                        //        mat[i] = (splits[i]).toFloat();
                        //    }
                        //    ////获取旋转角度
                        //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
                        //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                        //    //获取坐标
                        //    float X = mat[12];
                        //    float Y = mat[13];
                        //    float Z = mat[14];
                        //    //获取颜色
                        //    float R = (float)simpleEntity.getR() / 255;
                        //    float G = (float)simpleEntity.getG() / 255;
                        //    float B = (float)simpleEntity.getB() / 255;
                        //    float A = (float)simpleEntity.getA() / 255;
                        //    //获取长宽高
                        //    float L = (n.attribute("L")).toFloat();
                        //    float W = (n.attribute("W")).toFloat();
                        //    float T = (n.attribute("T")).toFloat();
                        //    float CS = (n.attribute("CS")).toFloat();
                        //    float N = (n.attribute("N")).toFloat();
                        //    float MH = (n.attribute("MH")).toFloat();
                        //    float D = (n.attribute("D")).toFloat();
                        //    //
                        //    glPushMatrix();
                        //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        //    glColor4f(R, G, B, A);
                        //    CircularFixedPlate(L, W, T, CS, N, MH, D, X, Y, Z, rX, rY, rZ);
                        //    glPopMatrix();
                        //}
                    }
                }
                //for (BoolEntity boolEntity : modFile.getBoolEntities()) {
            //      if (!boolEntity.getBoolType().isNull()) {
            //          if (boolEntity.getVisible() == ("true")) {
            //              if (boolEntity.getBoolType() == ("Difference")) {
            //                  QString  vs = boolEntity.getTransformMatrix();
            //                  QStringList splits = vs.split(",");
            //                  float mat[16];
            //                  for (int i = 0; i < 16; i++)
            //                  {
            //                      mat[i] = (splits[i]).toFloat();
            //                  }
            //                  ////获取旋转角度
            //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
            //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
            //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
            //                  //获取坐标
            //                  float X1 = mat[12];
            //                  float Y1 = mat[13];
            //                  float Z1 = mat[14];
            //                  //获取颜色
            //                  float R = (float)boolEntity.getR() / 255;
            //                  float G = (float)boolEntity.getG() / 255;
            //                  float B = (float)boolEntity.getB() / 255;
            //                  float A = (float)boolEntity.getA() / 255;
            //                  int  EntityId1 = boolEntity.getBoolEntityId1();
            //                  int  EntityId2 = boolEntity.getBoolEntityId2();
            //                  glPushMatrix();
            //                  //glTranslatef(X1, Z1, Y1);
            //                  glColor4f(R, G, B, A);
            //                  drawDifference(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
            //                  glPopMatrix();
            //              }
            //              if (boolEntity.getBoolType() == ("Union")) {
            //                  QString  vs = boolEntity.getTransformMatrix();
            //                  QStringList splits = vs.split(",");
            //                  float mat[16];
            //                  for (int i = 0; i < 16; i++)
            //                  {
            //                      mat[i] = (splits[i]).toFloat();
            //                  }
            //                  //获取旋转角度
            //                  float rX = (atan2(mat[9], mat[10])) * PI / 180;
            //                  float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
            //                  float rZ = (atan2(mat[4], mat[0])) * PI / 180;
            //                  //获取坐标
            //                  float X1 = mat[12];
            //                  float Y1 = mat[13];
            //                  float Z1 = mat[14];
            //                  //获取颜色
            //                  float R = (float)boolEntity.getR() / 255;
            //                  float G = (float)boolEntity.getG() / 255;
            //                  float B = (float)boolEntity.getB() / 255;
            //                  float A = (float)boolEntity.getA() / 255;
            //                  int  EntityId1 = boolEntity.getBoolEntityId1();
            //                  int  EntityId2 = boolEntity.getBoolEntityId2();
            //                  glPushMatrix();
            //                  glColor4f(R, G, B, A);
            //                  draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
            //                  draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
            //                  glPopMatrix();
            //              }
            //              if (boolEntity.getBoolType() == ("Intersection")) {
            //                  QString  vs = boolEntity.getTransformMatrix();
            //                  QStringList splits = vs.split(",");
            //                  float mat[16];
            //                  for (int i = 0; i < 16; i++)
            //                  {
            //                      mat[i] = (splits[i]).toFloat();
            //                  }
            //                  ////获取旋转角度
            //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
            //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
            //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
            //                  //获取坐标
            //                  float X1 = mat[12];
            //                  float Y1 = mat[13];
            //                  float Z1 = mat[14];
            //                  //获取颜色
            //                  float R = (float)boolEntity.getR() / 255;
            //                  float G = (float)boolEntity.getG() / 255;
            //                  float B = (float)boolEntity.getB() / 255;
            //                  float A = (float)boolEntity.getA() / 255;
            //                  int  EntityId1 = boolEntity.getBoolEntityId1();
            //                  int  EntityId2 = boolEntity.getBoolEntityId2();
            //                  glPushMatrix();
            //                  glColor4f(R, G, B, A);
            //                  drawIntersection(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
            //                  glPopMatrix();
            //              }
            //          }
            //      }
            //  }
               //glPopMatrix();
        //}
                //glPopMatrix();
            }
            for (BoolEntity boolEntity : modFile.getBoolEntities()) {
                if (!boolEntity.getBoolType().isNull()) {
                    if (boolEntity.getVisible() == ("true")) {
                        if (boolEntity.getBoolType() == ("Difference")) {
                            QString  vs = boolEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X1 = mat[12];
                            float Y1 = mat[13];
                            float Z1 = mat[14];
                            //获取颜色
                            float R = (float)boolEntity.getR() / 255;
                            float G = (float)boolEntity.getG() / 255;
                            float B = (float)boolEntity.getB() / 255;
                            float A = (float)boolEntity.getA() / 255;
                            int  EntityId1 = boolEntity.getBoolEntityId1();
                            int  EntityId2 = boolEntity.getBoolEntityId2();
                            glPushMatrix();
                            glColor4f(R, G, B, A);
                            drawDifference1(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1,X3,Y3,Z3,RX3,RY3,RZ3);

                            glPopMatrix();
                        }
                        if (boolEntity.getBoolType() == ("Union")) {
                            QString  vs = boolEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X1 = mat[12];
                            float Y1 = mat[13];
                            float Z1 = mat[14];
                            //获取颜色
                            float R = (float)boolEntity.getR() / 255;
                            float G = (float)boolEntity.getG() / 255;
                            float B = (float)boolEntity.getB() / 255;
                            float A = (float)boolEntity.getA() / 255;
                            int  EntityId1 = boolEntity.getBoolEntityId1();
                            int  EntityId2 = boolEntity.getBoolEntityId2();
                            //画第一个图形
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glColor4f(R, G, B, A);
                            draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
                            glPopMatrix();
                            //画第二个图形
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glColor4f(R, G, B, A);
                            draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
                            glPopMatrix();
                        }
                        if (boolEntity.getBoolType() == ("Intersection")) {
                            QString  vs = boolEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X1 = mat[12];
                            float Y1 = mat[13];
                            float Z1 = mat[14];
                            //获取颜色
                            float R = (float)boolEntity.getR() / 255;
                            float G = (float)boolEntity.getG() / 255;
                            float B = (float)boolEntity.getB() / 255;
                            float A = (float)boolEntity.getA() / 255;
                            int  EntityId1 = boolEntity.getBoolEntityId1();
                            int  EntityId2 = boolEntity.getBoolEntityId2();
                            glPushMatrix();
                            glColor4f(R, G, B, A);
                            drawIntersection1(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1,X3,Y3,Z3,RX3,RY3,RZ3);

                            glPopMatrix();
                        }
                    }
                    //else {
                    //    if (boolEntity.getBoolType() == ("Difference")) {
                    //        QString  vs = boolEntity.getTransformMatrix();
                    //        QStringList splits = vs.split(",");
                    //        float mat[16];
                    //        for (int i = 0; i < 16; i++)
                    //        {
                    //            mat[i] = (splits[i]).toFloat();
                    //        }
                    //        ////获取旋转角度
                    //        float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
                    //        float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                    //        float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
                    //        //获取坐标
                    //        float X1 = mat[12];
                    //        float Y1 = mat[13];
                    //        float Z1 = mat[14];
                    //        //获取颜色
                    //        float R = (float)boolEntity.getR() / 255;
                    //        float G = (float)boolEntity.getG() / 255;
                    //        float B = (float)boolEntity.getB() / 255;
                    //        float A = (float)boolEntity.getA() / 255;
                    //        int  EntityId1 = boolEntity.getBoolEntityId1();
                    //        int  EntityId2 = boolEntity.getBoolEntityId2();
                    //        glPushMatrix();
                    //        //glTranslatef(X1, Z1, Y1);
                    //        glColor4f(R, G, B, A);
                    //        drawDifference(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
                    //        glPopMatrix();
                    //    }
                    //}
                }
            }
        }
        else {
        QString  vs2 = modFile.gettransformMatrix2();
        QStringList vs2splits = vs2.split(",");
        float mat2[16];
        for (int i = 0; i < 16; i++)
        {
            mat2[i] = (vs2splits[i]).toFloat();
        }
        //获取旋转角度
        float RX3 = (atan2(mat2[9], mat2[10])) * PI / 180;
        float RY3 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
        float RZ3 = (atan2(mat2[4], mat2[0])) * PI / 180;
        ////获取坐标
        float X3 = mat2[12];
        float Y3 = mat2[13];
        float Z3 = mat2[14];
        QString  vs1 = modFile.gettransformMatrix1();
        QStringList vs1splits = vs1.split(",");
        float mat1[16];
        for (int i = 0; i < 16; i++)
        {
            mat1[i] = (vs1splits[i]).toFloat();
        }
        //获取旋转角度
        float RX2 = (atan2(mat1[9], mat1[10])) * PI / 180;
        float RY2 = (atan2(-mat1[8], sqrt(pow(mat1[9], 8) + pow(mat1[10], 8)))) * PI / 180;
        float RZ2 = (atan2(mat1[4], mat1[0])) * PI / 180;
        //获取坐标
        float X2 = mat1[12];
        float Y2 = mat1[13];
        float Z2 = mat1[14];
        for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
            if (!simpleEntity.getGraphicElement().isNull()) {
                if (simpleEntity.getVisible() == ("true")) {
                    if (simpleEntity.getGraphicElement().nodeName() == ("TerminalBlock")) {
                        QDomElement n = simpleEntity.getGraphicElement().toElement();
                        QString  vs = simpleEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        ////获取旋转角度
                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X = mat[12];
                        float Y = mat[13];
                        float Z = mat[14];
                        //获取颜色
                        float R = (float)simpleEntity.getR() / 255;
                        float G = (float)simpleEntity.getG() / 255;
                        float B = (float)simpleEntity.getB() / 255;
                        float A = (float)simpleEntity.getA() / 255;
                        //获取长宽高
                        float L = (n.attribute("L")).toFloat();
                        float W = (n.attribute("W")).toFloat();
                        float T = (n.attribute("T")).toFloat();
                        float CL = (n.attribute("CL")).toFloat();
                        float CS = (n.attribute("CS")).toFloat();
                        float RS = (n.attribute("RS")).toFloat();
                        float R1 = (n.attribute("R")).toFloat();
                        float CN = (n.attribute("CN")).toFloat();
                        float RN = (n.attribute("RN")).toFloat();
                        float BL = (n.attribute("BL")).toFloat();
                        //                  
                        glPushMatrix();
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glColor4f(R, G, B, A);
                        TerminalBlock2(L, W, T, CL, CS, RS, R1, CN, RN, BL, X, Y, Z, rX, rY, rZ, X3, Y3, Z3, RX3, RY3, RZ3, X2, Y2, Z2, RX2, RY2, RZ2);
                        glPopMatrix();
                    }
                    //if (simpleEntity.getGraphicElement().nodeName() == ("Rectangular fixed plate")) {
                    //    QDomElement n = simpleEntity.getGraphicElement().toElement();
                    //    QString  vs = simpleEntity.getTransformMatrix();
                    //    QStringList splits = vs.split(",");
                    //    float mat[16];
                    //    for (int i = 0; i < 16; i++)
                    //    {
                    //        mat[i] = (splits[i]).toFloat();
                    //    }
                    //    //获取旋转角度
                    //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
                    //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                    //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                    //    //获取坐标
                    //    float X = mat[12];
                    //    float Y = mat[13];
                    //    float Z = mat[14];
                    //    //获取颜色
                    //    float R = (float)simpleEntity.getR() / 255;
                    //    float G = (float)simpleEntity.getG() / 255;
                    //    float B = (float)simpleEntity.getB() / 255;
                    //    float A = (float)simpleEntity.getA() / 255;
                    //    //获取长宽高
                    //    float L = (n.attribute("L")).toFloat();
                    //    float W = (n.attribute("W")).toFloat();
                    //    float T = (n.attribute("T")).toFloat();
                    //    float CS = (n.attribute("CS")).toFloat();
                    //    float RS = (n.attribute("RS")).toFloat();
                    //    float CN = (n.attribute("CN")).toFloat();
                    //    float RN = (n.attribute("RN")).toFloat();
                    //    float MH = (n.attribute("MH")).toFloat();
                    //    float D = (n.attribute("D")).toFloat();
                    //    //
                    //    glPushMatrix();
                    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    //    glColor4f(R, G, B, A);
                    //    RectangularFixedPlate(L, W, T, CS, RS, CN, RN, MH, D, X, Y, Z, rX, rY, rZ);
                    //    glPopMatrix();
                    //}
                    //if (simpleEntity.getGraphicElement().nodeName() == ("Circular fixed plate")) {
                    //    QDomElement n = simpleEntity.getGraphicElement().toElement();
                    //    QString  vs = simpleEntity.getTransformMatrix();
                    //    QStringList splits = vs.split(",");
                    //    float mat[16];
                    //    for (int i = 0; i < 16; i++)
                    //    {
                    //        mat[i] = (splits[i]).toFloat();
                    //    }
                    //    ////获取旋转角度
                    //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
                    //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                    //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                    //    //获取坐标
                    //    float X = mat[12];
                    //    float Y = mat[13];
                    //    float Z = mat[14];
                    //    //获取颜色
                    //    float R = (float)simpleEntity.getR() / 255;
                    //    float G = (float)simpleEntity.getG() / 255;
                    //    float B = (float)simpleEntity.getB() / 255;
                    //    float A = (float)simpleEntity.getA() / 255;
                    //    //获取长宽高
                    //    float L = (n.attribute("L")).toFloat();
                    //    float W = (n.attribute("W")).toFloat();
                    //    float T = (n.attribute("T")).toFloat();
                    //    float CS = (n.attribute("CS")).toFloat();
                    //    float N = (n.attribute("N")).toFloat();
                    //    float MH = (n.attribute("MH")).toFloat();
                    //    float D = (n.attribute("D")).toFloat();
                    //    //
                    //    glPushMatrix();
                    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    //    glColor4f(R, G, B, A);
                    //    CircularFixedPlate(L, W, T, CS, N, MH, D, X, Y, Z, rX, rY, rZ);
                    //    glPopMatrix();
                    //}
                }
            }
            //for (BoolEntity boolEntity : modFile.getBoolEntities()) {
        //      if (!boolEntity.getBoolType().isNull()) {
        //          if (boolEntity.getVisible() == ("true")) {
        //              if (boolEntity.getBoolType() == ("Difference")) {
        //                  QString  vs = boolEntity.getTransformMatrix();
        //                  QStringList splits = vs.split(",");
        //                  float mat[16];
        //                  for (int i = 0; i < 16; i++)
        //                  {
        //                      mat[i] = (splits[i]).toFloat();
        //                  }
        //                  ////获取旋转角度
        //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
        //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
        //                  //获取坐标
        //                  float X1 = mat[12];
        //                  float Y1 = mat[13];
        //                  float Z1 = mat[14];
        //                  //获取颜色
        //                  float R = (float)boolEntity.getR() / 255;
        //                  float G = (float)boolEntity.getG() / 255;
        //                  float B = (float)boolEntity.getB() / 255;
        //                  float A = (float)boolEntity.getA() / 255;
        //                  int  EntityId1 = boolEntity.getBoolEntityId1();
        //                  int  EntityId2 = boolEntity.getBoolEntityId2();
        //                  glPushMatrix();
        //                  //glTranslatef(X1, Z1, Y1);
        //                  glColor4f(R, G, B, A);
        //                  drawDifference(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
        //                  glPopMatrix();
        //              }
        //              if (boolEntity.getBoolType() == ("Union")) {
        //                  QString  vs = boolEntity.getTransformMatrix();
        //                  QStringList splits = vs.split(",");
        //                  float mat[16];
        //                  for (int i = 0; i < 16; i++)
        //                  {
        //                      mat[i] = (splits[i]).toFloat();
        //                  }
        //                  //获取旋转角度
        //                  float rX = (atan2(mat[9], mat[10])) * PI / 180;
        //                  float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //                  float rZ = (atan2(mat[4], mat[0])) * PI / 180;
        //                  //获取坐标
        //                  float X1 = mat[12];
        //                  float Y1 = mat[13];
        //                  float Z1 = mat[14];
        //                  //获取颜色
        //                  float R = (float)boolEntity.getR() / 255;
        //                  float G = (float)boolEntity.getG() / 255;
        //                  float B = (float)boolEntity.getB() / 255;
        //                  float A = (float)boolEntity.getA() / 255;
        //                  int  EntityId1 = boolEntity.getBoolEntityId1();
        //                  int  EntityId2 = boolEntity.getBoolEntityId2();
        //                  glPushMatrix();
        //                  glColor4f(R, G, B, A);
        //                  draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
        //                  draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
        //                  glPopMatrix();
        //              }
        //              if (boolEntity.getBoolType() == ("Intersection")) {
        //                  QString  vs = boolEntity.getTransformMatrix();
        //                  QStringList splits = vs.split(",");
        //                  float mat[16];
        //                  for (int i = 0; i < 16; i++)
        //                  {
        //                      mat[i] = (splits[i]).toFloat();
        //                  }
        //                  ////获取旋转角度
        //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
        //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
        //                  //获取坐标
        //                  float X1 = mat[12];
        //                  float Y1 = mat[13];
        //                  float Z1 = mat[14];
        //                  //获取颜色
        //                  float R = (float)boolEntity.getR() / 255;
        //                  float G = (float)boolEntity.getG() / 255;
        //                  float B = (float)boolEntity.getB() / 255;
        //                  float A = (float)boolEntity.getA() / 255;
        //                  int  EntityId1 = boolEntity.getBoolEntityId1();
        //                  int  EntityId2 = boolEntity.getBoolEntityId2();
        //                  glPushMatrix();
        //                  glColor4f(R, G, B, A);
        //                  drawIntersection(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
        //                  glPopMatrix();
        //              }
        //          }
        //      }
        //  }
           //glPopMatrix();
    //}
            //glPopMatrix();
        }
        for (BoolEntity boolEntity : modFile.getBoolEntities()) {
            if (!boolEntity.getBoolType().isNull()) {
                if (boolEntity.getVisible() == ("true")) {
                    if (boolEntity.getBoolType() == ("Difference")) {
                        QString  vs = boolEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        ////获取旋转角度
                        float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X1 = mat[12];
                        float Y1 = mat[13];
                        float Z1 = mat[14];
                        //获取颜色
                        float R = (float)boolEntity.getR() / 255;
                        float G = (float)boolEntity.getG() / 255;
                        float B = (float)boolEntity.getB() / 255;
                        float A = (float)boolEntity.getA() / 255;
                        int  EntityId1 = boolEntity.getBoolEntityId1();
                        int  EntityId2 = boolEntity.getBoolEntityId2();
                        glPushMatrix();
                        glColor4f(R, G, B, A);
                        drawDifference2(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1,X3,Y3,Z3,RX3,RY3,RZ3,X2,Y2,Z3,RX2,RY2,RZ2);
                        glPopMatrix();
                    }
                    if (boolEntity.getBoolType() == ("Union")) {
                        QString  vs = boolEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        //获取旋转角度
                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X1 = mat[12];
                        float Y1 = mat[13];
                        float Z1 = mat[14];
                        //获取颜色
                        float R = (float)boolEntity.getR() / 255;
                        float G = (float)boolEntity.getG() / 255;
                        float B = (float)boolEntity.getB() / 255;
                        float A = (float)boolEntity.getA() / 255;
                        int  EntityId1 = boolEntity.getBoolEntityId1();
                        int  EntityId2 = boolEntity.getBoolEntityId2();
                        //绘制第一个图形
                        glPushMatrix();
                        glPushMatrix();
                        glTranslatef(X3, Z3, Y3);
                        glRotatef(RX3, 1, 0, 0);
                        glRotatef(RY3, 0, 1, 0);
                        glRotatef(RZ3, 0, 0, 1);
                        glPushMatrix();
                        glTranslatef(X2, Z2, Y2);
                        glRotatef(RX2, 1, 0, 0);
                        glRotatef(RY2, 0, 1, 0);
                        glRotatef(RZ2, 0, 0, 1);
                        glColor4f(R, G, B, A);
                        draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
                        glPopMatrix();
                        glPopMatrix();
                        glPopMatrix();
                        //绘制第二个图形
                        glPushMatrix();
                        glPushMatrix();
                        glTranslatef(X3, Z3, Y3);
                        glRotatef(RX3, 1, 0, 0);
                        glRotatef(RY3, 0, 1, 0);
                        glRotatef(RZ3, 0, 0, 1);
                        glPushMatrix();
                        glTranslatef(X2, Z2, Y2);
                        glRotatef(RX2, 1, 0, 0);
                        glRotatef(RY2, 0, 1, 0);
                        glRotatef(RZ2, 0, 0, 1);
                        glColor4f(R, G, B, A);
                        draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
                        glPopMatrix();
                        glPopMatrix();
                        glPopMatrix();
                    }
                    if (boolEntity.getBoolType() == ("Intersection")) {
                        QString  vs = boolEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        ////获取旋转角度
                        float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X1 = mat[12];
                        float Y1 = mat[13];
                        float Z1 = mat[14];
                        //获取颜色
                        float R = (float)boolEntity.getR() / 255;
                        float G = (float)boolEntity.getG() / 255;
                        float B = (float)boolEntity.getB() / 255;
                        float A = (float)boolEntity.getA() / 255;
                        int  EntityId1 = boolEntity.getBoolEntityId1();
                        int  EntityId2 = boolEntity.getBoolEntityId2();
                        glPushMatrix();
                        glColor4f(R, G, B, A);
                        drawIntersection2(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1,X3,Y3,Z3,RX3,RY3,RZ3, X2, Y2, Z2, RX2, RY2, RZ2);

                        glPopMatrix();
                    }
                }
                //else {
                //    if (boolEntity.getBoolType() == ("Difference")) {
                //        QString  vs = boolEntity.getTransformMatrix();
                //        QStringList splits = vs.split(",");
                //        float mat[16];
                //        for (int i = 0; i < 16; i++)
                //        {
                //            mat[i] = (splits[i]).toFloat();
                //        }
                //        ////获取旋转角度
                //        float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
                //        float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                //        float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
                //        //获取坐标
                //        float X1 = mat[12];
                //        float Y1 = mat[13];
                //        float Z1 = mat[14];
                //        //获取颜色
                //        float R = (float)boolEntity.getR() / 255;
                //        float G = (float)boolEntity.getG() / 255;
                //        float B = (float)boolEntity.getB() / 255;
                //        float A = (float)boolEntity.getA() / 255;
                //        int  EntityId1 = boolEntity.getBoolEntityId1();
                //        int  EntityId2 = boolEntity.getBoolEntityId2();
                //        glPushMatrix();
                //        //glTranslatef(X1, Z1, Y1);
                //        glColor4f(R, G, B, A);
                //        drawDifference(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
               //        glPopMatrix();
                //    }
                //}
            }

        }
       
}
      

    }
    glPopMatrix();
  

}
void myopengl::drawboolEntity1()
{
    for (int i = 0; i < gimModFileList.size(); i++) {
        ModFile modFile = gimModFileList[i];
        for (BoolEntity boolEntity : modFile.getBoolEntities()) {
            if (!boolEntity.getBoolType().isNull()) {
                if (boolEntity.getVisible() == ("true")) {
                    if (boolEntity.getBoolType() == ("Difference")) {
                        QString  vs = boolEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        ////获取旋转角度
                        float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X1 = mat[12];
                        float Y1 = mat[13];
                        float Z1 = mat[14];
                        //获取颜色
                        float R = (float)boolEntity.getR() / 255;
                        float G = (float)boolEntity.getG() / 255;
                        float B = (float)boolEntity.getB() / 255;
                        float A = (float)boolEntity.getA() / 255;
                        int  EntityId1 = boolEntity.getBoolEntityId1();
                        int  EntityId2 = boolEntity.getBoolEntityId2();
                        glPushMatrix();

                        glColor4f(0, 1, 1, 1);
                        //drawDifference(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1,X3,Y3,Z3);

                        glPopMatrix();
                    }
                    if (boolEntity.getBoolType() == ("Union")) {
                        QString  vs = boolEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        //获取旋转角度
                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X1 = mat[12];
                        float Y1 = mat[13];
                        float Z1 = mat[14];
                        //获取颜色
                        float R = (float)boolEntity.getR() / 255;
                        float G = (float)boolEntity.getG() / 255;
                        float B = (float)boolEntity.getB() / 255;
                        float A = (float)boolEntity.getA() / 255;
                        int  EntityId1 = boolEntity.getBoolEntityId1();
                        int  EntityId2 = boolEntity.getBoolEntityId2();
                        glPushMatrix();

                        glColor4f(0, 1, 1, 1);
                        draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
                        draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
                        glPopMatrix();
                    }
                    if (boolEntity.getBoolType() == ("Intersection")) {
                        QString  vs = boolEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        ////获取旋转角度
                        float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X1 = mat[12];
                        float Y1 = mat[13];
                        float Z1 = mat[14];
                        //获取颜色
                        float R = (float)boolEntity.getR() / 255;
                        float G = (float)boolEntity.getG() / 255;
                        float B = (float)boolEntity.getB() / 255;
                        float A = (float)boolEntity.getA() / 255;
                        int  EntityId1 = boolEntity.getBoolEntityId1();
                        int  EntityId2 = boolEntity.getBoolEntityId2();
                        glPushMatrix();
                        glColor4f(0, 1, 1, 1);
                        //drawIntersection(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);

                        glPopMatrix();
                    }
                }
            }
        }
        for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
            if (!simpleEntity.getGraphicElement().isNull()) {
                if (simpleEntity.getVisible() == ("true")) {
                    if (simpleEntity.getGraphicElement().nodeName() == ("TerminalBlock")) {
                        QDomElement n = simpleEntity.getGraphicElement().toElement();
                        QString  vs = simpleEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        ////获取旋转角度
                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X = mat[12];
                        float Y = mat[13];
                        float Z = mat[14];
                        //获取颜色
                        float R = (float)simpleEntity.getR() / 255;
                        float G = (float)simpleEntity.getG() / 255;
                        float B = (float)simpleEntity.getB() / 255;
                        float A = (float)simpleEntity.getA() / 255;
                        //获取长宽高
                        float L = (n.attribute("L")).toFloat();
                        float W = (n.attribute("W")).toFloat();
                        float T = (n.attribute("T")).toFloat();
                        float CL = (n.attribute("CL")).toFloat();
                        float CS = (n.attribute("CS")).toFloat();
                        float RS = (n.attribute("RS")).toFloat();
                        float R1 = (n.attribute("R")).toFloat();
                        float CN = (n.attribute("CN")).toFloat();
                        float RN = (n.attribute("RN")).toFloat();
                        float BL = (n.attribute("BL")).toFloat();
                        //                  
                        glPushMatrix();
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glColor4f(0, 1, 1, 1);
                        //TerminalBlock(L, W, T, CL, CS, RS, R1, CN, RN, BL, X, Y, Z, rX, rY, rZ);
                        glPopMatrix();
                    }
                    if (simpleEntity.getGraphicElement().nodeName() == ("Rectangular fixed plate")) {
                        QDomElement n = simpleEntity.getGraphicElement().toElement();
                        QString  vs = simpleEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        //获取旋转角度
                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X = mat[12];
                        float Y = mat[13];
                        float Z = mat[14];
                        //获取颜色
                        float R = (float)simpleEntity.getR() / 255;
                        float G = (float)simpleEntity.getG() / 255;
                        float B = (float)simpleEntity.getB() / 255;
                        float A = (float)simpleEntity.getA() / 255;
                        //获取长宽高
                        float L = (n.attribute("L")).toFloat();
                        float W = (n.attribute("W")).toFloat();
                        float T = (n.attribute("T")).toFloat();
                        float CS = (n.attribute("CS")).toFloat();
                        float RS = (n.attribute("RS")).toFloat();
                        float CN = (n.attribute("CN")).toFloat();
                        float RN = (n.attribute("RN")).toFloat();
                        float MH = (n.attribute("MH")).toFloat();
                        float D = (n.attribute("D")).toFloat();
                        //
                        glPushMatrix();
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glColor4f(0, 1, 1, 1);
                        RectangularFixedPlate(L, W, T, CS, RS, CN, RN, MH, D, X, Y, Z, rX, rY, rZ);
                        glPopMatrix();
                    }
                    if (simpleEntity.getGraphicElement().nodeName() == ("Circular fixed plate")) {
                        QDomElement n = simpleEntity.getGraphicElement().toElement();
                        QString  vs = simpleEntity.getTransformMatrix();
                        QStringList splits = vs.split(",");
                        float mat[16];
                        for (int i = 0; i < 16; i++)
                        {
                            mat[i] = (splits[i]).toFloat();
                        }
                        ////获取旋转角度
                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                        //获取坐标
                        float X = mat[12];
                        float Y = mat[13];
                        float Z = mat[14];
                        //获取颜色
                        float R = (float)simpleEntity.getR() / 255;
                        float G = (float)simpleEntity.getG() / 255;
                        float B = (float)simpleEntity.getB() / 255;
                        float A = (float)simpleEntity.getA() / 255;
                        //获取长宽高
                        float L = (n.attribute("L")).toFloat();
                        float W = (n.attribute("W")).toFloat();
                        float T = (n.attribute("T")).toFloat();
                        float CS = (n.attribute("CS")).toFloat();
                        float N = (n.attribute("N")).toFloat();
                        float MH = (n.attribute("MH")).toFloat();
                        float D = (n.attribute("D")).toFloat();
                        //
                        glPushMatrix();
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glColor4f(0, 1, 1, 1);
                        CircularFixedPlate(L, W, T, CS, N, MH, D, X, Y, Z, rX, rY, rZ);
                        glPopMatrix();
                    }
                }
            }
        }

    }
}
void myopengl::drawboolEntity2()
{
    //for (int i = 0; i < gimModFileList.size(); i++) {
    //    ModFile modFile = gimModFileList[i];
    //    for (BoolEntity boolEntity : modFile.getBoolEntities()) {
    //        if (!boolEntity.getBoolType().isNull()) {
    //            //if (boolEntity.getVisible() == ("true")) {
    //            if (boolEntity.getBoolType() == ("Difference")) {
    //                QString  vs = boolEntity.getTransformMatrix();
    //                QStringList splits = vs.split(",");
    //                float mat[16];
    //                for (int i = 0; i < 16; i++)
    //                {
    //                    mat[i] = (splits[i]).toFloat();
    //                }
    //                ////获取旋转角度
    //                float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
    //                float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
    //                //获取坐标
    //                float X1 = mat[12];
    //                float Y1 = mat[13];
    //                float Z1 = mat[14];
    //                //获取颜色
    //                float R = (float)boolEntity.getR() / 255;
    //                float G = (float)boolEntity.getG() / 255;
    //                float B = (float)boolEntity.getB() / 255;
    //                float A = (float)boolEntity.getA() / 255;
    //                int  EntityId1 = boolEntity.getBoolEntityId1();
    //                int  EntityId2 = boolEntity.getBoolEntityId2();
    //                glPushMatrix();
    //                clearPrimtives();
    //                if (!glIsList((GLuint)(100000000))) {
    //                    glNewList(100000000, GL_COMPILE);
    //                    //GLuint id100000000 = glGenLists(1);
    //                    //glNewList(id100000000, GL_COMPILE);
    //                    glPushMatrix();


    //                    for (int i = 0; i < gimModFileList.size(); i++) {
    //                        ModFile modFile = gimModFileList[i];
    //                        for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
    //                            if (!simpleEntity.getGraphicElement().isNull()) {
    //                                if (simpleEntity.getVisible() != ("true")) {

    //                                    if ((simpleEntity.getGraphicElement().nodeName() == ("Cuboid")) && (simpleEntity.getEntityId() == EntityId)) {

    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];


    //                                        //获取长宽高

    //                                        float L = (n.attribute("L")).toFloat();
    //                                        float W = (n.attribute("W")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();


    //                                        //绘制线框
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        Cuboid(L, W, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                        //绘制实体
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        Cuboid(L, W, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("Sphere") && simpleEntity.getEntityId() == EntityId) {

    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float R1 = (n.attribute("R")).toFloat();


    //                                        //GLuint id2 = glGenLists(1);
    //                                       // glNewList(id2, GL_COMPILE);
    //                                        //绘制线框
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        Sphere(R1);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //绘制实体
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        Sphere(R1);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("RotationalEllipsoid") && simpleEntity.getEntityId() == EntityId)
    //                                    {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        ////获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float LR = (n.attribute("LR")).toFloat();
    //                                        float WR = (n.attribute("WR")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();


    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        RotationalEllipsoid(LR, WR, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        RotationalEllipsoid(LR, WR, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("Table") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        ////获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float TL1 = (n.attribute("TL1")).toFloat();
    //                                        float TL2 = (n.attribute("TL2")).toFloat();
    //                                        float LL1 = (n.attribute("LL1")).toFloat();
    //                                        float LL2 = (n.attribute("LL2")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();

    //                                        //
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        Table(TL1, TL2, LL1, LL2, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        Table(TL1, TL2, LL1, LL2, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("OffsetRectangularTable") && simpleEntity.getEntityId() == EntityId)
    //                                    {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        ////获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float TL = (n.attribute("TL")).toFloat();
    //                                        float TW = (n.attribute("TW")).toFloat();
    //                                        float LL = (n.attribute("LL")).toFloat();
    //                                        float LW = (n.attribute("LW")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();
    //                                        float XOFF = (n.attribute("XOFF")).toFloat();
    //                                        float YOFF = (n.attribute("YOFF")).toFloat();

    //                                        //
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        // glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("Cylinder") && simpleEntity.getEntityId() == EntityId)
    //                                    {

    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float R1 = (n.attribute("R")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();

    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        Cylinder(R1, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        Cylinder(R1, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("TruncatedCone") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float TR = (n.attribute("TR")).toFloat();
    //                                        float BR = (n.attribute("BR")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();

    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        /// glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        TruncatedCone(TR, BR, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        TruncatedCone(TR, BR, H);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("EccentricTruncatedCone") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float TR = (n.attribute("TR")).toFloat();
    //                                        float BR = (n.attribute("BR")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();
    //                                        float TOPXOFF = (n.attribute("TOPXOFF")).toFloat();
    //                                        float TOPYOFF = (n.attribute("TOPYOFF")).toFloat();

    //                                        ////1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        // glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("Ring") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float DR = (n.attribute("DR")).toFloat();
    //                                        float R1 = (n.attribute("R")).toFloat();
    //                                        float Rad = (n.attribute("Rad")).toFloat();


    //                                        ////1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        Ring(DR, R1, Rad);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        Ring(DR, R1, Rad);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("RectangularRing") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float DR = (n.attribute("DR")).toFloat();
    //                                        float R1 = (n.attribute("R")).toFloat();
    //                                        float L = (n.attribute("L")).toFloat();
    //                                        float W = (n.attribute("W")).toFloat();

    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        RectangularRing(DR, R1, L, W);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        RectangularRing(DR, R1, L, W);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("EllipticRing") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float DR = (n.attribute("DR")).toFloat();

    //                                        float L = (n.attribute("L")).toFloat();
    //                                        float W = (n.attribute("W")).toFloat();

    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        EllipticRing(DR, L, W);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        EllipticRing(DR, L, W);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("CircularGasket") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float OR = (n.attribute("OR")).toFloat();
    //                                        float IR = (n.attribute("IR")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();
    //                                        float Rad = (n.attribute("Rad")).toFloat();

    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        CircularGasket(OR, IR, H, Rad);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        CircularGasket(OR, IR, H, Rad);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("TableGasket") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float TR = (n.attribute("TR")).toFloat();
    //                                        float OR = (n.attribute("OR")).toFloat();
    //                                        float IR = (n.attribute("IR")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();
    //                                        float Rad = (n.attribute("Rad")).toFloat();

    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        TableGasket(TR, OR, IR, H, Rad);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        TableGasket(TR, OR, IR, H, Rad);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("SquareGasket") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float L1 = (n.attribute("L1")).toFloat();
    //                                        float W1 = (n.attribute("W1")).toFloat();
    //                                        float L2 = (n.attribute("L2")).toFloat();
    //                                        float W2 = (n.attribute("W2")).toFloat();
    //                                        float H = (n.attribute("H")).toFloat();
    //                                        float CT = (n.attribute("CT")).toFloat();
    //                                        float Rad = (n.attribute("Rad")).toFloat();
    //                                        float CL = (n.attribute("CL")).toFloat();


    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("PorcelainBushing") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float H = (n.attribute("H")).toFloat();
    //                                        float R1 = (n.attribute("R")).toFloat();
    //                                        float R2 = (n.attribute("R1")).toFloat();
    //                                        float R3 = (n.attribute("R2")).toFloat();
    //                                        float N = (n.attribute("N")).toFloat();



    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        PorcelainBushing(H, R1, R2, R3, N);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        PorcelainBushing(H, R1, R2, R3, N);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("ConePorcelainBushing") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        //获取颜色
    //                                       /* float R = (float)simpleEntity.getR() / 255;
    //                                        float G = (float)simpleEntity.getG() / 255;
    //                                        float B = (float)simpleEntity.getB() / 255;
    //                                        float A = (float)simpleEntity.getA() / 255;*/
    //                                        //获取长宽高

    //                                        float H = (n.attribute("H")).toFloat();
    //                                        float R1 = (n.attribute("R")).toFloat();
    //                                        float R2 = (n.attribute("R1")).toFloat();
    //                                        float R3 = (n.attribute("R2")).toFloat();
    //                                        float N = (n.attribute("N")).toFloat();

    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        PorcelainBushing(H, R1, R2, R3, N);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        PorcelainBushing(H, R1, R2, R3, N);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                    }
    //                                    if (simpleEntity.getGraphicElement().nodeName() == ("Insulator") && simpleEntity.getEntityId() == EntityId) {
    //                                        QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                        QString  vs = simpleEntity.getTransformMatrix();
    //                                        QStringList splits = vs.split(",");
    //                                        float mat[16];
    //                                        for (int i = 0; i < 16; i++)
    //                                        {
    //                                            mat[i] = (splits[i]).toFloat();
    //                                        }
    //                                        ////获取旋转角度
    //                                        float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                        float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                        float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                        //获取坐标
    //                                        float X = mat[12];
    //                                        float Y = mat[13];
    //                                        float Z = mat[14];
    //                                        ////获取颜色
    //                                        //float R = (float)simpleEntity.getR() / 255;
    //                                        //float G = (float)simpleEntity.getG() / 255;
    //                                        //float B = (float)simpleEntity.getB() / 255;
    //                                        //float A = (float)simpleEntity.getA() / 255;
    //                                        //获取长宽高

    //                                        float N = (n.attribute("N")).toFloat();
    //                                        float D = (n.attribute("D")).toFloat();
    //                                        float N1 = (n.attribute("N1")).toFloat();
    //                                        float H1 = (n.attribute("H1")).toFloat();
    //                                        float R1 = (n.attribute("R1")).toFloat();
    //                                        float R2 = (n.attribute("R2")).toFloat();
    //                                        float R3 = (n.attribute("R")).toFloat();
    //                                        //float FL = (n.attribute("FL")).toFloat();
    //                                        //float AL = (n.attribute("AL")).toFloat();
    //                                        //float LN = (n.attribute("LN")).toFloat();


    //                                        //1
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                        Insulator(N, D, N1, H1, R1, R2, R3);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        //2
    //                                        glPushMatrix();
    //                                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                        glPushMatrix();
    //                                        glTranslatef(X1, Z1, Y1);
    //                                        glRotatef(rX1, 1, 0, 0);
    //                                        glRotatef(rY1, 0, 1, 0);
    //                                        glRotatef(rZ1, 0, 0, 1);
    //                                        glPushMatrix();
    //                                        glTranslatef(X, Z, Y);
    //                                        glRotatef(rX, 1, 0, 0);
    //                                        glRotatef(rY, 0, 1, 0);
    //                                        glRotatef(rZ, 0, 0, 1);
    //                                        //glColor4f(R, G, B, A);
    //                                        Insulator(N, D, N1, H1, R1, R2, R3);
    //                                        glPopMatrix();
    //                                        glPopMatrix();
    //                                        glPopMatrix();

    //                                    }
    //                                    //if (simpleEntity.getGraphicElement().nodeName() == ("TerminalBlock") && simpleEntity.getEntityId() == EntityId) {
    //                                    //    
    //                                    //    QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                    //    QString  vs = simpleEntity.getTransformMatrix();
    //                                    //    QStringList splits = vs.split(",");
    //                                    //    float mat[16];
    //                                    //    for (int i = 0; i < 16; i++)
    //                                    //    {
    //                                    //        mat[i] = (splits[i]).toFloat();
    //                                    //    }
    //                                    //    ////获取旋转角度
    //                                    //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                    //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                    //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                    //    //获取坐标
    //                                    //    float X = mat[12];
    //                                    //    float Y = mat[13];
    //                                    //    float Z = mat[14];
    //                                    //    ////获取颜色
    //                                    //    //float R = (float)simpleEntity.getR() / 255;
    //                                    //    //float G = (float)simpleEntity.getG() / 255;
    //                                    //    //float B = (float)simpleEntity.getB() / 255;
    //                                    //    //float A = (float)simpleEntity.getA() / 255;
    //                                    //    //获取长宽高
    //                                    //    float L = (n.attribute("L")).toFloat();
    //                                    //    float W = (n.attribute("W")).toFloat();
    //                                    //    float T = (n.attribute("T")).toFloat();
    //                                    //    float CL = (n.attribute("CL")).toFloat();
    //                                    //    float CS = (n.attribute("CS")).toFloat();
    //                                    //    float RS = (n.attribute("RS")).toFloat();
    //                                    //    float R1 = (n.attribute("R")).toFloat();
    //                                    //    float CN = (n.attribute("CN")).toFloat();
    //                                    //    float RN = (n.attribute("RN")).toFloat();
    //                                    //    float BL = (n.attribute("BL")).toFloat();
    //                                    //    //GLuint id18 = glGenLists(1);
    //                                    //    //glNewList(id18, GL_COMPILE);
    //                                    //    //1
    //                                    //    glPushMatrix();
    //                                    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                    //    glTranslatef(X, Z, Y);
    //                                    //    glRotatef(rX, 1, 0, 0);
    //                                    //    glRotatef(rY, 0, 1, 0);
    //                                    //    glRotatef(rZ, 0, 0, 1);
    //                                    //    glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                    //    TerminalBlock(L, W, T, CL, CS, RS, R1,CN,RN,BL, X,  Y,  Z, rX, rY, rZ);
    //                                    //    glPopMatrix();
    //                                    //    //2
    //                                    //    glPushMatrix();
    //                                    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                    //    glTranslatef(X, Z, Y);
    //                                    //    glRotatef(rX, 1, 0, 0);
    //                                    //    glRotatef(rY, 0, 1, 0);
    //                                    //    glRotatef(rZ, 0, 0, 1);
    //                                    //    //glColor4f(R, G, B, A);
    //                                    //    TerminalBlock(L, W, T, CL, CS, RS, R1, CN, RN,BL, X, Y, Z, rX, rY, rZ);
    //                                    //    glPopMatrix();
    //                                    //    // glEndList();
    //                                    //}
    //                                    //if (simpleEntity.getGraphicElement().nodeName() == ("Rectangular fixed plate") && simpleEntity.getEntityId() == EntityId) {
    //                                    //    QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                    //    QString  vs = simpleEntity.getTransformMatrix();
    //                                    //    QStringList splits = vs.split(",");
    //                                    //    float mat[16];
    //                                    //    for (int i = 0; i < 16; i++)
    //                                    //    {
    //                                    //        mat[i] = (splits[i]).toFloat();
    //                                    //    }
    //                                    //    ////获取旋转角度
    //                                    //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                    //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                    //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                    //    //获取坐标
    //                                    //    float X = mat[12];
    //                                    //    float Y = mat[13];
    //                                    //    float Z = mat[14];
    //                                    //    ////获取颜色
    //                                    //   /* float R = (float)simpleEntity.getR() / 255;
    //                                    //    float G = (float)simpleEntity.getG() / 255;
    //                                    //    float B = (float)simpleEntity.getB() / 255;
    //                                    //    float A = (float)simpleEntity.getA() / 255;*/
    //                                    //    //获取长宽高
    //                                    //    float L = (n.attribute("L")).toFloat();
    //                                    //    float W = (n.attribute("W")).toFloat();
    //                                    //    float T = (n.attribute("T")).toFloat();
    //                                    //    float CS = (n.attribute("CS")).toFloat();
    //                                    //    float RS = (n.attribute("RS")).toFloat();
    //                                    //    float CN = (n.attribute("CN")).toFloat();
    //                                    //    float RN = (n.attribute("RN")).toFloat();
    //                                    //    float MH = (n.attribute("MH")).toFloat();
    //                                    //    float D = (n.attribute("D")).toFloat();
    //                                    //    //GLuint id19 = glGenLists(1);
    //                                    //    //glNewList(id19, GL_COMPILE);
    //                                    //    //1
    //                                    //    glPushMatrix();
    //                                    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                    //    
    //                                    //    glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                    //    RectangularFixedPlate(L, W, T, CS, RS, CN, RN, MH, D,  X,  Y,  Z,  rX,  rY,  rZ);
    //                                    //    glPopMatrix();
    //                                    //    //2
    //                                    //    glPushMatrix();
    //                                    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                    //    
    //                                    //    
    //                                    //    //glColor4f(R, G, B, A);
    //                                    //     RectangularFixedPlate(L, W, T, CS, RS, CN, RN, MH, D, X, Y, Z, rX, rY, rZ);
    //                                    //    glPopMatrix();
    //                                    //    //glEndList();
    //                                    //}
    //                                    //if (simpleEntity.getGraphicElement().nodeName() == ("Circular fixed plate") && simpleEntity.getEntityId() == EntityId) {
    //                                    //    QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                                    //    QString  vs = simpleEntity.getTransformMatrix();
    //                                    //    QStringList splits = vs.split(",");
    //                                    //    float mat[16];
    //                                    //    for (int i = 0; i < 16; i++)
    //                                    //    {
    //                                    //        mat[i] = (splits[i]).toFloat();
    //                                    //    }
    //                                    //    ////获取旋转角度
    //                                    //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                                    //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                                    //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                                    //    //获取坐标
    //                                    //    float X = mat[12];
    //                                    //    float Y = mat[13];
    //                                    //    float Z = mat[14];
    //                                    //    ////获取颜色
    //                                    //    //float R = (float)simpleEntity.getR() / 255;
    //                                    //    //float G = (float)simpleEntity.getG() / 255;
    //                                    //    //float B = (float)simpleEntity.getB() / 255;
    //                                    //    //float A = (float)simpleEntity.getA() / 255;
    //                                    //    //获取长宽高
    //                                    //    float L = (n.attribute("L")).toFloat();
    //                                    //    float W = (n.attribute("W")).toFloat();
    //                                    //    float T = (n.attribute("T")).toFloat();
    //                                    //    float CS = (n.attribute("CS")).toFloat();
    //                                    //    float N = (n.attribute("N")).toFloat();
    //                                    //    float MH = (n.attribute("MH")).toFloat();
    //                                    //    float D = (n.attribute("D")).toFloat();
    //                                    //    //GLuint id20 = glGenLists(1);
    //                                    //   // glNewList(id20, GL_COMPILE);
    //                                    //    //1
    //                                    //    glPushMatrix();
    //                                    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //                                    //    glTranslatef(X, Z, Y);
    //                                    //    glRotatef(rX, 1, 0, 0);
    //                                    //    glRotatef(rY, 0, 1, 0);
    //                                    //    glRotatef(rZ, 0, 0, 1);
    //                                    //    glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
    //                                    //    CircularFixedPlate(L, W, T, CS, N, MH, D, X, Y, Z, rX, rY, rZ);
    //                                    //    glPopMatrix();
    //                                    //    //2
    //                                    //    glPushMatrix();
    //                                    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //                                    //    glTranslatef(X, Z, Y);
    //                                    //    glRotatef(rX, 1, 0, 0);
    //                                    //    glRotatef(rY, 0, 1, 0);
    //                                    //    glRotatef(rZ, 0, 0, 1);
    //                                    //    //glColor4f(R, G, B, A);
    //                                    //    CircularFixedPlate(L, W, T, CS, N, MH, D, X, Y, Z, rX, rY, rZ);
    //                                    //    glPopMatrix();
    //                                    //    //glEndList();
    //                                    //}
    //                                 // break;

    //                                }

    //                            }
    //                        }


    //                    }
    //                    glPopMatrix();
    //                    glEndList();
    //                }
    //                if (!glIsList((GLuint)(100000001))) {
    //                    glNewList(100000001, GL_COMPILE);
    //                    //GLuint id100000001 = glGenLists(1);
    //                    //glNewList(id100000001, GL_COMPILE);
    //                    glPushMatrix();

    //                    draw(EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
    //                    glPopMatrix();
    //                    glEndList();
    //                }
    //                primitives.push_back(new OpenCSG::DisplayListPrimitive(100000000, OpenCSG::Intersection, 1));
    //                primitives.push_back(new OpenCSG::DisplayListPrimitive(100000001, OpenCSG::Subtraction, 1));
    //                OpenCSG::render(primitives);
    //                glDepthFunc(GL_EQUAL);
    //                for (std::vector<OpenCSG::Primitive*>::const_iterator j = primitives.begin(); j != primitives.end(); ++j) {
    //                    (*j)->render();
    //                }
    //                glDepthFunc(GL_LESS);

    //                glPopMatrix();
    //            }
    //            if (boolEntity.getBoolType() == ("Union")) {
    //                QString  vs = boolEntity.getTransformMatrix();
    //                QStringList splits = vs.split(",");
    //                float mat[16];
    //                for (int i = 0; i < 16; i++)
    //                {
    //                    mat[i] = (splits[i]).toFloat();
    //                }
    //                //获取旋转角度
    //                float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                //获取坐标
    //                float X1 = mat[12];
    //                float Y1 = mat[13];
    //                float Z1 = mat[14];
    //                //获取颜色
    //                float R = (float)boolEntity.getR() / 255;
    //                float G = (float)boolEntity.getG() / 255;
    //                float B = (float)boolEntity.getB() / 255;
    //                float A = (float)boolEntity.getA() / 255;
    //                int  EntityId1 = boolEntity.getBoolEntityId1();
    //                int  EntityId2 = boolEntity.getBoolEntityId2();
    //                glPushMatrix();

    //                glColor4f(R, G, B, A);
    //                draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
    //                draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
    //                glPopMatrix();
    //            }
    //            if (boolEntity.getBoolType() == ("Intersection")) {
    //                QString  vs = boolEntity.getTransformMatrix();
    //                QStringList splits = vs.split(",");
    //                float mat[16];
    //                for (int i = 0; i < 16; i++)
    //                {
    //                    mat[i] = (splits[i]).toFloat();
    //                }
    //                ////获取旋转角度
    //                float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
    //                float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
    //                //获取坐标
    //                float X1 = mat[12];
    //                float Y1 = mat[13];
    //                float Z1 = mat[14];
    //                //获取颜色
    //                float R = (float)boolEntity.getR() / 255;
    //                float G = (float)boolEntity.getG() / 255;
    //                float B = (float)boolEntity.getB() / 255;
    //                float A = (float)boolEntity.getA() / 255;
    //                int  EntityId1 = boolEntity.getBoolEntityId1();
    //                int  EntityId2 = boolEntity.getBoolEntityId2();
    //                glPushMatrix();
    //                glColor4f(R, G, B, A);
    //                drawIntersection(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);

    //                glPopMatrix();
    //            }
    //            //}
    //        }
    //    }
    //   
    //}
}
void myopengl::mousePressEvent(QMouseEvent* event)
{

    // Selection buffer
    std::fill(selectBuffer.begin(), selectBuffer.end(), 0);
    glSelectBuffer(selectBufferSize, &selectBuffer[0]);

    // Draw for selection buffer
    glRenderMode(GL_SELECT);
    // Prepare for selection
    glInitNames();
    glPushName(0);
    // Matrix setting
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(event->x(), viewport[3] - event->y(), 1.0, 1.0, viewport);
    const   float  aspect = static_cast <float>(viewport[2]) / viewport[3];
    gluPerspective(45.0, aspect, 1.0, 1000.0);
    // Draw
    paintGL();
    // Reset matrix setting
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    //glMatrixMode(GL_MODELVIEW);
    glFlush();
    // Revert render mode
    hits = glRenderMode(GL_RENDER);
    // Show selection
    printf("%d hits\n", hits);
    if (hits > 0)
    {
        int  id = 0;
        for (int i = 0; i < hits; i++)
        {
            printf("Level: %u\n", selectBuffer[id + 0]);
            printf("  Min: %f\n", (double)selectBuffer[id + 1] / UINT_MAX);
            printf("  Max: %f\n", (double)selectBuffer[id + 2] / UINT_MAX);
            printf("   ID: %u\n", selectBuffer[id + 3]);
            //name = selectBuffer[id + 3];
            id += 4;
        }
        name = selectBuffer[4 * hits - 1];
        GimReader gim;
        gim.read();
    }
    else {
        name = 0;
    }
    ispressed = true;
    prepoint = event->pos();



}
void myopengl::mouseMoveEvent(QMouseEvent* event)
{
    float dx = event->pos().x() - prepoint.x();
    float dy = prepoint.y() - event->pos().y();


    float sensitivity = 0.005f;//灵敏度
    dx *= sensitivity;//偏移量x*灵敏度
    dy *= sensitivity;//偏移量y*灵敏度

    yaw += dx;
    pitch += dy;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camerafront = glm::normalize(front);

    update();


}
void myopengl::mouseReleaseEvent(QMouseEvent* event)
{
    //ispressed = false;
}
void myopengl::Axis() {
    //画下x,y,z轴

    glLineWidth(3.0f);
    glColor3f(1.0f, 0.0f, 0.0f); //画红色的x轴
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100000.0f, 0.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f); //画绿色的y轴
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100000.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f); //画蓝色的z轴
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100000.0f);
    glEnd();
    glFlush();

    //坐标轴刻度
    glPointSize(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);//画x轴上点
    glBegin(GL_POINTS);
    for (int x = 1; x < 1000; x = x + 1) {
        glVertex3f((float)x, 0.0f, 0.0f);
    }
    glEnd();

    glPointSize(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);//画y轴上点
    glBegin(GL_POINTS);
    for (int y = 1; y < 1000; y = y + 1) {
        glVertex3f(0.0f, (float)y, 0.0f);
    }
    glEnd();

    glPointSize(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);//画z轴上点
    glBegin(GL_POINTS);
    for (int z = 1; z < 1000; z = z + 1) {
        glVertex3f(0.0f, 0.0f, (float)z);
    }
    glEnd();
}
void myopengl::drawDifference1(int EntityId1, int EntityId2, GLfloat rX, GLfloat rY, GLfloat rZ, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3)
{
    glPushMatrix();
    clearPrimtives();
    if (!glIsList((GLuint)(100000000))) {
        glNewList(100000000, GL_COMPILE);

        glPushMatrix();
        draw1(EntityId1, rX, rY, rZ, X1, Y1, Z1, X3, Y3, Z3, RX3, RY3, RZ3);
        glPopMatrix();
        glEndList();
    }

    if (!glIsList((GLuint)(100000001))) {
        glNewList(100000001, GL_COMPILE);

        glPushMatrix();

        draw1(EntityId2, rX, rY, rZ, X1, Y1, Z1, X3, Y3, Z3, RX3, RY3, RZ3);
        glPopMatrix();
        glEndList();
    }
    primitives.push_back(new OpenCSG::DisplayListPrimitive(100000000, OpenCSG::Intersection, 1));
    primitives.push_back(new OpenCSG::DisplayListPrimitive(100000001, OpenCSG::Subtraction, 1));
    OpenCSG::render(primitives);
    glDepthFunc(GL_EQUAL);
    for (std::vector<OpenCSG::Primitive*>::const_iterator j = primitives.begin(); j != primitives.end(); ++j) {
        (*j)->render();
    }
    glDepthFunc(GL_LESS);
    glPopMatrix();

}
void myopengl::drawDifference2(int EntityId1, int EntityId2, GLfloat rX, GLfloat rY, GLfloat rZ, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat RX2, GLfloat RY2, GLfloat RZ2)
{
    glPushMatrix();
    clearPrimtives();
    if (!glIsList((GLuint)(100000000))) {
        glNewList(100000000, GL_COMPILE);

        glPushMatrix();
        draw2(EntityId1, rX, rY, rZ, X1, Y1, Z1, X3, Y3, Z3, RX3, RY3, RZ3,X2,Y2,Z2,RX2,RY2,RZ2);
        glPopMatrix();
        glEndList();
    }

    if (!glIsList((GLuint)(100000001))) {
        glNewList(100000001, GL_COMPILE);

        glPushMatrix();

        draw2(EntityId2, rX, rY, rZ, X1, Y1, Z1, X3, Y3, Z3, RX3, RY3, RZ3, X2, Y2, Z2, RX2, RY2, RZ2);
        glPopMatrix();
        glEndList();
    }
    primitives.push_back(new OpenCSG::DisplayListPrimitive(100000000, OpenCSG::Intersection, 1));
    primitives.push_back(new OpenCSG::DisplayListPrimitive(100000001, OpenCSG::Subtraction, 1));
    OpenCSG::render(primitives);
    glDepthFunc(GL_EQUAL);
    for (std::vector<OpenCSG::Primitive*>::const_iterator j = primitives.begin(); j != primitives.end(); ++j) {
        (*j)->render();
    }
    glDepthFunc(GL_LESS);
    glPopMatrix();

}
void myopengl::drawIntersection1(int EntityId1, int EntityId2, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3)
{
    glPushMatrix();
    clearPrimtives();
    if (!glIsList((GLuint)(100000017))) {
        glNewList(100000017, GL_COMPILE);

        glPushMatrix();
        draw1(EntityId1, rX1, rY1, rZ1, X1, Y1, Z1,X3,Y3,Z3,RX3,RY3,RZ3);
        glPopMatrix();
        glEndList();
    }
    if (!glIsList((GLuint)(100000018))) {
        glNewList(100000018, GL_COMPILE);

        glPushMatrix();

        draw1(EntityId2, rX1, rY1, rZ1, X1, Y1, Z1, X3, Y3, Z3, RX3, RY3, RZ3);
        glPopMatrix();
        glEndList();
    }
    primitives.push_back(new OpenCSG::DisplayListPrimitive(100000017, OpenCSG::Intersection, 1));
    primitives.push_back(new OpenCSG::DisplayListPrimitive(100000018, OpenCSG::Intersection, 1));

    OpenCSG::render(primitives);
    glDepthFunc(GL_EQUAL);
    for (std::vector<OpenCSG::Primitive*>::const_iterator j = primitives.begin(); j != primitives.end(); ++j) {
        (*j)->render();
    }
    glDepthFunc(GL_LESS);
    glPopMatrix();

}
void myopengl::drawIntersection2(int EntityId1, int EntityId2, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat RX2, GLfloat RY2, GLfloat RZ2)
{
    glPushMatrix();
    clearPrimtives();
    if (!glIsList((GLuint)(100000017))) {
        glNewList(100000017, GL_COMPILE);

        glPushMatrix();
        draw2(EntityId1, rX1, rY1, rZ1, X1, Y1, Z1, X3, Y3, Z3, RX3, RY3, RZ3, X2, Y2, Z2, RX2, RY2, RZ2);
        glPopMatrix();
        glEndList();
    }
    if (!glIsList((GLuint)(100000018))) {
        glNewList(100000018, GL_COMPILE);

        glPushMatrix();

        draw2(EntityId2, rX1, rY1, rZ1, X1, Y1, Z1, X3, Y3, Z3, RX3, RY3, RZ3, X2, Y2, Z2, RX2, RY2, RZ2);
        glPopMatrix();
        glEndList();
    }
    primitives.push_back(new OpenCSG::DisplayListPrimitive(100000017, OpenCSG::Intersection, 1));
    primitives.push_back(new OpenCSG::DisplayListPrimitive(100000018, OpenCSG::Intersection, 1));

    OpenCSG::render(primitives);
    glDepthFunc(GL_EQUAL);
    for (std::vector<OpenCSG::Primitive*>::const_iterator j = primitives.begin(); j != primitives.end(); ++j) {
        (*j)->render();
    }
    glDepthFunc(GL_LESS);
    glPopMatrix();

}
void myopengl::list1() {

        //glPushMatrix();
        for (int i = 0; i < gimModFileList.size(); i++) {

        if (!glIsList((GLuint)(i + 1))) {
            
            glNewList(i + 1, GL_COMPILE);
            ModFile modFile = gimModFileList[i];
            glLoadName(i + 1);
            if (modFile.gettransformMatrix1().isEmpty())
            {
                QString  vs2 = modFile.gettransformMatrix2();
                QStringList vs2splits = vs2.split(",");
                float mat2[16];
                for (int i = 0; i < 16; i++)
                {
                    mat2[i] = (vs2splits[i]).toFloat();
                }
                //获取旋转角度
                float RX2 = (atan2(mat2[9], mat2[10])) * PI / 180;
                float RY2 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
                float RZ2 = (atan2(mat2[4], mat2[0])) * PI / 180;
                ////获取坐标
                float X2 = mat2[12];
                float Y2 = mat2[13];
                float Z2 = mat2[14];
                glPushMatrix();
                glTranslatef(X2, Z2, Y2);
                glRotatef(RX2, 1, 0, 0);
                glRotatef(RY2, 0, 1, 0);
                glRotatef(RZ2, 0, 0, 1);
                glPushMatrix();
                for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
                    if (!simpleEntity.getGraphicElement().isNull()) {
                        if (simpleEntity.getVisible() == ("true")) {
                            if (simpleEntity.getGraphicElement().nodeName() == ("Cuboid")) {

                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float L = (n.attribute("L")).toFloat();
                                float W = (n.attribute("W")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //绘制线框
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Cuboid(L, W, H);
                                glPopMatrix();
                                //绘制实体
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Cuboid(L, W, H);
                                glPopMatrix();

                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Sphere")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float R1 = (n.attribute("R")).toFloat();
                                //绘制线框
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Sphere(R1);
                                glPopMatrix();
                                //绘制实体
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Sphere(R1);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("RotationalEllipsoid")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float LR = (n.attribute("LR")).toFloat();
                                float WR = (n.attribute("WR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                RotationalEllipsoid(LR, WR, H);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                RotationalEllipsoid(LR, WR, H);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Table")) {
                                
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TL1 = (n.attribute("TL1")).toFloat();
                                float TL2 = (n.attribute("TL2")).toFloat();
                                float LL1 = (n.attribute("LL1")).toFloat();
                                float LL2 = (n.attribute("LL2")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Table(TL1, TL2, LL1, LL2, H);
                                glPopMatrix();

                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Table(TL1, TL2, LL1, LL2, H);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("OffsetRectangularTable")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TL = (n.attribute("TL")).toFloat();
                                float TW = (n.attribute("TW")).toFloat();
                                float LL = (n.attribute("LL")).toFloat();
                                float LW = (n.attribute("LW")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float XOFF = (n.attribute("XOFF")).toFloat();
                                float YOFF = (n.attribute("YOFF")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Cylinder")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float R1 = (n.attribute("R")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Cylinder(R1, H);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Cylinder(R1, H);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("TruncatedCone")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TR = (n.attribute("TR")).toFloat();
                                float BR = (n.attribute("BR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                TruncatedCone(TR, BR, H);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                TruncatedCone(TR, BR, H);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("EccentricTruncatedCone")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TR = (n.attribute("TR")).toFloat();
                                float BR = (n.attribute("BR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float TOPXOFF = (n.attribute("TOPXOFF")).toFloat();
                                float TOPYOFF = (n.attribute("TOPYOFF")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Ring")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float DR = (n.attribute("DR")).toFloat();
                                float R1 = (n.attribute("R")).toFloat();
                                float Rad = (n.attribute("Rad")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Ring(DR, R1, Rad);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Ring(DR, R1, Rad);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("RectangularRing")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float DR = (n.attribute("DR")).toFloat();
                                float R1 = (n.attribute("R")).toFloat();
                                float L = (n.attribute("L")).toFloat();
                                float W = (n.attribute("W")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                RectangularRing(DR, R1, L, W);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                RectangularRing(DR, R1, L, W);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("EllipticRing")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float DR = (n.attribute("DR")).toFloat();
                                float L = (n.attribute("L")).toFloat();
                                float W = (n.attribute("W")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                EllipticRing(DR, L, W);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                EllipticRing(DR, L, W);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("CircularGasket")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float OR = (n.attribute("OR")).toFloat();
                                float IR = (n.attribute("IR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float Rad = (n.attribute("Rad")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                CircularGasket(OR, IR, H, Rad);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                CircularGasket(OR, IR, H, Rad);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("TableGasket")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TR = (n.attribute("TR")).toFloat();
                                float OR = (n.attribute("OR")).toFloat();
                                float IR = (n.attribute("IR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float Rad = (n.attribute("Rad")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                TableGasket(TR, OR, IR, H, Rad);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                TableGasket(TR, OR, IR, H, Rad);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("SquareGasket")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float L1 = (n.attribute("L1")).toFloat();
                                float W1 = (n.attribute("W1")).toFloat();
                                float L2 = (n.attribute("L2")).toFloat();
                                float W2 = (n.attribute("W2")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float CT = (n.attribute("CT")).toFloat();
                                float Rad = (n.attribute("Rad")).toFloat();
                                float CL = (n.attribute("CL")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("ConePorcelainBushing")) {
                                qDebug() << 1111 << endl;
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float H = (n.attribute("H")).toFloat();
                                float R1 = (n.attribute("R")).toFloat();
                                float R2 = (n.attribute("R1")).toFloat();
                                float R3 = (n.attribute("R2")).toFloat();
                                float N = (n.attribute("N")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                PorcelainBushing(H, R1, R2, R3, N);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                PorcelainBushing(H, R1, R2, R3, N);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Insulator")) {
                                
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float N = (n.attribute("N")).toFloat();
                                float D = (n.attribute("D")).toFloat();
                                float N1 = (n.attribute("N1")).toFloat();
                                float H1 = (n.attribute("H1")).toFloat();
                                float R1 = (n.attribute("R1")).toFloat();
                                float R2 = (n.attribute("R2")).toFloat();
                                float R3 = (n.attribute("R")).toFloat();
                                //float FL = (n.attribute("FL")).toFloat();
                                //float AL = (n.attribute("AL")).toFloat();
                                //float LN = (n.attribute("LN")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Insulator(N, D, N1, H1, R1, R2, R3);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Insulator(N, D, N1, H1, R1, R2, R3);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("StretchedBody")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                float L = (n.attribute("L")).toFloat();
                                QString Normal = n.attribute("Normal");
                                QString Array = n.attribute("Array");
                                //绘制线框
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                StretchedBody(Normal, Array, L);
                                glPopMatrix();

                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                StretchedBody(Normal, Array, L);
                                glPopMatrix();

                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Wire")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                QString  StartVector = n.attribute("StartVector");
                                QString  EndVector = n.attribute("EndVector");
                                QString  FitCoordArray = n.attribute("FitCoordArray");
                                QString  StartCoord = n.attribute("StartCoord");
                                QString  EndCoord = n.attribute("EndCoord");
                                float D = (n.attribute("D")).toFloat();
                                float Sag = (n.attribute("D")).toFloat();
                                //1
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0, 0, 0, 1);
                                //Wire(StartVector, EndVector, FitCoordArray, StartCoord, EndCoord, D, Sag);
                                glPopMatrix();
                                //2
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                               // Wire(StartVector, EndVector, FitCoordArray, StartCoord, EndCoord, D, Sag);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("PorcelainBushing")) {
                                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                                            QString  vs = simpleEntity.getTransformMatrix();
                                            QStringList splits = vs.split(",");
                                            float mat[16];
                                            for (int i = 0; i < 16; i++)
                                            {
                                                mat[i] = (splits[i]).toFloat();
                                            }
                                            ////获取旋转角度
                                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                            //获取坐标
                                            float X = mat[12];
                                            float Y = mat[13];
                                            float Z = mat[14];
                                            //获取颜色
                                            float R = (float)simpleEntity.getR() / 255;
                                            float G = (float)simpleEntity.getG() / 255;
                                            float B = (float)simpleEntity.getB() / 255;
                                            float A = (float)simpleEntity.getA() / 255;
                                            //获取长宽高
                                            float H = (n.attribute("H")).toFloat();
                                            float R1 = (n.attribute("R")).toFloat();
                                            float R2 = (n.attribute("R1")).toFloat();
                                            float R3 = (n.attribute("R2")).toFloat();
                                            float N1 = (n.attribute("N")).toFloat();
                                           
                                            //
                                            glPushMatrix();
                                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                            glTranslatef(X, Z, Y);
                                            glRotatef(rX, 1, 0, 0);
                                            glRotatef(rY, 0, 1, 0);
                                            glRotatef(rZ, 0, 0, 1);
                                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                            //PorcelainBushing(H, R1, R2, R3, N1);
                                            glPopMatrix();
                                            //
                                            glPushMatrix();
                                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                            glTranslatef(X, Z, Y);
                                            glRotatef(rX, 1, 0, 0);
                                            glRotatef(rY, 0, 1, 0);
                                            glRotatef(rZ, 0, 0, 1);
                                            glColor4f(R, G, B, A);
                                            //PorcelainBushing(H, R1, R2, R3, N1);
                                            glPopMatrix();
                                        }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Cable")) {
                               
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;

                                QString  InflectionCoordArray = n.attribute("InflectionCoordArray");
                                QString  StartCoord = n.attribute("StartCoord");
                                QString  EndCoord = n.attribute("EndCoord");
                                float IRArray = (n.attribute("IRArray")).toFloat();
                                float D = (n.attribute("D")).toFloat();

                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Cable(InflectionCoordArray, StartCoord, EndCoord, D, IRArray);
                                glPopMatrix();

                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Cable(InflectionCoordArray, StartCoord, EndCoord, D, IRArray);
                                glPopMatrix();
                            }
                            
                            
                                
                            
                        }
                    }
                }
                glPopMatrix();
                glPopMatrix();
            }
            else {
                QString  vs2 = modFile.gettransformMatrix2();
                QStringList vs2splits = vs2.split(",");
                float mat2[16];
                for (int i = 0; i < 16; i++)
                {
                    mat2[i] = (vs2splits[i]).toFloat();
                }
                //获取旋转角度
                float RX2 = (atan2(mat2[9], mat2[10])) * PI / 180;
                float RY2 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
                float RZ2 = (atan2(mat2[4], mat2[0])) * PI / 180;
                ////获取坐标
                float X2 = mat2[12];
                float Y2 = mat2[13];
                float Z2 = mat2[14];
                glPushMatrix();
                glTranslatef(X2, Z2, Y2);
                glRotatef(RX2, 1, 0, 0);
                glRotatef(RY2, 0, 1, 0);
                glRotatef(RZ2, 0, 0, 1);

                glPushMatrix();
                QString  vs1 = modFile.gettransformMatrix1();
                QStringList vs1splits = vs1.split(",");
                float mat1[16];
                for (int i = 0; i < 16; i++)
                {
                    mat1[i] = (vs1splits[i]).toFloat();
                }
                //获取旋转角度
                float   RX = (atan2(mat1[9], mat1[10])) * PI / 180;
                float RY = (atan2(-mat1[8], sqrt(pow(mat1[9], 8) + pow(mat1[10], 8)))) * PI / 180;
                float RZ = (atan2(mat1[4], mat1[0])) * PI / 180;
                //获取坐标
                float X1 = mat1[12];
                float Y1 = mat1[13];
                float Z1 = mat1[14];
                //glLoadName(i + 1);

                glTranslatef(X1, Z1, Y1);
                glRotatef(RX, 1, 0, 0);
                glRotatef(RY, 0, 1, 0);
                glRotatef(RZ, 0, 0, 1);
                glPushMatrix();

                //glLoadName(i + 1);
                for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
                    if (!simpleEntity.getGraphicElement().isNull()) {
                        if (simpleEntity.getVisible() == ("true")) {
                            if (simpleEntity.getGraphicElement().nodeName() == ("Cuboid")) {

                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float L = (n.attribute("L")).toFloat();
                                float W = (n.attribute("W")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //绘制线框
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Cuboid(L, W, H);
                                glPopMatrix();
                                //绘制实体
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Cuboid(L, W, H);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Sphere")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float R1 = (n.attribute("R")).toFloat();
                                //绘制线框
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Sphere(R1);
                                glPopMatrix();
                                //绘制实体
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Sphere(R1);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("RotationalEllipsoid")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float LR = (n.attribute("LR")).toFloat();
                                float WR = (n.attribute("WR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                RotationalEllipsoid(LR, WR, H);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                RotationalEllipsoid(LR, WR, H);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Table")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TL1 = (n.attribute("TL1")).toFloat();
                                float TL2 = (n.attribute("TL2")).toFloat();
                                float LL1 = (n.attribute("LL1")).toFloat();
                                float LL2 = (n.attribute("LL2")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Table(TL1, TL2, LL1, LL2, H);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Table(TL1, TL2, LL1, LL2, H);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("OffsetRectangularTable")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TL = (n.attribute("TL")).toFloat();
                                float TW = (n.attribute("TW")).toFloat();
                                float LL = (n.attribute("LL")).toFloat();
                                float LW = (n.attribute("LW")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float XOFF = (n.attribute("XOFF")).toFloat();
                                float YOFF = (n.attribute("YOFF")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Cylinder")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float R1 = (n.attribute("R")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Cylinder(R1, H);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Cylinder(R1, H);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("TruncatedCone")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TR = (n.attribute("TR")).toFloat();
                                float BR = (n.attribute("BR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                TruncatedCone(TR, BR, H);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                TruncatedCone(TR, BR, H);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("EccentricTruncatedCone")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TR = (n.attribute("TR")).toFloat();
                                float BR = (n.attribute("BR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float TOPXOFF = (n.attribute("TOPXOFF")).toFloat();
                                float TOPYOFF = (n.attribute("TOPYOFF")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Ring")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float DR = (n.attribute("DR")).toFloat();
                                float R1 = (n.attribute("R")).toFloat();
                                float Rad = (n.attribute("Rad")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Ring(DR, R1, Rad);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Ring(DR, R1, Rad);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("RectangularRing")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float DR = (n.attribute("DR")).toFloat();
                                float R1 = (n.attribute("R")).toFloat();
                                float L = (n.attribute("L")).toFloat();
                                float W = (n.attribute("W")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                RectangularRing(DR, R1, L, W);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                RectangularRing(DR, R1, L, W);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("EllipticRing")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float DR = (n.attribute("DR")).toFloat();
                                float L = (n.attribute("L")).toFloat();
                                float W = (n.attribute("W")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                EllipticRing(DR, L, W);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                EllipticRing(DR, L, W);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("CircularGasket")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float OR = (n.attribute("OR")).toFloat();
                                float IR = (n.attribute("IR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float Rad = (n.attribute("Rad")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                CircularGasket(OR, IR, H, Rad);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                CircularGasket(OR, IR, H, Rad);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("TableGasket")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float TR = (n.attribute("TR")).toFloat();
                                float OR = (n.attribute("OR")).toFloat();
                                float IR = (n.attribute("IR")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float Rad = (n.attribute("Rad")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                TableGasket(TR, OR, IR, H, Rad);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                TableGasket(TR, OR, IR, H, Rad);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("SquareGasket")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float L1 = (n.attribute("L1")).toFloat();
                                float W1 = (n.attribute("W1")).toFloat();
                                float L2 = (n.attribute("L2")).toFloat();
                                float W2 = (n.attribute("W2")).toFloat();
                                float H = (n.attribute("H")).toFloat();
                                float CT = (n.attribute("CT")).toFloat();
                                float Rad = (n.attribute("Rad")).toFloat();
                                float CL = (n.attribute("CL")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("ConePorcelainBushing")) {
                                
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float H = (n.attribute("H")).toFloat();
                                float R1 = (n.attribute("R")).toFloat();
                                float R2 = (n.attribute("R1")).toFloat();
                                float R3 = (n.attribute("R2")).toFloat();
                                float N = (n.attribute("N")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                PorcelainBushing(H, R1, R2, R3, N);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                PorcelainBushing(H, R1, R2, R3, N);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Insulator")) {
                                
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float N = (n.attribute("N")).toFloat();
                                float D = (n.attribute("D")).toFloat();
                                float N1 = (n.attribute("N1")).toFloat();
                                float H1 = (n.attribute("H1")).toFloat();
                                float R1 = (n.attribute("R1")).toFloat();
                                float R2 = (n.attribute("R2")).toFloat();
                                float R3 = (n.attribute("R")).toFloat();
                                //float FL = (n.attribute("FL")).toFloat();
                                //float AL = (n.attribute("AL")).toFloat();
                                //float LN = (n.attribute("LN")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Insulator(N, D, N1, H1, R1, R2, R3);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Insulator(N, D, N1, H1, R1, R2, R3);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("StretchedBody")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                float L = (n.attribute("L")).toFloat();
                                QString Normal = n.attribute("Normal");
                                QString Array = n.attribute("Array");
                                //绘制线框
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                StretchedBody(Normal, Array, L);
                                glPopMatrix();
                               glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                StretchedBody(Normal, Array, L);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Wire")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                QString  StartVector = n.attribute("StartVector");
                                QString  EndVector = n.attribute("EndVector");
                                QString  FitCoordArray = n.attribute("FitCoordArray");
                                QString  StartCoord = n.attribute("StartCoord");
                                QString  EndCoord = n.attribute("EndCoord");
                                float D = (n.attribute("D")).toFloat();
                                float Sag = (n.attribute("D")).toFloat();
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0, 0, 0, 1);
                               // Wire(StartVector, EndVector, FitCoordArray, StartCoord, EndCoord, D, Sag);
                                glPopMatrix();
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                //Wire(StartVector, EndVector, FitCoordArray, StartCoord, EndCoord, D, Sag);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("PorcelainBushing")) {
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                ////获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;
                                //获取长宽高
                                float H = (n.attribute("H")).toFloat();
                                float R1 = (n.attribute("R")).toFloat();
                                float R2 = (n.attribute("R1")).toFloat();
                                float R3 = (n.attribute("R2")).toFloat();
                                float N1 = (n.attribute("N")).toFloat();
                                
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                //PorcelainBushing(H, R1, R2, R3, N1);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                //PorcelainBushing(H, R1, R2, R3, N1);
                                glPopMatrix();
                            }
                            if (simpleEntity.getGraphicElement().nodeName() == ("Cable")) {
                              
                                QDomElement n = simpleEntity.getGraphicElement().toElement();
                                QString  vs = simpleEntity.getTransformMatrix();
                                QStringList splits = vs.split(",");
                                float mat[16];
                                for (int i = 0; i < 16; i++)
                                {
                                    mat[i] = (splits[i]).toFloat();
                                }
                                //获取旋转角度
                                float rX = (atan2(mat[9], mat[10])) * PI / 180;
                                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                                //获取坐标
                                float X = mat[12];
                                float Y = mat[13];
                                float Z = mat[14];
                                //获取颜色
                                float R = (float)simpleEntity.getR() / 255;
                                float G = (float)simpleEntity.getG() / 255;
                                float B = (float)simpleEntity.getB() / 255;
                                float A = (float)simpleEntity.getA() / 255;

                                QString  InflectionCoordArray = n.attribute("InflectionCoordArray");
                                QString  StartCoord = n.attribute("StartCoord");
                                QString  EndCoord = n.attribute("EndCoord");
                                float IRArray = (n.attribute("IRArray")).toFloat();
                                float D = (n.attribute("D")).toFloat();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                                Cable(InflectionCoordArray, StartCoord, EndCoord, D, IRArray);
                                glPopMatrix();
                                //
                                glPushMatrix();
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                                glTranslatef(X, Z, Y);
                                glRotatef(rX, 1, 0, 0);
                                glRotatef(rY, 0, 1, 0);
                                glRotatef(rZ, 0, 0, 1);
                                glColor4f(R, G, B, A);
                                Cable(InflectionCoordArray, StartCoord, EndCoord, D, IRArray);
                                glPopMatrix();
                            }
                            
                        }
                    }
                }

                glPopMatrix();
                glPopMatrix();
                glPopMatrix();
            }
            glEndList();
       }

        glCallList(i + 1);

        

       // ModFile modFile = gimModFileList[i];
       // if (modFile.gettransformMatrix1().isEmpty())
       // {
       //     QString  vs2 = modFile.gettransformMatrix2();
       //     QStringList vs2splits = vs2.split(",");
       //     float mat2[16];
       //     for (int i = 0; i < 16; i++)
       //     {
       //         mat2[i] = (vs2splits[i]).toFloat();
       //     }
       //     //获取旋转角度
       //     float RX2 = (atan2(mat2[9], mat2[10])) * PI / 180;
       //     float RY2 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
       //     float RZ2 = (atan2(mat2[4], mat2[0])) * PI / 180;
       //     ////获取坐标
       //     float X2 = mat2[12];
       //     float Y2 = mat2[13];
       //     float Z2 = mat2[14];
       //     for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
       //         if (!simpleEntity.getGraphicElement().isNull()) {
       //             if (simpleEntity.getVisible() == ("true")) {
       //                 if (simpleEntity.getGraphicElement().nodeName() == ("TerminalBlock")) {
       //                     QDomElement n = simpleEntity.getGraphicElement().toElement();
       //                     QString  vs = simpleEntity.getTransformMatrix();
       //                     QStringList splits = vs.split(",");
       //                     float mat[16];
       //                     for (int i = 0; i < 16; i++)
       //                     {
       //                         mat[i] = (splits[i]).toFloat();
       //                     }
       //                     ////获取旋转角度
       //                     float rX = (atan2(mat[9], mat[10])) * PI / 180;
       //                     float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //                     float rZ = (atan2(mat[4], mat[0])) * PI / 180;
       //                     //获取坐标
       //                     float X = mat[12];
       //                     float Y = mat[13];
       //                     float Z = mat[14];
       //                     //获取颜色
       //                     float R = (float)simpleEntity.getR() / 255;
       //                     float G = (float)simpleEntity.getG() / 255;
       //                     float B = (float)simpleEntity.getB() / 255;
       //                     float A = (float)simpleEntity.getA() / 255;
       //                     //获取长宽高
       //                     float L = (n.attribute("L")).toFloat();
       //                     float W = (n.attribute("W")).toFloat();
       //                     float T = (n.attribute("T")).toFloat();
       //                     float CL = (n.attribute("CL")).toFloat();
       //                     float CS = (n.attribute("CS")).toFloat();
       //                     float RS = (n.attribute("RS")).toFloat();
       //                     float R1 = (n.attribute("R")).toFloat();
       //                     float CN = (n.attribute("CN")).toFloat();
       //                     float RN = (n.attribute("RN")).toFloat();
       //                     float BL = (n.attribute("BL")).toFloat();
       //                     //                  
       //                     glPushMatrix();
       //                     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       //                     glColor4f(R, G, B, A);
       //                     TerminalBlock1(L, W, T, CL, CS, RS, R1, CN, RN, BL, X, Y, Z, rX, rY, rZ, X2, Y2, Z2, RX2, RY2, RZ2);
       //                     glPopMatrix();
       //                 }
       //                 //if (simpleEntity.getGraphicElement().nodeName() == ("Rectangular fixed plate")) {
       //                 //    QDomElement n = simpleEntity.getGraphicElement().toElement();
       //                 //    QString  vs = simpleEntity.getTransformMatrix();
       //                 //    QStringList splits = vs.split(",");
       //                 //    float mat[16];
       //                 //    for (int i = 0; i < 16; i++)
       //                 //    {
       //                 //        mat[i] = (splits[i]).toFloat();
       //                 //    }
       //                 //    //获取旋转角度
       //                 //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
       //                 //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //                 //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
       //                 //    //获取坐标
       //                 //    float X = mat[12];
       //                 //    float Y = mat[13];
       //                 //    float Z = mat[14];
       //                 //    //获取颜色
       //                 //    float R = (float)simpleEntity.getR() / 255;
       //                 //    float G = (float)simpleEntity.getG() / 255;
       //                 //    float B = (float)simpleEntity.getB() / 255;
       //                 //    float A = (float)simpleEntity.getA() / 255;
       //                 //    //获取长宽高
       //                 //    float L = (n.attribute("L")).toFloat();
       //                 //    float W = (n.attribute("W")).toFloat();
       //                 //    float T = (n.attribute("T")).toFloat();
       //                 //    float CS = (n.attribute("CS")).toFloat();
       //                 //    float RS = (n.attribute("RS")).toFloat();
       //                 //    float CN = (n.attribute("CN")).toFloat();
       //                 //    float RN = (n.attribute("RN")).toFloat();
       //                 //    float MH = (n.attribute("MH")).toFloat();
       //                 //    float D = (n.attribute("D")).toFloat();
       //                 //    //
       //                 //    glPushMatrix();
       //                 //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       //                 //    glColor4f(R, G, B, A);
       //                 //    RectangularFixedPlate(L, W, T, CS, RS, CN, RN, MH, D, X, Y, Z, rX, rY, rZ);
       //                 //    glPopMatrix();
       //                 //}
       //                 //if (simpleEntity.getGraphicElement().nodeName() == ("Circular fixed plate")) {
       //                 //    QDomElement n = simpleEntity.getGraphicElement().toElement();
       //                 //    QString  vs = simpleEntity.getTransformMatrix();
       //                 //    QStringList splits = vs.split(",");
       //                 //    float mat[16];
       //                 //    for (int i = 0; i < 16; i++)
       //                 //    {
       //                 //        mat[i] = (splits[i]).toFloat();
       //                 //    }
       //                 //    ////获取旋转角度
       //                 //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
       //                 //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //                 //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
       //                 //    //获取坐标
       //                 //    float X = mat[12];
       //                 //    float Y = mat[13];
       //                 //    float Z = mat[14];
       //                 //    //获取颜色
       //                 //    float R = (float)simpleEntity.getR() / 255;
       //                 //    float G = (float)simpleEntity.getG() / 255;
       //                 //    float B = (float)simpleEntity.getB() / 255;
       //                 //    float A = (float)simpleEntity.getA() / 255;
       //                 //    //获取长宽高
       //                 //    float L = (n.attribute("L")).toFloat();
       //                 //    float W = (n.attribute("W")).toFloat();
       //                 //    float T = (n.attribute("T")).toFloat();
       //                 //    float CS = (n.attribute("CS")).toFloat();
       //                 //    float N = (n.attribute("N")).toFloat();
       //                 //    float MH = (n.attribute("MH")).toFloat();
       //                 //    float D = (n.attribute("D")).toFloat();
       //                 //    //
       //                 //    glPushMatrix();
       //                 //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       //                 //    glColor4f(R, G, B, A);
       //                 //    CircularFixedPlate(L, W, T, CS, N, MH, D, X, Y, Z, rX, rY, rZ);
       //                 //    glPopMatrix();
       //                 //}
       //             }
       //         }
       //         //for (BoolEntity boolEntity : modFile.getBoolEntities()) {
       //     //      if (!boolEntity.getBoolType().isNull()) {
       //     //          if (boolEntity.getVisible() == ("true")) {
       //     //              if (boolEntity.getBoolType() == ("Difference")) {
       //     //                  QString  vs = boolEntity.getTransformMatrix();
       //     //                  QStringList splits = vs.split(",");
       //     //                  float mat[16];
       //     //                  for (int i = 0; i < 16; i++)
       //     //                  {
       //     //                      mat[i] = (splits[i]).toFloat();
       //     //                  }
       //     //                  ////获取旋转角度
       //     //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
       //     //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //     //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
       //     //                  //获取坐标
       //     //                  float X1 = mat[12];
       //     //                  float Y1 = mat[13];
       //     //                  float Z1 = mat[14];
       //     //                  //获取颜色
       //     //                  float R = (float)boolEntity.getR() / 255;
       //     //                  float G = (float)boolEntity.getG() / 255;
       //     //                  float B = (float)boolEntity.getB() / 255;
       //     //                  float A = (float)boolEntity.getA() / 255;
       //     //                  int  EntityId1 = boolEntity.getBoolEntityId1();
       //     //                  int  EntityId2 = boolEntity.getBoolEntityId2();
       //     //                  glPushMatrix();
       //     //                  //glTranslatef(X1, Z1, Y1);
       //     //                  glColor4f(R, G, B, A);
       //     //                  drawDifference(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
       //     //                  glPopMatrix();
       //     //              }
       //     //              if (boolEntity.getBoolType() == ("Union")) {
       //     //                  QString  vs = boolEntity.getTransformMatrix();
       //     //                  QStringList splits = vs.split(",");
       //     //                  float mat[16];
       //     //                  for (int i = 0; i < 16; i++)
       //     //                  {
       //     //                      mat[i] = (splits[i]).toFloat();
       //     //                  }
       //     //                  //获取旋转角度
       //     //                  float rX = (atan2(mat[9], mat[10])) * PI / 180;
       //     //                  float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //     //                  float rZ = (atan2(mat[4], mat[0])) * PI / 180;
       //     //                  //获取坐标
       //     //                  float X1 = mat[12];
       //     //                  float Y1 = mat[13];
       //     //                  float Z1 = mat[14];
       //     //                  //获取颜色
       //     //                  float R = (float)boolEntity.getR() / 255;
       //     //                  float G = (float)boolEntity.getG() / 255;
       //     //                  float B = (float)boolEntity.getB() / 255;
       //     //                  float A = (float)boolEntity.getA() / 255;
       //     //                  int  EntityId1 = boolEntity.getBoolEntityId1();
       //     //                  int  EntityId2 = boolEntity.getBoolEntityId2();
       //     //                  glPushMatrix();
       //     //                  glColor4f(R, G, B, A);
       //     //                  draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
       //     //                  draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
       //     //                  glPopMatrix();
       //     //              }
       //     //              if (boolEntity.getBoolType() == ("Intersection")) {
       //     //                  QString  vs = boolEntity.getTransformMatrix();
       //     //                  QStringList splits = vs.split(",");
       //     //                  float mat[16];
       //     //                  for (int i = 0; i < 16; i++)
       //     //                  {
       //     //                      mat[i] = (splits[i]).toFloat();
       //     //                  }
       //     //                  ////获取旋转角度
       //     //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
       //     //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //     //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
       //     //                  //获取坐标
       //     //                  float X1 = mat[12];
       //     //                  float Y1 = mat[13];
       //     //                  float Z1 = mat[14];
       //     //                  //获取颜色
       //     //                  float R = (float)boolEntity.getR() / 255;
       //     //                  float G = (float)boolEntity.getG() / 255;
       //     //                  float B = (float)boolEntity.getB() / 255;
       //     //                  float A = (float)boolEntity.getA() / 255;
       //     //                  int  EntityId1 = boolEntity.getBoolEntityId1();
       //     //                  int  EntityId2 = boolEntity.getBoolEntityId2();
       //     //                  glPushMatrix();
       //     //                  glColor4f(R, G, B, A);
       //     //                  drawIntersection(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
       //     //                  glPopMatrix();
       //     //              }
       //     //          }
       //     //      }
       //     //  }
       //        //glPopMatrix();
       // //}
       //         //glPopMatrix();
       //     }
       //}
       // else {
       //     QString  vs2 = modFile.gettransformMatrix2();
       //     QStringList vs2splits = vs2.split(",");
       //     float mat2[16];
       //     for (int i = 0; i < 16; i++)
       //     {
       //         mat2[i] = (vs2splits[i]).toFloat();
       //     }
       //     //获取旋转角度
       //     float RX2 = (atan2(mat2[9], mat2[10])) * PI / 180;
       //     float RY2 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
       //     float RZ2 = (atan2(mat2[4], mat2[0])) * PI / 180;
       //     ////获取坐标
       //     float X2 = mat2[12];
       //     float Y2 = mat2[13];
       //     float Z2 = mat2[14];
       //     QString  vs1 = modFile.gettransformMatrix1();
       //     QStringList vs1splits = vs1.split(",");
       //     float mat1[16];
       //     for (int i = 0; i < 16; i++)
       //     {
       //         mat1[i] = (vs1splits[i]).toFloat();
       //     }
       //     //获取旋转角度
       //     float   RX1 = (atan2(mat1[9], mat1[10])) * PI / 180;
       //     float RY1 = (atan2(-mat1[8], sqrt(pow(mat1[9], 8) + pow(mat1[10], 8)))) * PI / 180;
       //     float RZ1 = (atan2(mat1[4], mat1[0])) * PI / 180;
       //     //获取坐标
       //     float X1 = mat1[12];
       //     float Y1 = mat1[13];
       //     float Z1 = mat1[14];
       //     //glLoadName(i + 1);
       //    for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
       //         if (!simpleEntity.getGraphicElement().isNull()) {
       //             if (simpleEntity.getVisible() == ("true")) {
       //                 if (simpleEntity.getGraphicElement().nodeName() == ("TerminalBlock")) {
       //                     QDomElement n = simpleEntity.getGraphicElement().toElement();
       //                     QString  vs = simpleEntity.getTransformMatrix();
       //                     QStringList splits = vs.split(",");
       //                     float mat[16];
       //                     for (int i = 0; i < 16; i++)
       //                     {
       //                         mat[i] = (splits[i]).toFloat();
       //                     }
       //                     ////获取旋转角度
       //                     float rX = (atan2(mat[9], mat[10])) * PI / 180;
       //                     float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //                     float rZ = (atan2(mat[4], mat[0])) * PI / 180;
       //                     //获取坐标
       //                     float X = mat[12];
       //                     float Y = mat[13];
       //                     float Z = mat[14];
       //                     //获取颜色
       //                     float R = (float)simpleEntity.getR() / 255;
       //                     float G = (float)simpleEntity.getG() / 255;
       //                     float B = (float)simpleEntity.getB() / 255;
       //                     float A = (float)simpleEntity.getA() / 255;
       //                     //获取长宽高
       //                     float L = (n.attribute("L")).toFloat();
       //                     float W = (n.attribute("W")).toFloat();
       //                     float T = (n.attribute("T")).toFloat();
       //                     float CL = (n.attribute("CL")).toFloat();
       //                     float CS = (n.attribute("CS")).toFloat();
       //                     float RS = (n.attribute("RS")).toFloat();
       //                     float R1 = (n.attribute("R")).toFloat();
       //                     float CN = (n.attribute("CN")).toFloat();
       //                     float RN = (n.attribute("RN")).toFloat();
       //                     float BL = (n.attribute("BL")).toFloat();
       //                     //                  
       //                     glPushMatrix();
       //                     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       //                     glColor4f(R, G, B, A);
       //                     TerminalBlock2(L, W, T, CL, CS, RS, R1, CN, RN, BL, X, Y, Z, rX, rY, rZ, X2, Y2, Z2, RX2, RY2, RZ2, X1, Y1, Z1, RX1, RY1, RZ1);
       //                     glPopMatrix();
       //                 }
       //                 //if (simpleEntity.getGraphicElement().nodeName() == ("Rectangular fixed plate")) {
       //                 //    QDomElement n = simpleEntity.getGraphicElement().toElement();
       //                 //    QString  vs = simpleEntity.getTransformMatrix();
       //                 //    QStringList splits = vs.split(",");
       //                 //    float mat[16];
       //                 //    for (int i = 0; i < 16; i++)
       //                 //    {
       //                 //        mat[i] = (splits[i]).toFloat();
       //                 //    }
       //                 //    //获取旋转角度
       //                 //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
       //                 //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //                 //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
       //                 //    //获取坐标
       //                 //    float X = mat[12];
       //                 //    float Y = mat[13];
       //                 //    float Z = mat[14];
       //                 //    //获取颜色
       //                 //    float R = (float)simpleEntity.getR() / 255;
       //                 //    float G = (float)simpleEntity.getG() / 255;
       //                 //    float B = (float)simpleEntity.getB() / 255;
       //                 //    float A = (float)simpleEntity.getA() / 255;
       //                 //    //获取长宽高
       //                 //    float L = (n.attribute("L")).toFloat();
       //                 //    float W = (n.attribute("W")).toFloat();
       //                 //    float T = (n.attribute("T")).toFloat();
       //                 //    float CS = (n.attribute("CS")).toFloat();
       //                 //    float RS = (n.attribute("RS")).toFloat();
       //                 //    float CN = (n.attribute("CN")).toFloat();
       //                 //    float RN = (n.attribute("RN")).toFloat();
       //                 //    float MH = (n.attribute("MH")).toFloat();
       //                 //    float D = (n.attribute("D")).toFloat();
       //                 //    //
       //                 //    glPushMatrix();
       //                 //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       //                 //    glColor4f(R, G, B, A);
       //                 //    RectangularFixedPlate(L, W, T, CS, RS, CN, RN, MH, D, X, Y, Z, rX, rY, rZ);
       //                 //    glPopMatrix();
       //                 //}
       //                 //if (simpleEntity.getGraphicElement().nodeName() == ("Circular fixed plate")) {
       //                 //    QDomElement n = simpleEntity.getGraphicElement().toElement();
       //                 //    QString  vs = simpleEntity.getTransformMatrix();
       //                 //    QStringList splits = vs.split(",");
       //                 //    float mat[16];
       //                 //    for (int i = 0; i < 16; i++)
       //                 //    {
       //                 //        mat[i] = (splits[i]).toFloat();
       //                 //    }
       //                 //    ////获取旋转角度
       //                 //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
       //                 //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //                 //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
       //                 //    //获取坐标
       //                 //    float X = mat[12];
       //                 //    float Y = mat[13];
       //                 //    float Z = mat[14];
       //                 //    //获取颜色
       //                 //    float R = (float)simpleEntity.getR() / 255;
       //                 //    float G = (float)simpleEntity.getG() / 255;
       //                 //    float B = (float)simpleEntity.getB() / 255;
       //                 //    float A = (float)simpleEntity.getA() / 255;
       //                 //    //获取长宽高
       //                 //    float L = (n.attribute("L")).toFloat();
       //                 //    float W = (n.attribute("W")).toFloat();
       //                 //    float T = (n.attribute("T")).toFloat();
       //                 //    float CS = (n.attribute("CS")).toFloat();
       //                 //    float N = (n.attribute("N")).toFloat();
       //                 //    float MH = (n.attribute("MH")).toFloat();
       //                 //    float D = (n.attribute("D")).toFloat();
       //                 //    //
       //                 //    glPushMatrix();
       //                 //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       //                 //    glColor4f(R, G, B, A);
       //                 //    CircularFixedPlate(L, W, T, CS, N, MH, D, X, Y, Z, rX, rY, rZ);
       //                 //    glPopMatrix();
       //                 //}
       //             }
       //         }
       //         //for (BoolEntity boolEntity : modFile.getBoolEntities()) {
       //     //      if (!boolEntity.getBoolType().isNull()) {
       //     //          if (boolEntity.getVisible() == ("true")) {
       //     //              if (boolEntity.getBoolType() == ("Difference")) {
       //     //                  QString  vs = boolEntity.getTransformMatrix();
       //     //                  QStringList splits = vs.split(",");
       //     //                  float mat[16];
       //     //                  for (int i = 0; i < 16; i++)
       //     //                  {
       //     //                      mat[i] = (splits[i]).toFloat();
       //     //                  }
       //     //                  ////获取旋转角度
       //     //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
       //     //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //     //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
       //     //                  //获取坐标
       //     //                  float X1 = mat[12];
       //     //                  float Y1 = mat[13];
       //     //                  float Z1 = mat[14];
       //     //                  //获取颜色
       //     //                  float R = (float)boolEntity.getR() / 255;
       //     //                  float G = (float)boolEntity.getG() / 255;
       //     //                  float B = (float)boolEntity.getB() / 255;
       //     //                  float A = (float)boolEntity.getA() / 255;
       //     //                  int  EntityId1 = boolEntity.getBoolEntityId1();
       //     //                  int  EntityId2 = boolEntity.getBoolEntityId2();
       //     //                  glPushMatrix();
       //     //                  //glTranslatef(X1, Z1, Y1);
       //     //                  glColor4f(R, G, B, A);
       //     //                  drawDifference(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
       //     //                  glPopMatrix();
       //     //              }
       //     //              if (boolEntity.getBoolType() == ("Union")) {
       //     //                  QString  vs = boolEntity.getTransformMatrix();
       //     //                  QStringList splits = vs.split(",");
       //     //                  float mat[16];
       //     //                  for (int i = 0; i < 16; i++)
       //     //                  {
       //     //                      mat[i] = (splits[i]).toFloat();
       //     //                  }
       //     //                  //获取旋转角度
       //     //                  float rX = (atan2(mat[9], mat[10])) * PI / 180;
       //     //                  float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //     //                  float rZ = (atan2(mat[4], mat[0])) * PI / 180;
       //     //                  //获取坐标
       //     //                  float X1 = mat[12];
       //     //                  float Y1 = mat[13];
       //     //                  float Z1 = mat[14];
       //     //                  //获取颜色
       //     //                  float R = (float)boolEntity.getR() / 255;
       //     //                  float G = (float)boolEntity.getG() / 255;
       //     //                  float B = (float)boolEntity.getB() / 255;
       //     //                  float A = (float)boolEntity.getA() / 255;
       //     //                  int  EntityId1 = boolEntity.getBoolEntityId1();
       //     //                  int  EntityId2 = boolEntity.getBoolEntityId2();
       //     //                  glPushMatrix();
       //     //                  glColor4f(R, G, B, A);
       //     //                  draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
       //     //                  draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
       //     //                  glPopMatrix();
       //     //              }
       //     //              if (boolEntity.getBoolType() == ("Intersection")) {
       //     //                  QString  vs = boolEntity.getTransformMatrix();
       //     //                  QStringList splits = vs.split(",");
       //     //                  float mat[16];
       //     //                  for (int i = 0; i < 16; i++)
       //     //                  {
       //     //                      mat[i] = (splits[i]).toFloat();
       //     //                  }
       //     //                  ////获取旋转角度
       //     //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
       //     //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
       //     //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
       //     //                  //获取坐标
       //     //                  float X1 = mat[12];
       //     //                  float Y1 = mat[13];
       //     //                  float Z1 = mat[14];
       //     //                  //获取颜色
       //     //                  float R = (float)boolEntity.getR() / 255;
       //     //                  float G = (float)boolEntity.getG() / 255;
       //     //                  float B = (float)boolEntity.getB() / 255;
       //     //                  float A = (float)boolEntity.getA() / 255;
       //     //                  int  EntityId1 = boolEntity.getBoolEntityId1();
       //     //                  int  EntityId2 = boolEntity.getBoolEntityId2();
       //     //                  glPushMatrix();
       //     //                  glColor4f(R, G, B, A);
       //     //                  drawIntersection(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
       //     //                  glPopMatrix();
       //     //              }
       //     //          }
       //     //      }
       //     //  }
       //        //glPopMatrix();
       // //}
       //         //glPopMatrix();
       //     }
       //}

    }
       //glPopMatrix();



}
void myopengl::list2()
{
   
        //glPushMatrix();
        for (int i = 0; i < gimModFileList.size(); i++) {

         if (!glIsList((GLuint)(gimModFileList.size() + i + 1))) {
            glNewList(gimModFileList.size() + i + 1, GL_COMPILE);
            ModFile modFile = gimModFileList[i];
            if (modFile.gettransformMatrix1().isEmpty())
            {
                QString  vs2 = modFile.gettransformMatrix2();
                QStringList vs2splits = vs2.split(",");
                float mat2[16];
                for (int i = 0; i < 16; i++)
                {
                    mat2[i] = (vs2splits[i]).toFloat();
                }
                //获取旋转角度
                float RX2 = (atan2(mat2[9], mat2[10])) * PI / 180;
                float RY2 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
                float RZ2 = (atan2(mat2[4], mat2[0])) * PI / 180;
                ////获取坐标
                float X2 = mat2[12];
                float Y2 = mat2[13];
                float Z2 = mat2[14];
                glPushMatrix();
                glTranslatef(X2, Z2, Y2);
                glRotatef(RX2, 1, 0, 0);
                glRotatef(RY2, 0, 1, 0);
                glRotatef(RZ2, 0, 0, 1);
                glPushMatrix();
            
            for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
                if (!simpleEntity.getGraphicElement().isNull()) {
                    if (simpleEntity.getVisible() == ("true")) {
                        if (simpleEntity.getGraphicElement().nodeName() == ("Cuboid")) {

                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            //绘制线框
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Cuboid(L, W, H);
                            glPopMatrix();
                            //绘制实体
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            Cuboid(L, W, H);
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Sphere")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float R1 = (n.attribute("R")).toFloat();
                            //绘制线框
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Sphere(R1);
                            glPopMatrix();
                            //绘制实体
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            Sphere(R1);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("RotationalEllipsoid")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                          /*  float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float LR = (n.attribute("LR")).toFloat();
                            float WR = (n.attribute("WR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            RotationalEllipsoid(LR, WR, H);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            RotationalEllipsoid(LR, WR, H);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Table")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float TL1 = (n.attribute("TL1")).toFloat();
                            float TL2 = (n.attribute("TL2")).toFloat();
                            float LL1 = (n.attribute("LL1")).toFloat();
                            float LL2 = (n.attribute("LL2")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            Table(TL1, TL2, LL1, LL2, H);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Table(TL1, TL2, LL1, LL2, H);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("OffsetRectangularTable")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float TL = (n.attribute("TL")).toFloat();
                            float TW = (n.attribute("TW")).toFloat();
                            float LL = (n.attribute("LL")).toFloat();
                            float LW = (n.attribute("LW")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float XOFF = (n.attribute("XOFF")).toFloat();
                            float YOFF = (n.attribute("YOFF")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Cylinder")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float R1 = (n.attribute("R")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Cylinder(R1, H);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            Cylinder(R1, H);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("TruncatedCone")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                           /* float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float TR = (n.attribute("TR")).toFloat();
                            float BR = (n.attribute("BR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            TruncatedCone(TR, BR, H);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            TruncatedCone(TR, BR, H);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("EccentricTruncatedCone")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高
                            float TR = (n.attribute("TR")).toFloat();
                            float BR = (n.attribute("BR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float TOPXOFF = (n.attribute("TOPXOFF")).toFloat();
                            float TOPYOFF = (n.attribute("TOPYOFF")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Ring")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float DR = (n.attribute("DR")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Ring(DR, R1, Rad);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            Ring(DR, R1, Rad);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("RectangularRing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                           /* float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float DR = (n.attribute("DR")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            RectangularRing(DR, R1, L, W);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            RectangularRing(DR, R1, L, W);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("EllipticRing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float DR = (n.attribute("DR")).toFloat();
                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            EllipticRing(DR, L, W);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            EllipticRing(DR, L, W);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("CircularGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float OR = (n.attribute("OR")).toFloat();
                            float IR = (n.attribute("IR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            CircularGasket(OR, IR, H, Rad);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            CircularGasket(OR, IR, H, Rad);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("TableGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float TR = (n.attribute("TR")).toFloat();
                            float OR = (n.attribute("OR")).toFloat();
                            float IR = (n.attribute("IR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            TableGasket(TR, OR, IR, H, Rad);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            TableGasket(TR, OR, IR, H, Rad);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("SquareGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float L1 = (n.attribute("L1")).toFloat();
                            float W1 = (n.attribute("W1")).toFloat();
                            float L2 = (n.attribute("L2")).toFloat();
                            float W2 = (n.attribute("W2")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float CT = (n.attribute("CT")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();
                            float CL = (n.attribute("CL")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("PorcelainBushing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                           /* float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float H = (n.attribute("H")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float R2 = (n.attribute("R1")).toFloat();
                            float R3 = (n.attribute("R2")).toFloat();
                            float N = (n.attribute("N")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                           // PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                           // PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("ConePorcelainBushing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float H = (n.attribute("H")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float R2 = (n.attribute("R1")).toFloat();
                            float R3 = (n.attribute("R2")).toFloat();
                            float N = (n.attribute("N")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Insulator")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                            /*float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高
                            float N = (n.attribute("N")).toFloat();
                            float D = (n.attribute("D")).toFloat();
                            float N1 = (n.attribute("N1")).toFloat();
                            float H1 = (n.attribute("H1")).toFloat();
                            float R1 = (n.attribute("R1")).toFloat();
                            float R2 = (n.attribute("R2")).toFloat();
                            float R3 = (n.attribute("R")).toFloat();
                            //float FL = (n.attribute("FL")).toFloat();
                            //float AL = (n.attribute("AL")).toFloat();
                            //float LN = (n.attribute("LN")).toFloat();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Insulator(N, D, N1, H1, R1, R2, R3);
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            Insulator(N, D, N1, H1, R1, R2, R3);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("StretchedBody")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                          /*  float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            float L = (n.attribute("L")).toFloat();
                            QString Normal = n.attribute("Normal");
                            QString Array = n.attribute("Array");
                            //绘制线框
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            StretchedBody(Normal, Array, L);
                            glPopMatrix();

                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0,1, 1,1);
                            StretchedBody(Normal, Array, L);
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Wire")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                           /* float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            QString  StartVector = n.attribute("StartVector");
                            QString  EndVector = n.attribute("EndVector");
                            QString  FitCoordArray = n.attribute("FitCoordArray");
                            QString  StartCoord = n.attribute("StartCoord");
                            QString  EndCoord = n.attribute("EndCoord");
                            float D = (n.attribute("D")).toFloat();
                            float Sag = (n.attribute("D")).toFloat();
                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Y, Z);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 0, 0, 1);
                            //Wire(StartVector, EndVector, FitCoordArray, StartCoord, EndCoord, D, Sag);
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Y, Z);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            //Wire(StartVector, EndVector, FitCoordArray, StartCoord, EndCoord, D, Sag);
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Cable")) {

                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                           /* float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/

                            QString  InflectionCoordArray = n.attribute("InflectionCoordArray");
                            QString  StartCoord = n.attribute("StartCoord");
                            QString  EndCoord = n.attribute("EndCoord");
                            float IRArray = (n.attribute("IRArray")).toFloat();
                            float D = (n.attribute("D")).toFloat();

                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Cable(InflectionCoordArray, StartCoord, EndCoord, D, IRArray);
                            glPopMatrix();

                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            glColor4f(0, 1, 1, 1);
                            Cable(InflectionCoordArray, StartCoord, EndCoord, D, IRArray);
                            glPopMatrix();
                        }
                    }
                }
            }
            glPopMatrix();
            glPopMatrix();
           

        }
            else {
         QString  vs2 = modFile.gettransformMatrix2();
         QStringList vs2splits = vs2.split(",");
         float mat2[16];
         for (int i = 0; i < 16; i++)
         {
             mat2[i] = (vs2splits[i]).toFloat();
         }
         //获取旋转角度
         float RX2 = (atan2(mat2[9], mat2[10])) * PI / 180;
         float RY2 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
         float RZ2 = (atan2(mat2[4], mat2[0])) * PI / 180;
         ////获取坐标
         float X2 = mat2[12];
         float Y2 = mat2[13];
         float Z2 = mat2[14];
         glPushMatrix();
         glTranslatef(X2, Z2, Y2);
         glRotatef(RX2, 1, 0, 0);
         glRotatef(RY2, 0, 1, 0);
         glRotatef(RZ2, 0, 0, 1);

         glPushMatrix();
         QString  vs1 = modFile.gettransformMatrix1();
         QStringList vs1splits = vs1.split(",");
         float mat1[16];
         for (int i = 0; i < 16; i++)
         {
             mat1[i] = (vs1splits[i]).toFloat();
         }
         //获取旋转角度
         float   RX = (atan2(mat1[9], mat1[10])) * PI / 180;
         float RY = (atan2(-mat1[8], sqrt(pow(mat1[9], 8) + pow(mat1[10], 8)))) * PI / 180;
         float RZ = (atan2(mat1[4], mat1[0])) * PI / 180;
         //获取坐标
         float X1 = mat1[12];
         float Y1 = mat1[13];
         float Z1 = mat1[14];
         //glLoadName(i + 1);

         glTranslatef(X1, Z1, Y1);
         glRotatef(RX, 1, 0, 0);
         glRotatef(RY, 0, 1, 0);
         glRotatef(RZ, 0, 0, 1);
         glPushMatrix();
         for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
             if (!simpleEntity.getGraphicElement().isNull()) {
                 if (simpleEntity.getVisible() == ("true")) {
                     if (simpleEntity.getGraphicElement().nodeName() == ("Cuboid")) {

                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         //获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float L = (n.attribute("L")).toFloat();
                         float W = (n.attribute("W")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         //绘制线框
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         Cuboid(L, W, H);
                         glPopMatrix();
                         //绘制实体
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         Cuboid(L, W, H);
                         glPopMatrix();

                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("Sphere")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float R1 = (n.attribute("R")).toFloat();
                         //绘制线框
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         Sphere(R1);
                         glPopMatrix();
                         //绘制实体
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         Sphere(R1);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("RotationalEllipsoid")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         //获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                       /*  float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float LR = (n.attribute("LR")).toFloat();
                         float WR = (n.attribute("WR")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         RotationalEllipsoid(LR, WR, H);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         RotationalEllipsoid(LR, WR, H);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("Table")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         //获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float TL1 = (n.attribute("TL1")).toFloat();
                         float TL2 = (n.attribute("TL2")).toFloat();
                         float LL1 = (n.attribute("LL1")).toFloat();
                         float LL2 = (n.attribute("LL2")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         Table(TL1, TL2, LL1, LL2, H);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         Table(TL1, TL2, LL1, LL2, H);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("OffsetRectangularTable")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float TL = (n.attribute("TL")).toFloat();
                         float TW = (n.attribute("TW")).toFloat();
                         float LL = (n.attribute("LL")).toFloat();
                         float LW = (n.attribute("LW")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         float XOFF = (n.attribute("XOFF")).toFloat();
                         float YOFF = (n.attribute("YOFF")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("Cylinder")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float R1 = (n.attribute("R")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         Cylinder(R1, H);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         Cylinder(R1, H);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("TruncatedCone")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                        /* float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float TR = (n.attribute("TR")).toFloat();
                         float BR = (n.attribute("BR")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         TruncatedCone(TR, BR, H);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         TruncatedCone(TR, BR, H);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("EccentricTruncatedCone")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         //float R = (float)simpleEntity.getR() / 255;
                         //float G = (float)simpleEntity.getG() / 255;
                         //float B = (float)simpleEntity.getB() / 255;
                         //float A = (float)simpleEntity.getA() / 255;
                         //获取长宽高
                         float TR = (n.attribute("TR")).toFloat();
                         float BR = (n.attribute("BR")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         float TOPXOFF = (n.attribute("TOPXOFF")).toFloat();
                         float TOPYOFF = (n.attribute("TOPYOFF")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("Ring")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float DR = (n.attribute("DR")).toFloat();
                         float R1 = (n.attribute("R")).toFloat();
                         float Rad = (n.attribute("Rad")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         Ring(DR, R1, Rad);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         Ring(DR, R1, Rad);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("RectangularRing")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                        /* float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float DR = (n.attribute("DR")).toFloat();
                         float R1 = (n.attribute("R")).toFloat();
                         float L = (n.attribute("L")).toFloat();
                         float W = (n.attribute("W")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         RectangularRing(DR, R1, L, W);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         RectangularRing(DR, R1, L, W);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("EllipticRing")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float DR = (n.attribute("DR")).toFloat();
                         float L = (n.attribute("L")).toFloat();
                         float W = (n.attribute("W")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         EllipticRing(DR, L, W);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         EllipticRing(DR, L, W);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("CircularGasket")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         //获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float OR = (n.attribute("OR")).toFloat();
                         float IR = (n.attribute("IR")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         float Rad = (n.attribute("Rad")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         CircularGasket(OR, IR, H, Rad);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         CircularGasket(OR, IR, H, Rad);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("TableGasket")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float TR = (n.attribute("TR")).toFloat();
                         float OR = (n.attribute("OR")).toFloat();
                         float IR = (n.attribute("IR")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         float Rad = (n.attribute("Rad")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         TableGasket(TR, OR, IR, H, Rad);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         TableGasket(TR, OR, IR, H, Rad);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("SquareGasket")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float L1 = (n.attribute("L1")).toFloat();
                         float W1 = (n.attribute("W1")).toFloat();
                         float L2 = (n.attribute("L2")).toFloat();
                         float W2 = (n.attribute("W2")).toFloat();
                         float H = (n.attribute("H")).toFloat();
                         float CT = (n.attribute("CT")).toFloat();
                         float Rad = (n.attribute("Rad")).toFloat();
                         float CL = (n.attribute("CL")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("PorcelainBushing")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         ////获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                        /* float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float H = (n.attribute("H")).toFloat();
                         float R1 = (n.attribute("R")).toFloat();
                         float R2 = (n.attribute("R1")).toFloat();
                         float R3 = (n.attribute("R2")).toFloat();
                         float N = (n.attribute("N")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         //PorcelainBushing(H, R1, R2, R3, N);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         //PorcelainBushing(H, R1, R2, R3, N);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("ConePorcelainBushing")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         //获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float H = (n.attribute("H")).toFloat();
                         float R1 = (n.attribute("R")).toFloat();
                         float R2 = (n.attribute("R1")).toFloat();
                         float R3 = (n.attribute("R2")).toFloat();
                         float N = (n.attribute("N")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         PorcelainBushing(H, R1, R2, R3, N);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         PorcelainBushing(H, R1, R2, R3, N);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("Insulator")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         //获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                         /*float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         //获取长宽高
                         float N = (n.attribute("N")).toFloat();
                         float D = (n.attribute("D")).toFloat();
                         float N1 = (n.attribute("N1")).toFloat();
                         float H1 = (n.attribute("H1")).toFloat();
                         float R1 = (n.attribute("R1")).toFloat();
                         float R2 = (n.attribute("R2")).toFloat();
                         float R3 = (n.attribute("R")).toFloat();
                         //float FL = (n.attribute("FL")).toFloat();
                         //float AL = (n.attribute("AL")).toFloat();
                         //float LN = (n.attribute("LN")).toFloat();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         Insulator(N, D, N1, H1, R1, R2, R3);
                         glPopMatrix();
                         //
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         Insulator(N, D, N1, H1, R1, R2, R3);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("StretchedBody")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         //获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                       /*  float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         float L = (n.attribute("L")).toFloat();
                         QString Normal = n.attribute("Normal");
                         QString Array = n.attribute("Array");
                         //绘制线框
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         StretchedBody(Normal, Array, L);
                         glPopMatrix();

                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         StretchedBody(Normal, Array, L);
                         glPopMatrix();

                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("Wire")) {
                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         //获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                        /* float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/
                         QString  StartVector = n.attribute("StartVector");
                         QString  EndVector = n.attribute("EndVector");
                         QString  FitCoordArray = n.attribute("FitCoordArray");
                         QString  StartCoord = n.attribute("StartCoord");
                         QString  EndCoord = n.attribute("EndCoord");
                         float D = (n.attribute("D")).toFloat();
                         float Sag = (n.attribute("D")).toFloat();
                         //1
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Y, Z);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 0, 0, 1);
                         //Wire(StartVector, EndVector, FitCoordArray, StartCoord, EndCoord, D, Sag);
                         glPopMatrix();
                         //2
                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Y, Z);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         //Wire(StartVector, EndVector, FitCoordArray, StartCoord, EndCoord, D, Sag);
                         glPopMatrix();
                     }
                     if (simpleEntity.getGraphicElement().nodeName() == ("Cable")) {

                         QDomElement n = simpleEntity.getGraphicElement().toElement();
                         QString  vs = simpleEntity.getTransformMatrix();
                         QStringList splits = vs.split(",");
                         float mat[16];
                         for (int i = 0; i < 16; i++)
                         {
                             mat[i] = (splits[i]).toFloat();
                         }
                         //获取旋转角度
                         float rX = (atan2(mat[9], mat[10])) * PI / 180;
                         float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                         float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                         //获取坐标
                         float X = mat[12];
                         float Y = mat[13];
                         float Z = mat[14];
                         //获取颜色
                        /* float R = (float)simpleEntity.getR() / 255;
                         float G = (float)simpleEntity.getG() / 255;
                         float B = (float)simpleEntity.getB() / 255;
                         float A = (float)simpleEntity.getA() / 255;*/

                         QString  InflectionCoordArray = n.attribute("InflectionCoordArray");
                         QString  StartCoord = n.attribute("StartCoord");
                         QString  EndCoord = n.attribute("EndCoord");
                         float IRArray = (n.attribute("IRArray")).toFloat();
                         float D = (n.attribute("D")).toFloat();

                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                         Cable(InflectionCoordArray, StartCoord, EndCoord, D, IRArray);
                         glPopMatrix();

                         glPushMatrix();
                         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                         glTranslatef(X, Z, Y);
                         glRotatef(rX, 1, 0, 0);
                         glRotatef(rY, 0, 1, 0);
                         glRotatef(rZ, 0, 0, 1);
                         glColor4f(0, 1, 1, 1);
                         Cable(InflectionCoordArray, StartCoord, EndCoord, D, IRArray);
                         glPopMatrix();
                     }
                 }
             }
         }
         glPopMatrix();
         glPopMatrix();
         glPopMatrix();
          }
            glEndList();
       
        }

        glCallList(gimModFileList.size() + i + 1);

        //ModFile modFile = gimModFileList[i];
        //if (modFile.gettransformMatrix1().isEmpty())
        //{
        //    QString  vs2 = modFile.gettransformMatrix2();
        //    QStringList vs2splits = vs2.split(",");
        //    float mat2[16];
        //    for (int i = 0; i < 16; i++)
        //    {
        //        mat2[i] = (vs2splits[i]).toFloat();
        //    }
        //    //获取旋转角度
        //    float RX2 = (atan2(mat2[9], mat2[10])) * PI / 180;
        //    float RY2 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
        //    float RZ2 = (atan2(mat2[4], mat2[0])) * PI / 180;
        //    ////获取坐标
        //    float X2 = mat2[12];
        //    float Y2 = mat2[13];
        //    float Z2 = mat2[14];
        //    for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
        //        if (!simpleEntity.getGraphicElement().isNull()) {
        //            if (simpleEntity.getVisible() == ("true")) {
        //                if (simpleEntity.getGraphicElement().nodeName() == ("TerminalBlock")) {
        //                    QDomElement n = simpleEntity.getGraphicElement().toElement();
        //                    QString  vs = simpleEntity.getTransformMatrix();
        //                    QStringList splits = vs.split(",");
        //                    float mat[16];
        //                    for (int i = 0; i < 16; i++)
        //                    {
        //                        mat[i] = (splits[i]).toFloat();
        //                    }
        //                    ////获取旋转角度
        //                    float rX = (atan2(mat[9], mat[10])) * PI / 180;
        //                    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //                    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
        //                    //获取坐标
        //                    float X = mat[12];
        //                    float Y = mat[13];
        //                    float Z = mat[14];
        //                    //获取颜色
        //                    float R = (float)simpleEntity.getR() / 255;
        //                    float G = (float)simpleEntity.getG() / 255;
        //                    float B = (float)simpleEntity.getB() / 255;
        //                    float A = (float)simpleEntity.getA() / 255;
        //                    //获取长宽高
        //                    float L = (n.attribute("L")).toFloat();
        //                    float W = (n.attribute("W")).toFloat();
        //                    float T = (n.attribute("T")).toFloat();
        //                    float CL = (n.attribute("CL")).toFloat();
        //                    float CS = (n.attribute("CS")).toFloat();
        //                    float RS = (n.attribute("RS")).toFloat();
        //                    float R1 = (n.attribute("R")).toFloat();
        //                    float CN = (n.attribute("CN")).toFloat();
        //                    float RN = (n.attribute("RN")).toFloat();
        //                    float BL = (n.attribute("BL")).toFloat();
        //                    //                  
        //                    glPushMatrix();
        //                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //                    glColor4f(0, 1, 1, 1);
        //                    TerminalBlock1(L, W, T, CL, CS, RS, R1, CN, RN, BL, X, Y, Z, rX, rY, rZ, X2, Y2, Z2, RX2, RY2, RZ2);
        //                    glPopMatrix();
        //                }
        //                //if (simpleEntity.getGraphicElement().nodeName() == ("Rectangular fixed plate")) {
        //                //    QDomElement n = simpleEntity.getGraphicElement().toElement();
        //                //    QString  vs = simpleEntity.getTransformMatrix();
        //                //    QStringList splits = vs.split(",");
        //                //    float mat[16];
        //                //    for (int i = 0; i < 16; i++)
        //                //    {
        //                //        mat[i] = (splits[i]).toFloat();
        //                //    }
        //                //    //获取旋转角度
        //                //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
        //                //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //                //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
        //                //    //获取坐标
        //                //    float X = mat[12];
        //                //    float Y = mat[13];
        //                //    float Z = mat[14];
        //                //    //获取颜色
        //                //    float R = (float)simpleEntity.getR() / 255;
        //                //    float G = (float)simpleEntity.getG() / 255;
        //                //    float B = (float)simpleEntity.getB() / 255;
        //                //    float A = (float)simpleEntity.getA() / 255;
        //                //    //获取长宽高
        //                //    float L = (n.attribute("L")).toFloat();
        //                //    float W = (n.attribute("W")).toFloat();
        //                //    float T = (n.attribute("T")).toFloat();
        //                //    float CS = (n.attribute("CS")).toFloat();
        //                //    float RS = (n.attribute("RS")).toFloat();
        //                //    float CN = (n.attribute("CN")).toFloat();
        //                //    float RN = (n.attribute("RN")).toFloat();
        //                //    float MH = (n.attribute("MH")).toFloat();
        //                //    float D = (n.attribute("D")).toFloat();
        //                //    //
        //                //    glPushMatrix();
        //                //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //                //    glColor4f(R, G, B, A);
        //                //    RectangularFixedPlate(L, W, T, CS, RS, CN, RN, MH, D, X, Y, Z, rX, rY, rZ);
        //                //    glPopMatrix();
        //                //}
        //                //if (simpleEntity.getGraphicElement().nodeName() == ("Circular fixed plate")) {
        //                //    QDomElement n = simpleEntity.getGraphicElement().toElement();
        //                //    QString  vs = simpleEntity.getTransformMatrix();
        //                //    QStringList splits = vs.split(",");
        //                //    float mat[16];
        //                //    for (int i = 0; i < 16; i++)
        //                //    {
        //                //        mat[i] = (splits[i]).toFloat();
        //                //    }
        //                //    ////获取旋转角度
        //                //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
        //                //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //                //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
        //                //    //获取坐标
        //                //    float X = mat[12];
        //                //    float Y = mat[13];
        //                //    float Z = mat[14];
        //                //    //获取颜色
        //                //    float R = (float)simpleEntity.getR() / 255;
        //                //    float G = (float)simpleEntity.getG() / 255;
        //                //    float B = (float)simpleEntity.getB() / 255;
        //                //    float A = (float)simpleEntity.getA() / 255;
        //                //    //获取长宽高
        //                //    float L = (n.attribute("L")).toFloat();
        //                //    float W = (n.attribute("W")).toFloat();
        //                //    float T = (n.attribute("T")).toFloat();
        //                //    float CS = (n.attribute("CS")).toFloat();
        //                //    float N = (n.attribute("N")).toFloat();
        //                //    float MH = (n.attribute("MH")).toFloat();
        //                //    float D = (n.attribute("D")).toFloat();
        //                //    //
        //                //    glPushMatrix();
        //                //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //                //    glColor4f(R, G, B, A);
        //                //    CircularFixedPlate(L, W, T, CS, N, MH, D, X, Y, Z, rX, rY, rZ);
        //                //    glPopMatrix();
        //                //}
        //            }
        //        }
        //        //for (BoolEntity boolEntity : modFile.getBoolEntities()) {
        //    //      if (!boolEntity.getBoolType().isNull()) {
        //    //          if (boolEntity.getVisible() == ("true")) {
        //    //              if (boolEntity.getBoolType() == ("Difference")) {
        //    //                  QString  vs = boolEntity.getTransformMatrix();
        //    //                  QStringList splits = vs.split(",");
        //    //                  float mat[16];
        //    //                  for (int i = 0; i < 16; i++)
        //    //                  {
        //    //                      mat[i] = (splits[i]).toFloat();
        //    //                  }
        //    //                  ////获取旋转角度
        //    //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
        //    //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //    //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
        //    //                  //获取坐标
        //    //                  float X1 = mat[12];
        //    //                  float Y1 = mat[13];
        //    //                  float Z1 = mat[14];
        //    //                  //获取颜色
        //    //                  float R = (float)boolEntity.getR() / 255;
        //    //                  float G = (float)boolEntity.getG() / 255;
        //    //                  float B = (float)boolEntity.getB() / 255;
        //    //                  float A = (float)boolEntity.getA() / 255;
        //    //                  int  EntityId1 = boolEntity.getBoolEntityId1();
        //    //                  int  EntityId2 = boolEntity.getBoolEntityId2();
        //    //                  glPushMatrix();
        //    //                  //glTranslatef(X1, Z1, Y1);
        //    //                  glColor4f(R, G, B, A);
        //    //                  drawDifference(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
        //    //                  glPopMatrix();
        //    //              }
        //    //              if (boolEntity.getBoolType() == ("Union")) {
        //    //                  QString  vs = boolEntity.getTransformMatrix();
        //    //                  QStringList splits = vs.split(",");
        //    //                  float mat[16];
        //    //                  for (int i = 0; i < 16; i++)
        //    //                  {
        //    //                      mat[i] = (splits[i]).toFloat();
        //    //                  }
        //    //                  //获取旋转角度
        //    //                  float rX = (atan2(mat[9], mat[10])) * PI / 180;
        //    //                  float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //    //                  float rZ = (atan2(mat[4], mat[0])) * PI / 180;
        //    //                  //获取坐标
        //    //                  float X1 = mat[12];
        //    //                  float Y1 = mat[13];
        //    //                  float Z1 = mat[14];
        //    //                  //获取颜色
        //    //                  float R = (float)boolEntity.getR() / 255;
        //    //                  float G = (float)boolEntity.getG() / 255;
        //    //                  float B = (float)boolEntity.getB() / 255;
        //    //                  float A = (float)boolEntity.getA() / 255;
        //    //                  int  EntityId1 = boolEntity.getBoolEntityId1();
        //    //                  int  EntityId2 = boolEntity.getBoolEntityId2();
        //    //                  glPushMatrix();
        //    //                  glColor4f(R, G, B, A);
        //    //                  draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
        //    //                  draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
        //    //                  glPopMatrix();
        //    //              }
        //    //              if (boolEntity.getBoolType() == ("Intersection")) {
        //    //                  QString  vs = boolEntity.getTransformMatrix();
        //    //                  QStringList splits = vs.split(",");
        //    //                  float mat[16];
        //    //                  for (int i = 0; i < 16; i++)
        //    //                  {
        //    //                      mat[i] = (splits[i]).toFloat();
        //    //                  }
        //    //                  ////获取旋转角度
        //    //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
        //    //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //    //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
        //    //                  //获取坐标
        //    //                  float X1 = mat[12];
        //    //                  float Y1 = mat[13];
        //    //                  float Z1 = mat[14];
        //    //                  //获取颜色
        //    //                  float R = (float)boolEntity.getR() / 255;
        //    //                  float G = (float)boolEntity.getG() / 255;
        //    //                  float B = (float)boolEntity.getB() / 255;
        //    //                  float A = (float)boolEntity.getA() / 255;
        //    //                  int  EntityId1 = boolEntity.getBoolEntityId1();
        //    //                  int  EntityId2 = boolEntity.getBoolEntityId2();
        //    //                  glPushMatrix();
        //    //                  glColor4f(R, G, B, A);
        //    //                  drawIntersection(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
        //    //                  glPopMatrix();
        //    //              }
        //    //          }
        //    //      }
        //    //  }
        //       //glPopMatrix();
        ////}
        //        //glPopMatrix();
        //    }
        //}
        //else {
        //    QString  vs2 = modFile.gettransformMatrix2();
        //    QStringList vs2splits = vs2.split(",");
        //    float mat2[16];
        //    for (int i = 0; i < 16; i++)
        //    {
        //        mat2[i] = (vs2splits[i]).toFloat();
        //    }
        //    //获取旋转角度
        //    float RX2 = (atan2(mat2[9], mat2[10])) * PI / 180;
        //    float RY2 = (atan2(-mat2[8], sqrt(pow(mat2[9], 8) + pow(mat2[10], 8)))) * PI / 180;
        //    float RZ2 = (atan2(mat2[4], mat2[0])) * PI / 180;
        //    ////获取坐标
        //    float X2 = mat2[12];
        //    float Y2 = mat2[13];
        //    float Z2 = mat2[14];
        //    QString  vs1 = modFile.gettransformMatrix1();
        //    QStringList vs1splits = vs1.split(",");
        //    float mat1[16];
        //    for (int i = 0; i < 16; i++)
        //    {
        //        mat1[i] = (vs1splits[i]).toFloat();
        //    }
        //    //获取旋转角度
        //    float   RX1 = (atan2(mat1[9], mat1[10])) * PI / 180;
        //    float RY1 = (atan2(-mat1[8], sqrt(pow(mat1[9], 8) + pow(mat1[10], 8)))) * PI / 180;
        //    float RZ1 = (atan2(mat1[4], mat1[0])) * PI / 180;
        //    //获取坐标
        //    float X1 = mat1[12];
        //    float Y1 = mat1[13];
        //    float Z1 = mat1[14];
        //    //glLoadName(i + 1);
        //    for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
        //        if (!simpleEntity.getGraphicElement().isNull()) {
        //            if (simpleEntity.getVisible() == ("true")) {
        //                if (simpleEntity.getGraphicElement().nodeName() == ("TerminalBlock")) {
        //                    QDomElement n = simpleEntity.getGraphicElement().toElement();
        //                    QString  vs = simpleEntity.getTransformMatrix();
        //                    QStringList splits = vs.split(",");
        //                    float mat[16];
        //                    for (int i = 0; i < 16; i++)
        //                    {
        //                        mat[i] = (splits[i]).toFloat();
        //                    }
        //                    ////获取旋转角度
        //                    float rX = (atan2(mat[9], mat[10])) * PI / 180;
        //                    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //                    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
        //                    //获取坐标
        //                    float X = mat[12];
        //                    float Y = mat[13];
        //                    float Z = mat[14];
        //                    //获取颜色
        //                    float R = (float)simpleEntity.getR() / 255;
        //                    float G = (float)simpleEntity.getG() / 255;
        //                    float B = (float)simpleEntity.getB() / 255;
        //                    float A = (float)simpleEntity.getA() / 255;
        //                    //获取长宽高
        //                    float L = (n.attribute("L")).toFloat();
        //                    float W = (n.attribute("W")).toFloat();
        //                    float T = (n.attribute("T")).toFloat();
        //                    float CL = (n.attribute("CL")).toFloat();
        //                    float CS = (n.attribute("CS")).toFloat();
        //                    float RS = (n.attribute("RS")).toFloat();
        //                    float R1 = (n.attribute("R")).toFloat();
        //                    float CN = (n.attribute("CN")).toFloat();
        //                    float RN = (n.attribute("RN")).toFloat();
        //                    float BL = (n.attribute("BL")).toFloat();
        //                    //                  
        //                    glPushMatrix();
        //                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //                    glColor4f(0, 1, 1, 1);
        //                    TerminalBlock2(L, W, T, CL, CS, RS, R1, CN, RN, BL, X, Y, Z, rX, rY, rZ, X2, Y2, Z2, RX2, RY2, RZ2, X1, Y1, Z1, RX1, RY1, RZ1);
        //                    glPopMatrix();
        //                }
        //                //if (simpleEntity.getGraphicElement().nodeName() == ("Rectangular fixed plate")) {
        //                //    QDomElement n = simpleEntity.getGraphicElement().toElement();
        //                //    QString  vs = simpleEntity.getTransformMatrix();
        //                //    QStringList splits = vs.split(",");
        //                //    float mat[16];
        //                //    for (int i = 0; i < 16; i++)
        //                //    {
        //                //        mat[i] = (splits[i]).toFloat();
        //                //    }
        //                //    //获取旋转角度
        //                //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
        //                //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //                //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
        //                //    //获取坐标
        //                //    float X = mat[12];
        //                //    float Y = mat[13];
        //                //    float Z = mat[14];
        //                //    //获取颜色
        //                //    float R = (float)simpleEntity.getR() / 255;
        //                //    float G = (float)simpleEntity.getG() / 255;
        //                //    float B = (float)simpleEntity.getB() / 255;
        //                //    float A = (float)simpleEntity.getA() / 255;
        //                //    //获取长宽高
        //                //    float L = (n.attribute("L")).toFloat();
        //                //    float W = (n.attribute("W")).toFloat();
        //                //    float T = (n.attribute("T")).toFloat();
        //                //    float CS = (n.attribute("CS")).toFloat();
        //                //    float RS = (n.attribute("RS")).toFloat();
        //                //    float CN = (n.attribute("CN")).toFloat();
        //                //    float RN = (n.attribute("RN")).toFloat();
        //                //    float MH = (n.attribute("MH")).toFloat();
        //                //    float D = (n.attribute("D")).toFloat();
        //                //    //
        //                //    glPushMatrix();
        //                //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //                //    glColor4f(R, G, B, A);
        //                //    RectangularFixedPlate(L, W, T, CS, RS, CN, RN, MH, D, X, Y, Z, rX, rY, rZ);
        //                //    glPopMatrix();
        //                //}
        //                //if (simpleEntity.getGraphicElement().nodeName() == ("Circular fixed plate")) {
        //                //    QDomElement n = simpleEntity.getGraphicElement().toElement();
        //                //    QString  vs = simpleEntity.getTransformMatrix();
        //                //    QStringList splits = vs.split(",");
        //                //    float mat[16];
        //                //    for (int i = 0; i < 16; i++)
        //                //    {
        //                //        mat[i] = (splits[i]).toFloat();
        //                //    }
        //                //    ////获取旋转角度
        //                //    float rX = (atan2(mat[9], mat[10])) * PI / 180;
        //                //    float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //                //    float rZ = (atan2(mat[4], mat[0])) * PI / 180;
        //                //    //获取坐标
        //                //    float X = mat[12];
        //                //    float Y = mat[13];
        //                //    float Z = mat[14];
        //                //    //获取颜色
        //                //    float R = (float)simpleEntity.getR() / 255;
        //                //    float G = (float)simpleEntity.getG() / 255;
        //                //    float B = (float)simpleEntity.getB() / 255;
        //                //    float A = (float)simpleEntity.getA() / 255;
        //                //    //获取长宽高
        //                //    float L = (n.attribute("L")).toFloat();
        //                //    float W = (n.attribute("W")).toFloat();
        //                //    float T = (n.attribute("T")).toFloat();
        //                //    float CS = (n.attribute("CS")).toFloat();
        //                //    float N = (n.attribute("N")).toFloat();
        //                //    float MH = (n.attribute("MH")).toFloat();
        //                //    float D = (n.attribute("D")).toFloat();
        //                //    //
        //                //    glPushMatrix();
        //                //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //                //    glColor4f(R, G, B, A);
        //                //    CircularFixedPlate(L, W, T, CS, N, MH, D, X, Y, Z, rX, rY, rZ);
        //                //    glPopMatrix();
        //                //}
        //            }
        //        }
        //        //for (BoolEntity boolEntity : modFile.getBoolEntities()) {
        //    //      if (!boolEntity.getBoolType().isNull()) {
        //    //          if (boolEntity.getVisible() == ("true")) {
        //    //              if (boolEntity.getBoolType() == ("Difference")) {
        //    //                  QString  vs = boolEntity.getTransformMatrix();
        //    //                  QStringList splits = vs.split(",");
        //    //                  float mat[16];
        //    //                  for (int i = 0; i < 16; i++)
        //    //                  {
        //    //                      mat[i] = (splits[i]).toFloat();
        //    //                  }
        //    //                  ////获取旋转角度
        //    //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
        //    //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //    //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
        //    //                  //获取坐标
        //    //                  float X1 = mat[12];
        //    //                  float Y1 = mat[13];
        //    //                  float Z1 = mat[14];
        //    //                  //获取颜色
        //    //                  float R = (float)boolEntity.getR() / 255;
        //    //                  float G = (float)boolEntity.getG() / 255;
        //    //                  float B = (float)boolEntity.getB() / 255;
        //    //                  float A = (float)boolEntity.getA() / 255;
        //    //                  int  EntityId1 = boolEntity.getBoolEntityId1();
        //    //                  int  EntityId2 = boolEntity.getBoolEntityId2();
        //    //                  glPushMatrix();
        //    //                  //glTranslatef(X1, Z1, Y1);
        //    //                  glColor4f(R, G, B, A);
        //    //                  drawDifference(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
        //    //                  glPopMatrix();
        //    //              }
        //    //              if (boolEntity.getBoolType() == ("Union")) {
        //    //                  QString  vs = boolEntity.getTransformMatrix();
        //    //                  QStringList splits = vs.split(",");
        //    //                  float mat[16];
        //    //                  for (int i = 0; i < 16; i++)
        //    //                  {
        //    //                      mat[i] = (splits[i]).toFloat();
        //    //                  }
        //    //                  //获取旋转角度
        //    //                  float rX = (atan2(mat[9], mat[10])) * PI / 180;
        //    //                  float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //    //                  float rZ = (atan2(mat[4], mat[0])) * PI / 180;
        //    //                  //获取坐标
        //    //                  float X1 = mat[12];
        //    //                  float Y1 = mat[13];
        //    //                  float Z1 = mat[14];
        //    //                  //获取颜色
        //    //                  float R = (float)boolEntity.getR() / 255;
        //    //                  float G = (float)boolEntity.getG() / 255;
        //    //                  float B = (float)boolEntity.getB() / 255;
        //    //                  float A = (float)boolEntity.getA() / 255;
        //    //                  int  EntityId1 = boolEntity.getBoolEntityId1();
        //    //                  int  EntityId2 = boolEntity.getBoolEntityId2();
        //    //                  glPushMatrix();
        //    //                  glColor4f(R, G, B, A);
        //    //                  draw(EntityId1, rX, rY, rZ, X1, Y1, Z1);
        //    //                  draw(EntityId2, rX, rY, rZ, X1, Y1, Z1);
        //    //                  glPopMatrix();
        //    //              }
        //    //              if (boolEntity.getBoolType() == ("Intersection")) {
        //    //                  QString  vs = boolEntity.getTransformMatrix();
        //    //                  QStringList splits = vs.split(",");
        //    //                  float mat[16];
        //    //                  for (int i = 0; i < 16; i++)
        //    //                  {
        //    //                      mat[i] = (splits[i]).toFloat();
        //    //                  }
        //    //                  ////获取旋转角度
        //    //                  float rX1 = (atan2(mat[9], mat[10])) * PI / 180;
        //    //                  float rY1 = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
        //    //                  float rZ1 = (atan2(mat[4], mat[0])) * PI / 180;
        //    //                  //获取坐标
        //    //                  float X1 = mat[12];
        //    //                  float Y1 = mat[13];
        //    //                  float Z1 = mat[14];
        //    //                  //获取颜色
        //    //                  float R = (float)boolEntity.getR() / 255;
        //    //                  float G = (float)boolEntity.getG() / 255;
        //    //                  float B = (float)boolEntity.getB() / 255;
        //    //                  float A = (float)boolEntity.getA() / 255;
        //    //                  int  EntityId1 = boolEntity.getBoolEntityId1();
        //    //                  int  EntityId2 = boolEntity.getBoolEntityId2();
        //    //                  glPushMatrix();
        //    //                  glColor4f(R, G, B, A);
        //    //                  drawIntersection(EntityId1, EntityId2, rX1, rY1, rZ1, X1, Y1, Z1);
        //    //                  glPopMatrix();
        //    //              }
        //    //          }
        //    //      }
        //    //  }
        //       //glPopMatrix();
        ////}
        //        //glPopMatrix();
        //    }
        //}




         }
        //glPopMatrix();
}
void myopengl::draw(int EntityId, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1)
{
    glPushMatrix();
    for (int i = 0; i < gimModFileList.size(); i++) {
        ModFile modFile = gimModFileList[i];
        for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
            if (!simpleEntity.getGraphicElement().isNull()) {
                if (simpleEntity.getVisible() != ("true")) {
                    if (simpleEntity.getEntityId() == EntityId) {
                        if ((simpleEntity.getGraphicElement().nodeName() == ("Cuboid"))) {
                            //qDebug()<<1111<<endl;
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];


                            //获取长宽高

                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();
                            float H = (n.attribute("H")).toFloat();


                            //绘制线框
                            /*glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);

                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            Cuboid(L, W, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();*/

                            //绘制实体
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            Cuboid(L, W, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Sphere")) {

                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float R1 = (n.attribute("R")).toFloat();


                            //GLuint id2 = glGenLists(1);
                           // glNewList(id2, GL_COMPILE);
                            //绘制线框
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Sphere(R1);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //绘制实体
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Sphere(R1);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("RotationalEllipsoid"))
                        {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            ////获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float LR = (n.attribute("LR")).toFloat();
                            float WR = (n.attribute("WR")).toFloat();
                            float H = (n.attribute("H")).toFloat();


                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            RotationalEllipsoid(LR, WR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            RotationalEllipsoid(LR, WR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Table")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            ////获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TL1 = (n.attribute("TL1")).toFloat();
                            float TL2 = (n.attribute("TL2")).toFloat();
                            float LL1 = (n.attribute("LL1")).toFloat();
                            float LL2 = (n.attribute("LL2")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Table(TL1, TL2, LL1, LL2, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Table(TL1, TL2, LL1, LL2, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("OffsetRectangularTable"))
                        {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            ////获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TL = (n.attribute("TL")).toFloat();
                            float TW = (n.attribute("TW")).toFloat();
                            float LL = (n.attribute("LL")).toFloat();
                            float LW = (n.attribute("LW")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float XOFF = (n.attribute("XOFF")).toFloat();
                            float YOFF = (n.attribute("YOFF")).toFloat();

                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            // glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Cylinder"))
                        {
                            //qDebug() << 2222 << endl;
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float R1 = (n.attribute("R")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Cylinder(R1, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Cylinder(R1, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("TruncatedCone")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TR = (n.attribute("TR")).toFloat();
                            float BR = (n.attribute("BR")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            /// glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            TruncatedCone(TR, BR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            TruncatedCone(TR, BR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("EccentricTruncatedCone")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TR = (n.attribute("TR")).toFloat();
                            float BR = (n.attribute("BR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float TOPXOFF = (n.attribute("TOPXOFF")).toFloat();
                            float TOPYOFF = (n.attribute("TOPYOFF")).toFloat();

                            ////1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            // glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Ring")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float DR = (n.attribute("DR")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();


                            ////1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Ring(DR, R1, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Ring(DR, R1, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("RectangularRing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float DR = (n.attribute("DR")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            RectangularRing(DR, R1, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            RectangularRing(DR, R1, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("EllipticRing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float DR = (n.attribute("DR")).toFloat();

                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            EllipticRing(DR, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            EllipticRing(DR, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("CircularGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float OR = (n.attribute("OR")).toFloat();
                            float IR = (n.attribute("IR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            CircularGasket(OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            CircularGasket(OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("TableGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TR = (n.attribute("TR")).toFloat();
                            float OR = (n.attribute("OR")).toFloat();
                            float IR = (n.attribute("IR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            TableGasket(TR, OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            TableGasket(TR, OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("SquareGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float L1 = (n.attribute("L1")).toFloat();
                            float W1 = (n.attribute("W1")).toFloat();
                            float L2 = (n.attribute("L2")).toFloat();
                            float W2 = (n.attribute("W2")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float CT = (n.attribute("CT")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();
                            float CL = (n.attribute("CL")).toFloat();


                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("PorcelainBushing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float H = (n.attribute("H")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float R2 = (n.attribute("R1")).toFloat();
                            float R3 = (n.attribute("R2")).toFloat();
                            float N = (n.attribute("N")).toFloat();



                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("ConePorcelainBushing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                           /* float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高

                            float H = (n.attribute("H")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float R2 = (n.attribute("R1")).toFloat();
                            float R3 = (n.attribute("R2")).toFloat();
                            float N = (n.attribute("N")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Insulator")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float N = (n.attribute("N")).toFloat();
                            float D = (n.attribute("D")).toFloat();
                            float N1 = (n.attribute("N1")).toFloat();
                            float H1 = (n.attribute("H1")).toFloat();
                            float R1 = (n.attribute("R1")).toFloat();
                            float R2 = (n.attribute("R2")).toFloat();
                            float R3 = (n.attribute("R")).toFloat();
                            //float FL = (n.attribute("FL")).toFloat();
                            //float AL = (n.attribute("AL")).toFloat();
                            //float LN = (n.attribute("LN")).toFloat();


                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Insulator(N, D, N1, H1, R1, R2, R3);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Insulator(N, D, N1, H1, R1, R2, R3);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                       
                    }
                }

            }
        }


    }
    glPopMatrix();
}
void myopengl::draw1(int EntityId, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3)
{
    glPushMatrix();
    for (int i = 0; i < gimModFileList.size(); i++) {
        ModFile modFile = gimModFileList[i];
        for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
            if (!simpleEntity.getGraphicElement().isNull()) {
                if (simpleEntity.getVisible() != ("true")) {
                    if (simpleEntity.getEntityId() == EntityId) {
                        if ((simpleEntity.getGraphicElement().nodeName() == ("Cuboid"))) {                            
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];


                            //获取长宽高

                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();
                            float H = (n.attribute("H")).toFloat();


                            //绘制线框
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);

                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            Cuboid(L, W, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                            //绘制实体
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            Cuboid(L, W, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Sphere")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float R1 = (n.attribute("R")).toFloat();
                             //绘制线框
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Sphere(R1);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //绘制实体
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Sphere(R1);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("RotationalEllipsoid"))
                        {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            ////获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float LR = (n.attribute("LR")).toFloat();
                            float WR = (n.attribute("WR")).toFloat();
                            float H = (n.attribute("H")).toFloat();


                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            RotationalEllipsoid(LR, WR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            RotationalEllipsoid(LR, WR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Table")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            ////获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TL1 = (n.attribute("TL1")).toFloat();
                            float TL2 = (n.attribute("TL2")).toFloat();
                            float LL1 = (n.attribute("LL1")).toFloat();
                            float LL2 = (n.attribute("LL2")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Table(TL1, TL2, LL1, LL2, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Table(TL1, TL2, LL1, LL2, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("OffsetRectangularTable"))
                        {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            ////获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TL = (n.attribute("TL")).toFloat();
                            float TW = (n.attribute("TW")).toFloat();
                            float LL = (n.attribute("LL")).toFloat();
                            float LW = (n.attribute("LW")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float XOFF = (n.attribute("XOFF")).toFloat();
                            float YOFF = (n.attribute("YOFF")).toFloat();

                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            // glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Cylinder"))
                        {
                            //qDebug() << 2222 << endl;
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float R1 = (n.attribute("R")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Cylinder(R1, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Cylinder(R1, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("TruncatedCone")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TR = (n.attribute("TR")).toFloat();
                            float BR = (n.attribute("BR")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            /// glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            TruncatedCone(TR, BR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            TruncatedCone(TR, BR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("EccentricTruncatedCone")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TR = (n.attribute("TR")).toFloat();
                            float BR = (n.attribute("BR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float TOPXOFF = (n.attribute("TOPXOFF")).toFloat();
                            float TOPYOFF = (n.attribute("TOPYOFF")).toFloat();

                            ////1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            // glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Ring")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float DR = (n.attribute("DR")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();


                            ////1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Ring(DR, R1, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Ring(DR, R1, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("RectangularRing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float DR = (n.attribute("DR")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            RectangularRing(DR, R1, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            RectangularRing(DR, R1, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("EllipticRing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float DR = (n.attribute("DR")).toFloat();

                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            EllipticRing(DR, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            EllipticRing(DR, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("CircularGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float OR = (n.attribute("OR")).toFloat();
                            float IR = (n.attribute("IR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            CircularGasket(OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            CircularGasket(OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("TableGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TR = (n.attribute("TR")).toFloat();
                            float OR = (n.attribute("OR")).toFloat();
                            float IR = (n.attribute("IR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            TableGasket(TR, OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            TableGasket(TR, OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("SquareGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float L1 = (n.attribute("L1")).toFloat();
                            float W1 = (n.attribute("W1")).toFloat();
                            float L2 = (n.attribute("L2")).toFloat();
                            float W2 = (n.attribute("W2")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float CT = (n.attribute("CT")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();
                            float CL = (n.attribute("CL")).toFloat();


                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("PorcelainBushing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float H = (n.attribute("H")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float R2 = (n.attribute("R1")).toFloat();
                            float R3 = (n.attribute("R2")).toFloat();
                            float N = (n.attribute("N")).toFloat();



                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("ConePorcelainBushing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                           /* float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高

                            float H = (n.attribute("H")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float R2 = (n.attribute("R1")).toFloat();
                            float R3 = (n.attribute("R2")).toFloat();
                            float N = (n.attribute("N")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Insulator")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float N = (n.attribute("N")).toFloat();
                            float D = (n.attribute("D")).toFloat();
                            float N1 = (n.attribute("N1")).toFloat();
                            float H1 = (n.attribute("H1")).toFloat();
                            float R1 = (n.attribute("R1")).toFloat();
                            float R2 = (n.attribute("R2")).toFloat();
                            float R3 = (n.attribute("R")).toFloat();
                            //float FL = (n.attribute("FL")).toFloat();
                            //float AL = (n.attribute("AL")).toFloat();
                            //float LN = (n.attribute("LN")).toFloat();


                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Insulator(N, D, N1, H1, R1, R2, R3);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Insulator(N, D, N1, H1, R1, R2, R3);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                     
                    }
                }

            }
        }


    }
    glPopMatrix();
}
void myopengl::draw2(int EntityId, GLfloat rX1, GLfloat rY1, GLfloat rZ1, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat X3, GLfloat Y3, GLfloat Z3, GLfloat RX3, GLfloat RY3, GLfloat RZ3, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat RX2, GLfloat RY2, GLfloat RZ2 )
{
    glPushMatrix();
    for (int i = 0; i < gimModFileList.size(); i++) {
        ModFile modFile = gimModFileList[i];
        for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
            if (!simpleEntity.getGraphicElement().isNull()) {
                if (simpleEntity.getVisible() != ("true")) {
                    if (simpleEntity.getEntityId() == EntityId) {
                        if ((simpleEntity.getGraphicElement().nodeName() == ("Cuboid"))) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            //获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];

                            //获取长宽高
                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //绘制线框
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            Cuboid(L, W, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                            //绘制实体
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            Cuboid(L, W, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Sphere")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float R1 = (n.attribute("R")).toFloat();
                            //绘制线框
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Sphere(R1);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //绘制实体
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Sphere(R1);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("RotationalEllipsoid"))
                        {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            ////获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float LR = (n.attribute("LR")).toFloat();
                            float WR = (n.attribute("WR")).toFloat();
                            float H = (n.attribute("H")).toFloat();


                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            RotationalEllipsoid(LR, WR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            RotationalEllipsoid(LR, WR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Table")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            ////获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TL1 = (n.attribute("TL1")).toFloat();
                            float TL2 = (n.attribute("TL2")).toFloat();
                            float LL1 = (n.attribute("LL1")).toFloat();
                            float LL2 = (n.attribute("LL2")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Table(TL1, TL2, LL1, LL2, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Table(TL1, TL2, LL1, LL2, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("OffsetRectangularTable"))
                        {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            ////获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TL = (n.attribute("TL")).toFloat();
                            float TW = (n.attribute("TW")).toFloat();
                            float LL = (n.attribute("LL")).toFloat();
                            float LW = (n.attribute("LW")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float XOFF = (n.attribute("XOFF")).toFloat();
                            float YOFF = (n.attribute("YOFF")).toFloat();

                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            // glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            OffsetRectangularTable(TL, TW, LL, LW, H, XOFF, YOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Cylinder"))
                        {
                            //qDebug() << 2222 << endl;
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float R1 = (n.attribute("R")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Cylinder(R1, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Cylinder(R1, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("TruncatedCone")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TR = (n.attribute("TR")).toFloat();
                            float BR = (n.attribute("BR")).toFloat();
                            float H = (n.attribute("H")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            /// glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            TruncatedCone(TR, BR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            TruncatedCone(TR, BR, H);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("EccentricTruncatedCone")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TR = (n.attribute("TR")).toFloat();
                            float BR = (n.attribute("BR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float TOPXOFF = (n.attribute("TOPXOFF")).toFloat();
                            float TOPYOFF = (n.attribute("TOPYOFF")).toFloat();

                            ////1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            // glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            EccentricTruncatedCone(TR, BR, H, TOPXOFF, TOPYOFF);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Ring")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float DR = (n.attribute("DR")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();


                            ////1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Ring(DR, R1, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Ring(DR, R1, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("RectangularRing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float DR = (n.attribute("DR")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            RectangularRing(DR, R1, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            RectangularRing(DR, R1, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("EllipticRing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float DR = (n.attribute("DR")).toFloat();

                            float L = (n.attribute("L")).toFloat();
                            float W = (n.attribute("W")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            EllipticRing(DR, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            EllipticRing(DR, L, W);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("CircularGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float OR = (n.attribute("OR")).toFloat();
                            float IR = (n.attribute("IR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            CircularGasket(OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            CircularGasket(OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("TableGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float TR = (n.attribute("TR")).toFloat();
                            float OR = (n.attribute("OR")).toFloat();
                            float IR = (n.attribute("IR")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            TableGasket(TR, OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            TableGasket(TR, OR, IR, H, Rad);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("SquareGasket")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float L1 = (n.attribute("L1")).toFloat();
                            float W1 = (n.attribute("W1")).toFloat();
                            float L2 = (n.attribute("L2")).toFloat();
                            float W2 = (n.attribute("W2")).toFloat();
                            float H = (n.attribute("H")).toFloat();
                            float CT = (n.attribute("CT")).toFloat();
                            float Rad = (n.attribute("Rad")).toFloat();
                            float CL = (n.attribute("CL")).toFloat();


                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            SquareGasket(L1, W1, L2, W2, H, CT, Rad, CL);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("PorcelainBushing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float H = (n.attribute("H")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float R2 = (n.attribute("R1")).toFloat();
                            float R3 = (n.attribute("R2")).toFloat();
                            float N = (n.attribute("N")).toFloat();



                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("ConePorcelainBushing")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            //获取颜色
                           /* float R = (float)simpleEntity.getR() / 255;
                            float G = (float)simpleEntity.getG() / 255;
                            float B = (float)simpleEntity.getB() / 255;
                            float A = (float)simpleEntity.getA() / 255;*/
                            //获取长宽高

                            float H = (n.attribute("H")).toFloat();
                            float R1 = (n.attribute("R")).toFloat();
                            float R2 = (n.attribute("R1")).toFloat();
                            float R3 = (n.attribute("R2")).toFloat();
                            float N = (n.attribute("N")).toFloat();

                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            PorcelainBushing(H, R1, R2, R3, N);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                        }
                        if (simpleEntity.getGraphicElement().nodeName() == ("Insulator")) {
                            QDomElement n = simpleEntity.getGraphicElement().toElement();
                            QString  vs = simpleEntity.getTransformMatrix();
                            QStringList splits = vs.split(",");
                            float mat[16];
                            for (int i = 0; i < 16; i++)
                            {
                                mat[i] = (splits[i]).toFloat();
                            }
                            ////获取旋转角度
                            float rX = (atan2(mat[9], mat[10])) * PI / 180;
                            float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
                            float rZ = (atan2(mat[4], mat[0])) * PI / 180;
                            //获取坐标
                            float X = mat[12];
                            float Y = mat[13];
                            float Z = mat[14];
                            ////获取颜色
                            //float R = (float)simpleEntity.getR() / 255;
                            //float G = (float)simpleEntity.getG() / 255;
                            //float B = (float)simpleEntity.getB() / 255;
                            //float A = (float)simpleEntity.getA() / 255;
                            //获取长宽高

                            float N = (n.attribute("N")).toFloat();
                            float D = (n.attribute("D")).toFloat();
                            float N1 = (n.attribute("N1")).toFloat();
                            float H1 = (n.attribute("H1")).toFloat();
                            float R1 = (n.attribute("R1")).toFloat();
                            float R2 = (n.attribute("R2")).toFloat();
                            float R3 = (n.attribute("R")).toFloat();
                            //float FL = (n.attribute("FL")).toFloat();
                            //float AL = (n.attribute("AL")).toFloat();
                            //float LN = (n.attribute("LN")).toFloat();


                            //1
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(0.0F, 0.0F, 0.0F, 1.0F);
                            Insulator(N, D, N1, H1, R1, R2, R3);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            //2
                            glPushMatrix();
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            glPushMatrix();
                            glTranslatef(X3, Z3, Y3);
                            glRotatef(RX3, 1, 0, 0);
                            glRotatef(RY3, 0, 1, 0);
                            glRotatef(RZ3, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X2, Z2, Y2);
                            glRotatef(RX2, 1, 0, 0);
                            glRotatef(RY2, 0, 1, 0);
                            glRotatef(RZ2, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X1, Z1, Y1);
                            glRotatef(rX1, 1, 0, 0);
                            glRotatef(rY1, 0, 1, 0);
                            glRotatef(rZ1, 0, 0, 1);
                            glPushMatrix();
                            glTranslatef(X, Z, Y);
                            glRotatef(rX, 1, 0, 0);
                            glRotatef(rY, 0, 1, 0);
                            glRotatef(rZ, 0, 0, 1);
                            //glColor4f(R, G, B, A);
                            Insulator(N, D, N1, H1, R1, R2, R3);
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();
                            glPopMatrix();

                        }

                    }
                }

            }
        }


    }
    glPopMatrix();
}
void myopengl::Cylinder(GLfloat R, GLfloat H)
{
    glPushMatrix();
    GLUquadricObj* qobj1 = gluNewQuadric();
    GLUquadricObj* qobj2 = gluNewQuadric();
    GLUquadricObj* qobj3 = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(qobj1, R, R, H, 32, 32);
    glScalef(-1.0f, 1.0f, -1.0f);
    gluDisk(qobj2, 0.0, R, 32, 32);
    glScalef(-1.0f, 1.0f, -1.0f);
    glTranslatef(0.0f, 0.0f, H);
    gluDisk(qobj3, 0.0, R, 32, 32);
    gluDeleteQuadric(qobj1);
    gluDeleteQuadric(qobj2);
    gluDeleteQuadric(qobj3);
    glPopMatrix();
}
void myopengl::Cuboid(GLfloat L, GLfloat W, GLfloat H)
{
    //qDebug() << 111111 << endl;
    glPushMatrix();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //

   //由四个点组成一个四边形

    GLfloat M = L / 2;
    GLfloat n = W / 2;

    glBegin(GL_QUADS);
    //画底面
    glVertex3f(M, 0, -n);
    glVertex3f(M, 0, n);
    glVertex3f(-M, 0, n);
    glVertex3f(-M, 0, -n);


    //画上面
    glVertex3f(M, H, -n);
    glVertex3f(-M, H, -n);
    glVertex3f(-M, H, n);
    glVertex3f(M, H, n);
    //画右侧
    glVertex3f(M, 0, -n);
    glVertex3f(M, H, -n);
    glVertex3f(M, H, n);
    glVertex3f(M, 0, n);
    //画左侧
    glVertex3f(-M, 0, n);
    glVertex3f(-M, H, n);
    glVertex3f(-M, H, -n);
    glVertex3f(-M, 0, -n);
    //画前面
    glVertex3f(M, 0, n);
    glVertex3f(M, H, n);
    glVertex3f(-M, H, n);
    glVertex3f(-M, 0, n);




    //画后面
    glVertex3f(M, 0, -n);
    glVertex3f(-M, 0, -n);
    glVertex3f(-M, H, -n);
    glVertex3f(M, H, -n);






    glEnd();

    glPopMatrix();
}
void myopengl::Sphere(GLfloat radius)
{
    glPushMatrix();
    GLUquadric* quadObj1 = gluNewQuadric();
    glScalef(-1.0f, 1.0f, -1.0f);
    gluSphere(quadObj1, radius, 32, 32);
    gluDeleteQuadric(quadObj1);
    glPopMatrix();
}
void myopengl::RotationalEllipsoid(GLfloat RL, GLfloat WR, GLfloat H)
{
    glPushMatrix();
    float step_z = PI / 32;
    float step_xy = 2 * PI / 32;
    float x[4], y[4], z[4];

    float angle_z = 0.0;
    float angle_xy = 0.0;
    int i = 0, j = 0;
    glBegin(GL_QUADS);
    for (i = 0; i < 32; i++)
    {
        angle_z = i * step_z;

        for (j = 0; j < 32; j++)
        {
            angle_xy = j * step_xy;

            x[0] = RL * sin(angle_z) * cos(angle_xy);
            y[0] = WR * sin(angle_z) * sin(angle_xy);
            z[0] = H * cos(angle_z);

            x[1] = RL * sin(angle_z + step_z) * cos(angle_xy);
            y[1] = WR * sin(angle_z + step_z) * sin(angle_xy);
            z[1] = H * cos(angle_z + step_z);

            x[2] = RL * sin(angle_z + step_z) * cos(angle_xy + step_xy);
            y[2] = WR * sin(angle_z + step_z) * sin(angle_xy + step_xy);
            z[2] = H * cos(angle_z + step_z);

            x[3] = RL * sin(angle_z) * cos(angle_xy + step_xy);
            y[3] = WR * sin(angle_z) * sin(angle_xy + step_xy);
            z[3] = H * cos(angle_z);
            for (int k = 0; k < 4; k++)
            {

                glVertex3f(0 + x[k], 0 + y[k], 0 + z[k]);
            }
        }
    }
    glEnd();
    glPopMatrix();
}
void myopengl::Table(GLfloat TL1, GLfloat TL2, GLfloat LL1, GLfloat LL2, GLfloat H)
{

    /* TL1	顶面对角线长 1
        TL2	顶面对角线长 2
        LL1	底面对角线长 1
        LL2	底面对角线长 2
        H	高*/
    glPushMatrix();
    GLfloat M = TL1 / 2;
    GLfloat N = TL2 / 2;
    GLfloat P = LL1 / 2;
    GLfloat Q = LL2 / 2;
    glBegin(GL_QUADS);//由四个点组成一个四边形

     //画底面
    glVertex3f(P, 0, 0);
    glVertex3f(0, 0, Q);
    glVertex3f(-P, 0, 0);
    glVertex3f(0, 0, -Q);
    //画上面
    glVertex3f(M, H, 0);
    glVertex3f(0, H, N);
    glVertex3f(-M, H, 0);
    glVertex3f(0, H, -N);
    //画左侧
    glVertex3f(P, 0, 0);
    glVertex3f(0, 0, H);
    glVertex3f(0, H, N);
    glVertex3f(M, H, 0);
    //画前面
    glVertex3f(0, 0, Q);
    glVertex3f(-P, 0, 0);;
    glVertex3f(-M, H, 0);
    glVertex3f(0, H, N);
    //画右侧
    glVertex3f(-P, 0, 0);
    glVertex3f(0, 0, -Q);
    glVertex3f(0, H, -N);
    glVertex3f(-M, H, 0);
    //画后面
    glVertex3f(P, 0, 0);
    glVertex3f(0, 0, -Q);
    glVertex3f(0, H, -N);
    glVertex3f(M, H, 0);
    glEnd();
    glPopMatrix();
}
void myopengl::OffsetRectangularTable(GLfloat TL, GLfloat TW, GLfloat LL, GLfloat LW, GLfloat H, GLfloat XOFF, GLfloat YOFF)
{
    glPushMatrix();
    GLfloat M = TL / 2;
    GLfloat N = TW / 2;
    GLfloat P = LL / 2;
    GLfloat Q = LW / 2;
    glBegin(GL_QUADS);//由四个点组成一个四边形

     //画底面
    glVertex3f(P, 0, -Q);
    glVertex3f(P, 0, Q);
    glVertex3f(-P, 0, Q);
    glVertex3f(-P, 0, -Q);
    //画上面
    glVertex3f(XOFF + M, H, -YOFF + N);
    glVertex3f(XOFF + M, H, YOFF + N);
    glVertex3f(-XOFF + M, H, YOFF + N);
    glVertex3f(-XOFF + M, H, -YOFF + N);
    //画左侧
    glVertex3f(P, 0, -Q);
    glVertex3f(P, 0, Q);
    glVertex3f(XOFF + M, H, YOFF + N);
    glVertex3f(XOFF + M, H, -YOFF + N);
    //画前面
    glVertex3f(P, 0, Q);
    glVertex3f(-P, 0, Q);
    glVertex3f(-XOFF + M, H, YOFF + N);
    glVertex3f(XOFF + M, H, YOFF + N);
    //画右侧
    glVertex3f(-P, 0, Q);
    glVertex3f(-P, 0, -Q);
    glVertex3f(-XOFF + M, H, -YOFF + N);
    glVertex3f(-XOFF + M, H, YOFF + N);
    //画后面
    glVertex3f(P, 0, -Q);
    glVertex3f(-P, 0, -Q);
    glVertex3f(-XOFF + M, H, -YOFF + N);
    glVertex3f(XOFF + M, H, -YOFF + N);
    glEnd();
    glPopMatrix();
}
void myopengl::TruncatedCone(GLfloat TR, GLfloat BR, GLfloat H)
{
    glPushMatrix();
    glTranslatef(0, H, 0);
    glPushMatrix();
    GLUquadricObj* qobj = gluNewQuadric();

    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(qobj, TR, BR, H, 32, 32);
    //glScalef(-1.0f, 1.0f, -1.0f);
    gluDisk(qobj, 0.0, TR, 32, 32);
    //glScalef(-1.0f, 1.0f, -1.0f);
    glTranslatef(0.0f, 0.0f, H);

    gluDisk(qobj, 0.0, BR, 32, 32);

    gluDeleteQuadric(qobj);
    glPopMatrix();
    glPopMatrix();
}
void myopengl::EccentricTruncatedCone(GLfloat TR, GLfloat BR, GLfloat H, GLfloat TOPXOFF, GLfloat TOPYOFF)
{
    glPushMatrix();
    GLUquadricObj* qobj = gluNewQuadric();
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUAD_STRIP);//连续填充四边形串
    int i = 0;
    for (i = 0; i <= 360; i += 15)
    {
        float p = i * 3.14 / 180;
        glVertex3f(TR * sin(p) + TOPXOFF, TR * cos(p) + TOPYOFF, 1.0f);
        glVertex3f(BR * sin(p), BR * cos(p), 0.0f);
    }
    glEnd();

    gluDisk(qobj, 0.0, BR, 32, 32);

    glTranslatef(TOPXOFF, TOPYOFF, H);

    gluDisk(qobj, 0.0, TR, 32, 32);

    gluDeleteQuadric(qobj);
    glPopMatrix();
}
//gim文档用的图
void myopengl::Ring(GLfloat DR, GLfloat R, GLfloat Rad)
{
    glPushMatrix();
    double sideDelta = 2 * PI / 32;//控制里面闭环
    double ringDelta = Rad / 32;//控制弧度
    double theta = 0;
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    double phi, sinPhi, cosPhi;
    double dist;
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    for (int i = 0; i < 32; i++)
    {
        double theta1 = theta + ringDelta;
        double cosTheta1 = cos(theta1);
        double sinTheta1 = sin(theta1);

        glBegin(GL_QUAD_STRIP);
        phi = 0;
        for (int j = 0; j <= 32; j++)
        {
            phi = phi + sideDelta;
            cosPhi = cos(phi);
            sinPhi = sin(phi);
            dist = R + (DR * cosPhi);

            glNormal3f(cosTheta * cosPhi, sinTheta * cosPhi, sinPhi);

            glVertex3f(cosTheta * dist, sinTheta * dist, DR * sinPhi);

            glNormal3f(cosTheta1 * cosPhi, sinTheta1 * cosPhi, sinPhi);

            glVertex3f(cosTheta1 * dist, sinTheta1 * dist, DR * sinPhi);
        }
        glEnd();
        theta = theta1;
        cosTheta = cosTheta1;
        sinTheta = sinTheta1;
    }
    glPopMatrix();
}
//画图电缆用的rings
void myopengl::Rings(GLfloat R, GLfloat DR, GLdouble Rad, GLdouble theta)
{
    glPushMatrix();
    double sideDelta = 2 * PI / 32;//控制里面闭环
    double ringDelta = Rad / 32;//控制弧度
    //double theta = -90;
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    double phi, sinPhi, cosPhi;
    double dist;
    // glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    for (int i = 0; i < 32; i++)
    {
        double theta1 = theta + ringDelta;
        double cosTheta1 = cos(theta1);
        double sinTheta1 = sin(theta1);

        glBegin(GL_QUAD_STRIP);
        phi = 0;
        for (int j = 0; j <= 32; j++)
        {
            phi = phi + sideDelta;
            cosPhi = cos(phi);
            sinPhi = sin(phi);
            dist = R + (DR * cosPhi);

            glNormal3f(cosTheta * cosPhi, sinTheta * cosPhi, sinPhi);

            glVertex3f(cosTheta * dist, sinTheta * dist, DR * sinPhi);

            glNormal3f(cosTheta1 * cosPhi, sinTheta1 * cosPhi, sinPhi);

            glVertex3f(cosTheta1 * dist, sinTheta1 * dist, DR * sinPhi);
        }
        glEnd();
        theta = theta1;
        cosTheta = cosTheta1;
        sinTheta = sinTheta1;
    }
    glPopMatrix();
}
void myopengl::RectangularRing(GLfloat DR, GLfloat R, GLfloat L, GLfloat W)
{
    glPushMatrix();
    GLfloat M = L - 2 * (R - DR);
    GLfloat N = W - 2 * (R - DR);
    GLfloat T = R - DR;

    glPushMatrix();
    GLUquadricObj* qobj = gluNewQuadric();
    glTranslatef(-M / 2, 0, -W / 2);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(qobj, DR, DR, M, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(M / 2, 0, -N / 2);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    Ring(DR, T, PI / 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-M / 2, 0, W / 2);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(qobj, DR, DR, M, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(M / 2, 0, N / 2);
    Ring(DR, T, PI / 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-M / 2, 0, -N / 2);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    Ring(DR, T, PI / 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-M / 2, 0, N / 2);
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
    Ring(DR, T, PI / 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(L / 2, 0, -N / 2);
    gluCylinder(qobj, DR, DR, N, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-L / 2, 0, -N / 2);
    gluCylinder(qobj, DR, DR, N, 32, 32);
    glPopMatrix();
    glPopMatrix();
}
void myopengl::EllipticRing(GLfloat DR, GLfloat L, GLfloat W)
{
    glPushMatrix();
    double sideDelta = 2 * PI / 32;
    double ringDelta = 2 * PI / 32;//控制弧度
    double theta = 0;
    double cosTheta = 1.0;
    double sinTheta = 0.0;

    double phi, sinPhi, cosPhi;
    double dist1;
    double dist2;
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    for (int i = 0; i < 32; i++)
    {
        double theta1 = theta + ringDelta;
        double cosTheta1 = cos(theta1);
        double sinTheta1 = sin(theta1);

        glBegin(GL_QUAD_STRIP);
        phi = 0;
        for (int j = 0; j <= 32; j++)
        {
            phi = phi + sideDelta;
            cosPhi = L * cos(phi);
            sinPhi = W * sin(phi);
            dist1 = L + (DR * cosPhi);
            dist2 = W + (DR * cosPhi);

            glNormal3f(cosTheta * cosPhi, sinTheta * cosPhi, sinPhi);

            glVertex3f(cosTheta * dist1, sinTheta * dist2, DR * sinPhi);

            glNormal3f(cosTheta1 * cosPhi, sinTheta1 * cosPhi, sinPhi);

            glVertex3f(cosTheta1 * dist1, sinTheta1 * dist2, DR * sinPhi);
        }
        glEnd();
        theta = theta1;
        cosTheta = cosTheta1;
        sinTheta = sinTheta1;
    }
    glPopMatrix();
}
void myopengl::CircularGasket(GLfloat IR, GLfloat OR, GLfloat H, GLfloat Rad)
{
    glPushMatrix();
    GLUquadricObj* qobj = gluNewQuadric();
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glPushMatrix();

    gluPartialDisk(qobj, IR, OR, 32, 32, 0, Rad);
    /* GLUquadric *qobj,
    GLdouble   innerRadius,
        GLdouble   outerRadius,
        GLint      slices,
        GLint      loops,
        GLdouble   startAngle,
        GLdouble   sweepAngle*/
    glBegin(GL_QUAD_STRIP);//连续填充四边形串
    int j = 0;
    for (j = 0; j <= Rad; j += 15)
    {
        float p = (float)(j * 3.14 / 180);
        glVertex3f(IR * sin(p), IR * cos(p), H);
        glVertex3f(IR * sin(p), IR * cos(p), 0.0f);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    int i = 0;
    for (i = 0; i <= Rad; i += 15)
    {
        float p = (float)(i * 3.14 / 180);
        glVertex3f(OR * sin(p), OR * cos(p), H);
        glVertex3f(OR * sin(p), OR * cos(p), 0.0f);
    }
    glEnd();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, H);
    gluPartialDisk(qobj, IR, OR, 32, 32, 0, Rad);
    glPopMatrix();
    gluDeleteQuadric(qobj);
    glPopMatrix();
}
void myopengl::TableGasket(GLfloat TR, GLfloat OR, GLfloat IR, GLfloat H, GLfloat Rad)
{
    glPushMatrix();
    GLUquadricObj* qobj = gluNewQuadric();
    glRotatef(270, 1.0f, 0.0f, 0.0f);
    glPushMatrix();
    gluPartialDisk(qobj, IR, OR, 32, 32, 0, Rad);

    glBegin(GL_QUAD_STRIP);//连续填充四边形串
    int i = 0;
    for (i = 0; i <= Rad; i += 15)
    {
        float p = (float)(i * 3.14 / 180);
        glVertex3f(IR * sin(p), IR * cos(p), H);
        glVertex3f(IR * sin(p), IR * cos(p), 0.0f);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);//连续填充四边形串
    int j = 0;
    for (j = 0; j <= Rad; j += 15)
    {
        float p = (float)(j * 3.14 / 180);
        glVertex3f(TR * sin(p), TR * cos(p), H);
        glVertex3f(OR * sin(p), OR * cos(p), 0);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, H);
    gluPartialDisk(qobj, IR, TR, 32, 32, 0, Rad);
    glPopMatrix();
    gluDeleteQuadric(qobj);
    glPopMatrix();
}
void myopengl::SquareGasket(GLfloat L1, GLfloat W1, GLfloat L2, GLfloat W2, GLfloat H, GLfloat CT, GLfloat R, GLfloat CL)
{
    glPushMatrix();
    if (CT == 1) {
        glRotatef(270, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        //画右底面
        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glVertex3f(L1 / 2, 0, W1 / 2);
        glVertex3f(L1 / 2, 0, -W1 / 2);
        //右上面
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);
        glVertex3f(L1 / 2, H, W1 / 2);
        glVertex3f(L1 / 2, H, -W1 / 2);
        //画上面底
        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-L1 / 2, 0, -W1 / 2);
        glVertex3f(L1 / 2, 0, -W1 / 2);
        //画上面上
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glVertex3f(-L1 / 2, H, -W1 / 2);
        glVertex3f(L1 / 2, H, -W1 / 2);
        //画左侧底面
        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-L1 / 2, 0, W1 / 2);
        glVertex3f(-L1 / 2, 0, -W1 / 2);
        //画左侧上面
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glVertex3f(-L2 / 2, H, W2 / 2);
        glVertex3f(-L1 / 2, H, W1 / 2);
        glVertex3f(-L1 / 2, H, -W1 / 2);
        //画前面底面
        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-L1 / 2, 0, W1 / 2);
        glVertex3f(L1 / 2, 0, W1 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        //画前面上面
        glVertex3f(-L2 / 2, H, W2 / 2);
        glVertex3f(-L1 / 2, H, W1 / 2);
        glVertex3f(L1 / 2, H, W1 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);


        glVertex3f(L1 / 2, 0, W1 / 2);
        glVertex3f(L1 / 2, H, W1 / 2);
        glVertex3f(L1 / 2, 0, -W1 / 2);
        glVertex3f(L1 / 2, H, -W1 / 2);

        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, H, -W2 / 2);

        glVertex3f(-L1 / 2, 0, -W1 / 2);
        glVertex3f(-L1 / 2, H, -W1 / 2);
        glVertex3f(L1 / 2, 0, -W1 / 2);
        glVertex3f(L1 / 2, H, -W1 / 2);

        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-L2 / 2, H, W2 / 2);

        glVertex3f(-L1 / 2, 0, W1 / 2);
        glVertex3f(-L1 / 2, H, W1 / 2);
        glVertex3f(-L1 / 2, H, -W1 / 2);
        glVertex3f(-L1 / 2, H, -W1 / 2);

        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-L2 / 2, H, W2 / 2);
        glVertex3f(-L1 / 2, 0, W1 / 2);
        glVertex3f(-L1 / 2, H, W1 / 2);

        glVertex3f(L1 / 2, 0, W1 / 2);
        glVertex3f(L1 / 2, H, W1 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);
        glEnd();
    }
    else if (CT == 3) {
        GLfloat M = (L1 / 2) - CL;
        GLfloat N = (W1 / 2) - CL;
        glRotatef(270, 0.0f, 0.0f, 1.0f);
        //画右底面
        glBegin(GL_POLYGON);
        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glVertex3f(M, 0, W1 / 2);
        glVertex3f(L1 / 2, 0, N);
        glVertex3f(L1 / 2, 0, -N);
        glEnd();
        //画上地面
        glBegin(GL_POLYGON);
        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-M, 0, -W1 / 2);
        glVertex3f(M, 0, -W1 / 2);
        glVertex3f(L1 / 2, 0, -N);
        glEnd();
        //画左地底面
        glBegin(GL_POLYGON);
        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-M, 0, -W1 / 2);
        glVertex3f(-L1 / 2, 0, -N);
        glVertex3f(-L1 / 2, 0, N);
        glVertex3f(-L2 / 2, 0, W2 / 2);
        glEnd();
        //画下面底面
        glBegin(GL_POLYGON);
        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-L1 / 2, 0, N);
        glVertex3f(-M, 0, W1 / 2);
        glVertex3f(M, 0, W1 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glEnd();


        //画右上面
        glBegin(GL_POLYGON);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);
        glVertex3f(M, H, W1 / 2);
        glVertex3f(L1 / 2, H, N);
        glVertex3f(L1 / 2, H, -N);
        glEnd();
        //画上上面
        glBegin(GL_POLYGON);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glVertex3f(-M, H, -W1 / 2);
        glVertex3f(M, H, -W1 / 2);
        glVertex3f(L1 / 2, H, -N);
        glEnd();
        //画左上面
        glBegin(GL_POLYGON);
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glVertex3f(-M, H, -W1 / 2);
        glVertex3f(-L1 / 2, H, -N);
        glVertex3f(-L1 / 2, H, N);
        glVertex3f(-L2 / 2, H, W2 / 2);
        glEnd();
        //画下上面
        glBegin(GL_POLYGON);
        glVertex3f(-L2 / 2, H, W2 / 2);
        glVertex3f(-L1 / 2, H, N);
        glVertex3f(-M, H, W1 / 2);
        glVertex3f(M, H, W1 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);
        glEnd();


        //画侧面
        glBegin(GL_QUAD_STRIP);
        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);

        glVertex3f(M, 0, W1 / 2);
        glVertex3f(M, H, W1 / 2);
        glVertex3f(L1 / 2, 0, N);
        glVertex3f(L1 / 2, H, N);

        glVertex3f(L1 / 2, 0, N);
        glVertex3f(L1 / 2, H, N);
        glVertex3f(L1 / 2, 0, -N);
        glVertex3f(L1 / 2, H, -N);

        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, H, -W2 / 2);

        glVertex3f(-M, 0, -W1 / 2);
        glVertex3f(-M, H, -W1 / 2);
        glVertex3f(M, 0, -W1 / 2);
        glVertex3f(M, H, -W1 / 2);

        glVertex3f(M, 0, -W1 / 2);
        glVertex3f(M, H, -W1 / 2);
        glVertex3f(L1 / 2, 0, -N);
        glVertex3f(L1 / 2, H, -N);

        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glVertex3f(-M, 0, -W1 / 2);
        glVertex3f(-M, H, -W1 / 2);

        glVertex3f(-M, 0, -W1 / 2);
        glVertex3f(-M, H, -W1 / 2);
        glVertex3f(-L1 / 2, 0, -N);
        glVertex3f(-L1 / 2, H, -N);

        glVertex3f(-L1 / 2, 0, -N);
        glVertex3f(-L1 / 2, H, -N);
        glVertex3f(-L1 / 2, 0, N);
        glVertex3f(-L1 / 2, H, N);

        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-L2 / 2, H, W2 / 2);

        glVertex3f(-L1 / 2, 0, N);
        glVertex3f(-L1 / 2, H, N);
        glVertex3f(-M, 0, W1 / 2);
        glVertex3f(-M, H, W1 / 2);

        glVertex3f(-M, 0, W1 / 2);
        glVertex3f(-M, H, W1 / 2);
        glVertex3f(M, 0, W1 / 2);
        glVertex3f(M, H, W1 / 2);

        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-L2 / 2, H, W2 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);
        glEnd();
    }
    else {
        glRotatef(270.0f, 0.0f, 0.0f, 1.0f);
        GLUquadricObj* qobj = gluNewQuadric();
        GLfloat P = (L1 / 2) - R;
        GLfloat Q = (W1 / 2) - R;
        //画右底面
        glBegin(GL_POLYGON);
        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glVertex3f(P, 0, Q);
        glVertex3f(L1 / 2, 0, Q);
        glVertex3f(L1 / 2, 0, -Q);
        glVertex3f(P, 0, -Q);
        glEnd();
        glPushMatrix();
        glTranslated(P, 0, Q);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluPartialDisk(qobj, 0, R, 32, 32, 0, 90);
        glPopMatrix();
        glPushMatrix();
        glTranslated(P, 0, -Q);
        glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
        gluPartialDisk(qobj, 0, R, 32, 32, 0, 90);
        glPopMatrix();
        //画上底面
        glBegin(GL_POLYGON);
        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(P, 0, -Q);
        glVertex3f(P, 0, -W1 / 2);
        glVertex3f(-P, 0, -W1 / 2);
        glVertex3f(-P, 0, -Q);
        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glEnd();
        glPushMatrix();
        glTranslated(-P, 0, -Q);
        glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        gluPartialDisk(qobj, 0, R, 32, 32, 0, 90);
        glPopMatrix();
        //画左底面
        glBegin(GL_POLYGON);
        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-P, 0, -Q);
        glVertex3f(-L1 / 2, 0, -Q);
        glVertex3f(-L1 / 2, 0, Q);
        glVertex3f(-P, 0, Q);
        glVertex3f(-L2 / 2, 0, W2 / 2);
        glEnd();
        glPushMatrix();
        glTranslated(-P, 0, Q);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        gluPartialDisk(qobj, 0, R, 32, 32, 0, 90);
        glPopMatrix();
        //画下底面
        glBegin(GL_POLYGON);
        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-P, 0, Q);
        glVertex3f(-P, 0, W1 / 2);
        glVertex3f(P, 0, W1 / 2);
        glVertex3f(P, 0, Q);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glEnd();


        //画右上面
        glBegin(GL_POLYGON);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);
        glVertex3f(P, H, Q);
        glVertex3f(L1 / 2, H, Q);
        glVertex3f(L1 / 2, H, -Q);
        glVertex3f(P, H, -Q);
        glEnd();
        glPushMatrix();
        glTranslated(P, H, Q);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        gluPartialDisk(qobj, 0, R, 32, 32, 0, 90);
        glPopMatrix();
        glPushMatrix();
        glTranslated(P, H, -Q);
        glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
        gluPartialDisk(qobj, 0, R, 32, 32, 0, 90);
        glPopMatrix();
        //画上上面
        glBegin(GL_POLYGON);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(P, H, -Q);
        glVertex3f(P, H, -W1 / 2);
        glVertex3f(-P, H, -W1 / 2);
        glVertex3f(-P, H, -Q);
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glEnd();
        glPushMatrix();
        glTranslated(-P, H, -Q);
        glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        gluPartialDisk(qobj, 0, R, 32, 32, 0, 90);
        glPopMatrix();
        //画左上面
        glBegin(GL_POLYGON);
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glVertex3f(-P, H, -Q);
        glVertex3f(-L1 / 2, H, -Q);
        glVertex3f(-L1 / 2, H, Q);
        glVertex3f(-P, H, Q);
        glVertex3f(-L2 / 2, H, W2 / 2);
        glEnd();
        glPushMatrix();
        glTranslated(-P, H, Q);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        gluPartialDisk(qobj, 0, R, 32, 32, 0, 90);
        glPopMatrix();
        //画下上面
        glBegin(GL_POLYGON);
        glVertex3f(-L2 / 2, H, W2 / 2);
        glVertex3f(-P, H, Q);
        glVertex3f(-P, H, W1 / 2);
        glVertex3f(P, H, W1 / 2);
        glVertex3f(P, H, Q);
        glVertex3f(L2 / 2, H, W2 / 2);
        glEnd();


        //画侧面
        glBegin(GL_QUAD_STRIP);
        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);

        glVertex3f(L1 / 2, 0, Q);
        glVertex3f(L1 / 2, H, Q);
        glVertex3f(L1 / 2, 0, -Q);
        glVertex3f(L1 / 2, H, -Q);

        glVertex3f(L2 / 2, 0, -W2 / 2);
        glVertex3f(L2 / 2, H, -W2 / 2);
        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, H, -W2 / 2);

        glVertex3f(P, 0, -W1 / 2);
        glVertex3f(P, H, -W1 / 2);
        glVertex3f(-P, 0, -W1 / 2);
        glVertex3f(-P, H, -W1 / 2);

        glVertex3f(-L2 / 2, 0, -W2 / 2);
        glVertex3f(-L2 / 2, H, -W2 / 2);
        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-L2 / 2, H, W2 / 2);

        glVertex3f(-L1 / 2, 0, -Q);
        glVertex3f(-L1 / 2, H, -Q);
        glVertex3f(-L1 / 2, 0, Q);
        glVertex3f(-L1 / 2, H, Q);

        glVertex3f(-L2 / 2, 0, W2 / 2);
        glVertex3f(-L2 / 2, H, W2 / 2);
        glVertex3f(L2 / 2, 0, W2 / 2);
        glVertex3f(L2 / 2, H, W2 / 2);

        glVertex3f(-P, 0, W1 / 2);
        glVertex3f(-P, H, W1 / 2);
        glVertex3f(P, 0, W1 / 2);
        glVertex3f(P, H, W1 / 2);
        glEnd();

        glPushMatrix();
        glTranslated(P, H, Q);
        glRotatef(-270.0f, 1.0f, 0.0f, 0.0f);
        glBegin(GL_QUAD_STRIP);//连续填充四边形串
        int j = 0;
        for (j = 0; j <= 90; j += 15)
        {
            float p = (float)(j * 3.14 / 180);
            glVertex3f(R * sin(p), R * cos(p), H);
            glVertex3f(R * sin(p), R * cos(p), 0.0f);
        }
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslated(P, 0, -Q);
        glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
        glBegin(GL_QUAD_STRIP);//连续填充四边形串
        int i = 0;
        for (i = 0; i <= 90; i += 15)
        {
            float p = (float)(i * 3.14 / 180);
            glVertex3f(R * sin(p), R * cos(p), H);
            glVertex3f(R * sin(p), R * cos(p), 0.0f);
        }
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-P, 0, -Q);
        glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUAD_STRIP);//连续填充四边形串
        int a = 0;
        for (a = 0; a <= 90; a += 15)
        {
            float p = (float)(a * 3.14 / 180);
            glVertex3f(R * sin(p), R * cos(p), H);
            glVertex3f(R * sin(p), R * cos(p), 0.0f);
        }
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslated(-P, H, Q);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_QUAD_STRIP);//连续填充四边形串
        int b = 0;
        for (b = 0; b <= 90; b += 15)
        {
            float p = (float)(b * 3.14 / 180);
            glVertex3f(R * sin(p), R * cos(p), H);
            glVertex3f(R * sin(p), R * cos(p), 0.0f);
        }
        glEnd();
        glPopMatrix();
        gluDeleteQuadric(qobj);
    }
    glPopMatrix();
}
void myopengl::StretchedBody(QString Normal, QString  Array, GLfloat L)
{
    //放向量
    QStringList Normalsplits = Normal.split(",");
    double vector1[3];
    vector1[0] = (Normalsplits[0]).toDouble();
    vector1[1] = (Normalsplits[1]).toDouble();
    vector1[2] = (Normalsplits[2]).toDouble();
    QStringList Arraysplits = Array.split(";");
    //建立数组，可以放上下底坐标
    int size = 2 * Arraysplits.size();
    double* vectorX = new double[size]();
    double* vectorY = new double[size]();
    double* vectorZ = new double[size]();
    //放出上底坐标
    int size1 = Arraysplits.size();
    double* vectorX2 = new  double[size1]();
    double* vectorY2 = new  double[size1]();
    double* vectorZ2 = new  double[size1]();
    //先把下底坐标放入vectorX、vectorY、vectorZ
    for (int i = 0; i < Arraysplits.size(); i++) {
        QStringList Arraysplits1 = Arraysplits[i].split(",");
        vectorX[i] = Arraysplits1[0].toDouble();
        vectorY[i] = Arraysplits1[1].toDouble();
        vectorZ[i] = Arraysplits1[2].toDouble();
        //
    }
    //把上底坐标放入vectorX2、vectorY2、vectorZ2
    for (int i = 0; i < Arraysplits.size(); i++) {
        double vector2[3];
        QStringList Arraysplits2 = Arraysplits[i].split(",");
        vector2[0] = Arraysplits2[0].toDouble();
        vector2[1] = Arraysplits2[1].toDouble();
        vector2[2] = Arraysplits2[2].toDouble();
        vectorX2[i] = vector2[0] + vector1[0];
        vectorY2[i] = vector2[1] + vector1[1] + L;
        vectorZ2[i] = vector2[2] + vector1[2];
    }
    //再把上底坐标放入vectorX、vectorY、vectorZ
    for (int i = Arraysplits.size(); i < 2 * Arraysplits.size(); i++) {
        int m = i - Arraysplits.size();
        vectorX[i] = vectorX2[m];
        vectorY[i] = vectorY2[m];
        vectorZ[i] = vectorZ2[m];

    }
    //画图
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < 2 * Arraysplits.size(); i++) {
        for (int j = 0; j < 2 * Arraysplits.size(); j++) {
            glVertex3f(vectorX[i], vectorZ[i], vectorY[i]);
            glVertex3f(vectorX[j], vectorZ[j], vectorY[j]);
        }

    }
    glEnd();
    glPopMatrix();

}
void myopengl::PorcelainBushing(GLfloat H, GLfloat R1, GLfloat R2, GLfloat R3, GLfloat N1)
{
    glPushMatrix();
    glRotatef(270, 1.0f, 0.0f, 0.0f);
    GLUquadricObj* qobj1 = gluNewQuadric();
    GLUquadricObj* qobj2 = gluNewQuadric();
    GLUquadricObj* qobj3 = gluNewQuadric();
    //画圆柱
    glPushMatrix();
    gluCylinder(qobj1, R1, R1, H, 32, 32);
    glPopMatrix();
    GLfloat H2 = H / N1 / 4.0F;
    glPushMatrix();
    for (int i = 0; i < N1; i++) {
       
        //绘制小曲面
        glPushMatrix();
        glTranslatef(0.0f, 0.0F, H2);
        gluCylinder(qobj2, R3, R1, H2, 32, 32);
        glPopMatrix();
        //绘制大曲面
        glPushMatrix();
        glTranslatef(0.0f, 0.0F, 3 * H2);
        gluCylinder(qobj3, R2, R1, H2, 32, 32);
        glPopMatrix();
        
        glTranslatef(0.0f, 0.0F, 4 * H2);
        
    }
    glPopMatrix();
    gluDeleteQuadric(qobj1);
    gluDeleteQuadric(qobj2);
    gluDeleteQuadric(qobj3);
    glPopMatrix();
}
void myopengl::ConePorcelainBushing(GLfloat H, GLfloat BR, GLfloat TR, GLfloat BR1, GLfloat BR2, GLfloat TR1, GLfloat TR2, GLfloat N)
{
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0.0f, H, 0.0);
    glRotatef(90, 1.0f, 0.0f, 0.0f);

    GLUquadricObj* qobj = gluNewQuadric();
    glPushMatrix();
    gluCylinder(qobj, TR, BR, H, 32, 32);
    glPopMatrix();
    GLfloat H2 = H / N / 8.0F;
    for (int i = 0; i < N; i++) {
        //绘制顶部大曲面
        glPushMatrix();
        glTranslatef(0.0f, 0.0F, H2);
        gluCylinder(qobj, TR, TR1, H2, 32, 32);
        glPopMatrix();

        //绘制顶部小曲面
        glPushMatrix();
        glTranslatef(0.0f, 0.0F, 3 * H2);
        gluCylinder(qobj, TR, TR2, H2, 32, 32);
        glPopMatrix();

        //绘制底部大曲面
        glPushMatrix();
        glTranslatef(0.0f, 0.0F, 5 * H2);
        gluCylinder(qobj, TR, BR1, H2, 32, 32);
        glPopMatrix();


        //绘制底部小曲面
        glPushMatrix();
        glTranslatef(0.0f, 0.0F, 7 * H2);
        gluCylinder(qobj, TR, BR2, H2, 32, 32);
        glPopMatrix();
        glTranslatef(0.0f, 0.0F, 8 * H2);

    }
    gluDeleteQuadric(qobj);
    glPopMatrix();
    glPopMatrix();

}
void myopengl::Insulator(int N, GLfloat D, int N1, GLfloat H1, GLfloat R1, GLfloat R2, GLfloat R)
{
    glPushMatrix();
    for (int j = 0; j < N; j++) {


        glPushMatrix();
        GLfloat M = H1 * N1;
        glTranslatef(-M / 2, 0, j * D);
        glRotatef(90, 0.0f, 1.0f, 0.0f);


        GLUquadricObj* qobj = gluNewQuadric();

        gluCylinder(qobj, R, R, M, 32, 32);



        GLfloat H = H1 / 4.0F;
        for (int i = 0; i < N1; i++) {
            //绘制大曲面
            gluCylinder(qobj, R, R1, H, 32, 32);


            //绘制小曲面
            glPushMatrix();
            glTranslatef(0.0f, 0.0F, 2 * H);
            gluCylinder(qobj, R, R2, H, 32, 32);
            glPopMatrix();
            glTranslatef(0.0f, 0.0F, 4 * H);
        }

        gluDeleteQuadric(qobj);

        glPopMatrix();

    }
    glPopMatrix();
}
void myopengl::VTypeInsulator(GLfloat X, GLfloat AD, int N1, GLfloat H1, GLfloat R, GLfloat R1, GLfloat R2, GLfloat FL, GLfloat AL)
{
    glPushMatrix();
    GLfloat M = H1 * N1;

    GLfloat P = (X - AD) / 2 * M;
    GLfloat Q = acos(P);
    GLfloat H = H1 / 4.0F;

    glPushMatrix();
    glTranslatef(-X / 2, 2.0F, 0.0F);
    glRotatef(30, 1.0f, 0.0f, 0.0f);

    GLUquadricObj* qobj = gluNewQuadric();
    gluCylinder(qobj, R, R, M, 32, 32);

    for (int i = 0; i < N1; i++) {
        //绘制大曲面
        gluCylinder(qobj, R, R1, H, 32, 32);
        //绘制小曲面
        glPushMatrix();
        glTranslatef(0.0f, 0.0F, 2 * H);
        gluCylinder(qobj, R, R2, H, 32, 32);
        glPopMatrix();
        glTranslatef(0.0f, 0.0F, 4 * H);
    }

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-X / 2, -2.0F, 0.0F);
    glRotatef(-30, 1.0f, 0.0f, 0.0f);

    gluCylinder(qobj, R, R, M, 32, 32);
    //GLfloat H = H1 / 4.0F;
    for (int i = 0; i < N1; i++) {
        //绘制大曲面
        gluCylinder(qobj, R, R1, H, 32, 32);
        //绘制小曲面
        glPushMatrix();
        glTranslatef(0.0f, 0.0F, 2 * H);
        gluCylinder(qobj, R, R2, H, 32, 32);
        glPopMatrix();
        glTranslatef(0.0f, 0.0F, 4 * H);
    }
    gluDeleteQuadric(qobj);
    glPopMatrix();
    glPopMatrix();
}
void myopengl::IrregularCuboid(GLfloat L, GLfloat W, GLfloat T, GLfloat CL)
{
    glPushMatrix();
    glBegin(GL_QUADS);//由四个点组成一个四边形

    //GLfloat M = L / 2;
    GLfloat N = W / 2;
    GLfloat P = T / 2;
    //画底面
    glVertex3f(-N, 0, -P);
    glVertex3f(-N, 0, P);
    glVertex3f(N, 0, P);
    glVertex3f(N, 0, -P);
    //画上面
    glVertex3f(-N + CL, L, -P);
    glVertex3f(-N + CL, L, P);
    glVertex3f(N - CL, L, P);
    glVertex3f(N - CL, L, -P);
    //画左侧
    glVertex3f(N, 0, -P);
    glVertex3f(N, L - CL, -P);
    glVertex3f(N, L - CL, P);
    glVertex3f(N, 0, P);
    //画右侧
    glVertex3f(-N, 0, -P);
    glVertex3f(-N, 0, P);
    glVertex3f(-N, L - CL, P);
    glVertex3f(-N, L - CL, -P);

    //右上方四边形
    glVertex3f(N, L - CL, P);
    glVertex3f(N, L - CL, -P);
    glVertex3f(N - CL, L, -P);
    glVertex3f(N - CL, L, P);

    //左上方四边形
    glVertex3f(-N, L - CL, -P);
    glVertex3f(-N, L - CL, P);
    glVertex3f(-N + CL, L, P);
    glVertex3f(-N + CL, L, -P);
    glEnd();
    glBegin(GL_POLYGON);
    //画前面
    glVertex3f(-N, 0, P);
    glVertex3f(N, 0, P);
    glVertex3f(N, L - CL, P);
    glVertex3f(N - CL, L, P);
    glVertex3f(-N + CL, L, P);
    glVertex3f(-N, L - CL, P);

    glEnd();
    glBegin(GL_POLYGON);
    //画后面
    glVertex3f(N, 0, -P);
    glVertex3f(-N, 0, -P);
    glVertex3f(-N, L - CL, -P);
    glVertex3f(-N + CL, L, -P);
    glVertex3f(N - CL, L, -P);
    glVertex3f(N, L - CL, -P);
    glEnd();

    glPopMatrix();
}
void myopengl::TerminalBlock(GLfloat L, GLfloat W, GLfloat T, GLfloat CL, GLfloat CS, GLfloat RS, GLfloat R1, int CN, int RN, GLfloat BL, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ)
{
    glPushMatrix();
    clearPrimtives();
    GLfloat  m = T + 0.5;
    GLfloat Q = RN / 2;
    GLfloat r = (CN - 1) / 2;

    GLfloat P = CN / 2;
    GLfloat s = (RN - 1) / 2;

    if (!glIsList((GLuint)(1002))) {
        //GLuint 100000002 = glGenLists(1);
        glNewList(1002, GL_COMPILE);

        glPushMatrix();
        glScalef(ScalefX, ScalefY, ScalefZ);
        glTranslatef(X, Z, Y);
        glRotatef(rX, 1, 0, 0);
        glRotatef(rY, 0, 1, 0);
        glRotatef(rZ, 0, 0, 1);
        IrregularCuboid(L, W, T, CL);
        glPopMatrix();

        glEndList();
    }
    primitives.push_back(new OpenCSG::DisplayListPrimitive(1002, OpenCSG::Intersection, 1));
    if (CN % 2 == 0 && RN % 2 != 0) {
        int a = 1;
        for (int x = -P; x < P; ++x) {
            int i = a;
            for (int z = -s; z <= s; ++z) {
                GLfloat  o = BL + s * RS;
                int b = 1100 + z + i;
                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);
                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(0, o, -m);
                    glPushMatrix();
                    glTranslatef((2 * x + 1) * CS / 2, z * RS, 0);
                    glRotated(-90, 1, 0, 0);
                    Cylinder(R1, L);
                    glPopMatrix();
                    glPopMatrix();
                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));
            }
            a = a + RN;
        }

    }
    if (CN % 2 == 0 && RN % 2 == 0) {
        int a = 4;


        for (int x = -P; x < P; ++x) {

            int i = a;
            for (int z = -Q; z < Q; ++z) {

                GLfloat  n = BL + Q * RS;
                GLfloat c = (2 * x + 1) * CS / 2;
                GLfloat d = (2 * z + 1) * RS / 2;
                int b = 1005 + z + i;



                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);
                    //GLuint id100000004 = glGenLists(1);
                    //glNewList(id100000004, GL_COMPILE);

                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(0, n, -m);
                    glPushMatrix();
                    glTranslatef(c, d, 0);
                    glRotated(-90, 1, 0, 0);
                    Cylinder(R1, L);
                    glPopMatrix();
                    glPopMatrix();

                    glEndList();
                }



                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + CN;

        }
    }
    if (CN % 2 != 0 && RN % 2 == 0) {
        int a = 1;
        for (int x = -r; x <= r; ++x) {
            int i = a;
            for (int z = -Q; z < Q; ++z) {
                int b = 1100 + z + i;
                GLfloat  n = BL + Q * RS;
                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);
                    //GLuint id100000005 = glGenLists(1);
                    //glNewList(id100000005, GL_COMPILE);

                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glScalef(ScalefX, ScalefY, ScalefZ);


                    glTranslatef(0, n, -m);

                    glPushMatrix();

                    glTranslatef(x * CS, (2 * z + 1) * RS / 2, 0);

                    glRotated(-90, 1, 0, 0);

                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);

                    Cylinder(R1, L);

                    glPopMatrix();
                    glPopMatrix();

                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + RN;
        }

    }
    if (CN % 2 != 0 && RN % 2 != 0) {
        int a = 1;
        for (int x = -r; x <= r; ++x) {
            int i = a;
            for (int z = -s; z <= s; ++z) {
                GLfloat  n = BL + s * RS;
                int b = 1100 + z + i;
                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);
                    //GLuint id100000006 = glGenLists(1);
                    //glNewList(id100000006, GL_COMPILE);

                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);

                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(0, n, -m);

                    glPushMatrix();

                    glTranslatef(x * CS, z * RS, 0);
                    glRotated(-90, 1, 0, 0);
                    Cylinder(R1, L);
                    glPopMatrix();
                    glPopMatrix();

                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + RN;
        }

    }

    OpenCSG::render(primitives);
    glDepthFunc(GL_EQUAL);
    for (std::vector<OpenCSG::Primitive*>::const_iterator j = primitives.begin(); j != primitives.end(); ++j) {
        (*j)->render();
    }
    glDepthFunc(GL_LESS);
    glPopMatrix();


}
void myopengl::TerminalBlock1(GLfloat L, GLfloat W, GLfloat T, GLfloat CL, GLfloat CS, GLfloat RS, GLfloat R1, int CN, int RN, GLfloat BL, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat rX2, GLfloat rY2, GLfloat rZ2)
{
    glPushMatrix();
    clearPrimtives();
    GLfloat  m = T + 0.5;
    GLfloat Q = RN / 2;
    GLfloat r = (CN - 1) / 2;

    GLfloat P = CN / 2;
    GLfloat s = (RN - 1) / 2;

    if (!glIsList((GLuint)(1002))) {

        glNewList(1002, GL_COMPILE);

        glPushMatrix();
        glScalef(ScalefX, ScalefY, ScalefZ);

        glTranslatef(X2, Z2, Y2);
        glRotatef(rX2, 1, 0, 0);
        glRotatef(rY2, 0, 1, 0);
        glRotatef(rZ2, 0, 0, 1);
        glPushMatrix();
        glTranslatef(X, Z, Y);
        glRotatef(rX, 1, 0, 0);
        glRotatef(rY, 0, 1, 0);
        glRotatef(rZ, 0, 0, 1);
        IrregularCuboid(L, W, T, CL);
        glPopMatrix();
        glPopMatrix();

        glEndList();
    }
    primitives.push_back(new OpenCSG::DisplayListPrimitive(1002, OpenCSG::Intersection, 1));
    if (CN % 2 == 0 && RN % 2 != 0) {
        int a = 1;
        for (int x = -P; x < P; ++x) {
            int i = a;
            for (int z = -s; z <= s; ++z) {
                GLfloat  o = BL + s * RS;
                int b = 1100 + z + i;
                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);

                    glPushMatrix();
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(X2, Z2, Y2);
                    glRotatef(rX2, 1, 0, 0);
                    glRotatef(rY2, 0, 1, 0);
                    glRotatef(rZ2, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);

                    glTranslatef(0, o, -m);
                    glPushMatrix();
                    glTranslatef((2 * x + 1) * CS / 2, z * RS, 0);
                    glRotated(-90, 1, 0, 0);
                    Cylinder(R1, L);
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + RN;
        }

    }
    if (CN % 2 == 0 && RN % 2 == 0) {
        int a = 4;


        for (int x = -P; x < P; ++x) {

            int i = a;
            for (int z = -Q; z < Q; ++z) {

                GLfloat  n = BL + Q * RS;
                GLfloat c = (2 * x + 1) * CS / 2;
                GLfloat d = (2 * z + 1) * RS / 2;
                int b = 1005 + z + i;



                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);

                    glPushMatrix();
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(X2, Z2, Y2);
                    glRotatef(rX2, 1, 0, 0);
                    glRotatef(rY2, 0, 1, 0);
                    glRotatef(rZ2, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);

                    glTranslatef(0, n, -m);
                    glPushMatrix();
                    glTranslatef(c, d, 0);
                    glRotated(-90, 1, 0, 0);
                    Cylinder(R1, L);
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glEndList();
                }



                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + CN;

        }
    }
    if (CN % 2 != 0 && RN % 2 == 0) {
        int a = 1;
        for (int x = -r; x <= r; ++x) {
            int i = a;
            for (int z = -Q; z < Q; ++z) {
                int b = 1100 + z + i;
                GLfloat  n = BL + Q * RS;
                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);

                    glPushMatrix();
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(X2, Z2, Y2);
                    glRotatef(rX2, 1, 0, 0);
                    glRotatef(rY2, 0, 1, 0);
                    glRotatef(rZ2, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X, Z, Y);



                    glTranslatef(0, n, -m);

                    glPushMatrix();

                    glTranslatef(x * CS, (2 * z + 1) * RS / 2, 0);

                    glRotated(-90, 1, 0, 0);

                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);

                    Cylinder(R1, L);

                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + RN;
        }

    }
    if (CN % 2 != 0 && RN % 2 != 0) {
        int a = 1;
        for (int x = -r; x <= r; ++x) {
            int i = a;
            for (int z = -s; z <= s; ++z) {
                GLfloat  n = BL + s * RS;
                int b = 1100 + z + i;
                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);

                    glPushMatrix();
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(X2, Z2, Y2);
                    glRotatef(rX2, 1, 0, 0);
                    glRotatef(rY2, 0, 1, 0);
                    glRotatef(rZ2, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);


                    glTranslatef(0, n, -m);

                    glPushMatrix();

                    glTranslatef(x * CS, z * RS, 0);
                    glRotated(-90, 1, 0, 0);
                    Cylinder(R1, L);
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + RN;
        }

    }

    OpenCSG::render(primitives);
    glDepthFunc(GL_EQUAL);
    for (std::vector<OpenCSG::Primitive*>::const_iterator j = primitives.begin(); j != primitives.end(); ++j) {
        (*j)->render();
    }
    glDepthFunc(GL_LESS);
    glPopMatrix();


}
void myopengl::TerminalBlock2(GLfloat L, GLfloat W, GLfloat T, GLfloat CL, GLfloat CS, GLfloat RS, GLfloat R1, int CN, int RN, GLfloat BL, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ, GLfloat X2, GLfloat Y2, GLfloat Z2, GLfloat rX2, GLfloat rY2, GLfloat rZ2, GLfloat X1, GLfloat Y1, GLfloat Z1, GLfloat rX1, GLfloat rY1, GLfloat rZ1)
{
    glPushMatrix();
    clearPrimtives();
    GLfloat  m = T + 0.5;
    GLfloat Q = RN / 2;
    GLfloat r = (CN - 1) / 2;

    GLfloat P = CN / 2;
    GLfloat s = (RN - 1) / 2;

    if (!glIsList((GLuint)(1002))) {

        glNewList(1002, GL_COMPILE);
        glPushMatrix();
        glScalef(ScalefX, ScalefY, ScalefZ);
        glTranslatef(X2, Z2, Y2);
        glRotatef(rX2, 1, 0, 0);
        glRotatef(rY2, 0, 1, 0);
        glRotatef(rZ2, 0, 0, 1);
        glPushMatrix();
        glTranslatef(X1, Z1, Y1);
        glRotatef(rX1, 1, 0, 0);
        glRotatef(rY1, 0, 1, 0);
        glRotatef(rZ1, 0, 0, 1);
        glPushMatrix();

        glTranslatef(X, Z, Y);
        glRotatef(rX, 1, 0, 0);
        glRotatef(rY, 0, 1, 0);
        glRotatef(rZ, 0, 0, 1);
        IrregularCuboid(L, W, T, CL);
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
        glEndList();
    }
    primitives.push_back(new OpenCSG::DisplayListPrimitive(1002, OpenCSG::Intersection, 1));
    if (CN % 2 == 0 && RN % 2 != 0) {
        int a = 1;
        for (int x = -P; x < P; ++x) {
            int i = a;
            for (int z = -s; z <= s; ++z) {
                GLfloat  o = BL + s * RS;
                int b = 1100 + z + i;
                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);

                    glPushMatrix();
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(X2, Z2, Y2);
                    glRotatef(rX2, 1, 0, 0);
                    glRotatef(rY2, 0, 1, 0);
                    glRotatef(rZ2, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X1, Z1, Y1);
                    glRotatef(rX1, 1, 0, 0);
                    glRotatef(rY1, 0, 1, 0);
                    glRotatef(rZ1, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);

                    glTranslatef(0, o, -m);
                    glPushMatrix();
                    glTranslatef((2 * x + 1) * CS / 2, z * RS, 0);
                    glRotated(-90, 1, 0, 0);
                    Cylinder(R1, L);
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + RN;
        }

    }
    if (CN % 2 == 0 && RN % 2 == 0) {
        int a = 4;


        for (int x = -P; x < P; ++x) {

            int i = a;
            for (int z = -Q; z < Q; ++z) {

                GLfloat  n = BL + Q * RS;
                GLfloat c = (2 * x + 1) * CS / 2;
                GLfloat d = (2 * z + 1) * RS / 2;
                int b = 1005 + z + i;



                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);

                    glPushMatrix();
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(X2, Z2, Y2);
                    glRotatef(rX2, 1, 0, 0);
                    glRotatef(rY2, 0, 1, 0);
                    glRotatef(rZ2, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X1, Z1, Y1);
                    glRotatef(rX1, 1, 0, 0);
                    glRotatef(rY1, 0, 1, 0);
                    glRotatef(rZ1, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);

                    glTranslatef(0, n, -m);
                    glPushMatrix();
                    glTranslatef(c, d, 0);
                    glRotated(-90, 1, 0, 0);
                    Cylinder(R1, L);
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glEndList();
                }



                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + CN;

        }
    }
    if (CN % 2 != 0 && RN % 2 == 0) {
        int a = 1;
        for (int x = -r; x <= r; ++x) {
            int i = a;
            for (int z = -Q; z < Q; ++z) {
                int b = 1100 + z + i;
                GLfloat  n = BL + Q * RS;
                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);

                    glPushMatrix();
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(X2, Z2, Y2);
                    glRotatef(rX2, 1, 0, 0);
                    glRotatef(rY2, 0, 1, 0);
                    glRotatef(rZ2, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X1, Z1, Y1);
                    glRotatef(rX1, 1, 0, 0);
                    glRotatef(rY1, 0, 1, 0);
                    glRotatef(rZ1, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glTranslatef(0, n, -m);

                    glPushMatrix();

                    glTranslatef(x * CS, (2 * z + 1) * RS / 2, 0);

                    glRotated(-90, 1, 0, 0);

                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);

                    Cylinder(R1, L);

                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + RN;
        }

    }
    if (CN % 2 != 0 && RN % 2 != 0) {
        int a = 1;
        for (int x = -r; x <= r; ++x) {
            int i = a;
            for (int z = -s; z <= s; ++z) {
                GLfloat  n = BL + s * RS;
                int b = 1100 + z + i;
                if (!glIsList((GLuint)(b))) {
                    glNewList(b, GL_COMPILE);

                    glPushMatrix();
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(X2, Z2, Y2);
                    glRotatef(rX2, 1, 0, 0);
                    glRotatef(rY2, 0, 1, 0);
                    glRotatef(rZ2, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X1, Z1, Y1);
                    glRotatef(rX1, 1, 0, 0);
                    glRotatef(rY1, 0, 1, 0);
                    glRotatef(rZ1, 0, 0, 1);
                    glPushMatrix();
                    glTranslatef(X, Z, Y);
                    glRotatef(rX, 1, 0, 0);
                    glRotatef(rY, 0, 1, 0);
                    glRotatef(rZ, 0, 0, 1);


                    glTranslatef(0, n, -m);

                    glPushMatrix();

                    glTranslatef(x * CS, z * RS, 0);
                    glRotated(-90, 1, 0, 0);
                    Cylinder(R1, L);
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glPopMatrix();
                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(b, OpenCSG::Subtraction, 1));

            }
            a = a + RN;
        }

    }

    OpenCSG::render(primitives);
    glDepthFunc(GL_EQUAL);
    for (std::vector<OpenCSG::Primitive*>::const_iterator j = primitives.begin(); j != primitives.end(); ++j) {
        (*j)->render();
    }
    glDepthFunc(GL_LESS);
    glPopMatrix();


}
void myopengl::Wire(QString StartVector, QString EndVector, QString FitCoordArray, QString StartCoord, QString EndCoord, GLfloat D, GLfloat Sag)
{ //读StartVector的坐标
    QStringList StartVectorsplits = StartVector.split(",");
    int size1 = 3;
    double* vector1 = new double[size1]();
    vector1[0] = (StartVectorsplits[0]).toDouble();
    vector1[1] = (StartVectorsplits[1]).toDouble();
    vector1[2] = (StartVectorsplits[2]).toDouble();
    //读EndVector的坐标
    QStringList EndVectorsplits = EndVector.split(",");
    double* vector2 = new double[size1]();
    vector2[0] = (EndVectorsplits[0]).toDouble();
    vector2[1] = (EndVectorsplits[1]).toDouble();
    vector2[2] = (EndVectorsplits[2]).toDouble();
    //读StartCoord的坐标
    QStringList StartCoordsplits = StartCoord.split(",");
    double* vector3 = new double[size1]();
    vector3[0] = (StartCoordsplits[0]).toDouble();
    vector3[1] = (StartCoordsplits[1]).toDouble();
    vector3[2] = (StartCoordsplits[2]).toDouble();
    //读EndCoord的坐标
    QStringList EndCoordsplits = EndCoord.split(",");
    double* vector4 = new double[size1]();
    vector4[0] = (EndCoordsplits[0]).toDouble();
    vector4[1] = (EndCoordsplits[1]).toDouble();
    vector4[2] = (EndCoordsplits[2]).toDouble();
    //把FitCoordArray的坐标放进vectorX、vectorY、vectorZ数组中
    QStringList FitCoordArraysplits = FitCoordArray.split(";");
    int size = FitCoordArraysplits.size();
    double* vectorX = new  double[size]();
    double* vectorY = new  double[size]();
    double* vectorZ = new  double[size]();
    for (int i = 0; i < FitCoordArraysplits.size(); i++) {
        QStringList FitCoordArraysplits1 = FitCoordArraysplits[i].split(",");
        vectorX[i] = FitCoordArraysplits1[0].toFloat();
        vectorY[i] = FitCoordArraysplits1[1].toFloat();
        vectorZ[i] = FitCoordArraysplits1[2].toFloat();
    }
    //画线
    glPushMatrix();
    glLineWidth(D);
    //平移到起始位置，若不平移会在原点画
    glTranslatef(vector3[0], vector3[2], vector3[1]);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < FitCoordArraysplits.size(); i++) {
        glVertex3f(vectorX[i], vectorZ[i], vectorY[i]);
        glVertex3f(vectorX[i + 1], vectorZ[i + 1], vectorY[i + 1]);
        //qDebug() << vectorX[i] << vectorX[i + 1] << endl;
    }
    glEnd();

    glPopMatrix();

}
void myopengl::Cable(QString InflectionCoordArray, QString StartCoord, QString EndCoord, GLfloat D, GLfloat IRArray)
{
    //把FitCoordArray的坐标放进vectorX、vectorY、vectorZ数组中
    QStringList InflectionCoordArraysplits = InflectionCoordArray.split(";");
    int size = InflectionCoordArraysplits.size() + 2;
    double* vectorX = new  double[size]();
    double* vectorY = new  double[size]();
    double* vectorZ = new  double[size]();
    //把StartCoord的坐标放进vectorX、vectorY、vectorZ
    int size1 = 3;
    //QStringList StartCoordsplits = StartCoord.split(",");
    ////double* vector1 = new double[size1]();
    //vectorX[0] = (StartCoordsplits[0]).toDouble();
    //vectorY[0] = (StartCoordsplits[1]).toDouble();
    //vectorZ[0] = (StartCoordsplits[2]).toDouble();
    QStringList EndCoordsplits1 = EndCoord.split(",");
    double* vector2 = new double[size1]();
    vector2[0] = (EndCoordsplits1[0]).toDouble();
    vector2[1] = (EndCoordsplits1[1]).toDouble();
    vector2[2] = (EndCoordsplits1[2]).toDouble();
    QStringList StartCoordsplits1 = StartCoord.split(",");
    double* vector1 = new double[size1]();
    vector1[0] = (StartCoordsplits1[0]).toDouble();
    vector1[1] = (StartCoordsplits1[1]).toDouble();
    vector1[2] = (StartCoordsplits1[2]).toDouble();

   /* int z = InflectionCoordArraysplits.size() + 1;
    for (int i = 1; i < InflectionCoordArraysplits.size() + 1; i++) {

        QStringList InflectionCoordArraysplits1 = InflectionCoordArraysplits[i - 1].split(",");
        vectorX[i] = InflectionCoordArraysplits1[0].toDouble();
        vectorY[i] = InflectionCoordArraysplits1[1].toDouble();
        vectorZ[i] = InflectionCoordArraysplits1[2].toDouble();
    }*/
   // //把EndCoord的坐标放进vectorX、vectorY、vectorZ
    //for (int i = InflectionCoordArraysplits.size() + 1; i < InflectionCoordArraysplits.size() + 2; i++) {
    //    //int m = i-i;
    //    vectorX[i] = vector2[0];
    //    vectorY[i] = vector2[1];
    //    vectorZ[i] = vector2[2];
    //    //qDebug() << vectorX[i] << vectorY[i] << vectorZ[i] << endl;
    //}



    //for (int i = 0; i < InflectionCoordArraysplits.size() + 2; i++) {
    //    //qDebug() << vectorX[i] << vectorY[i] << vectorZ[i] << endl;
    //    //qDebug()<< vectorX[i] << vectorY[i] << vectorZ[i] <<endl;
    //  // //
    //    double dx0 = vectorX[i + 1] - vectorX[i];
    //    double dy0 = vectorY[i + 1] - vectorY[i];
    //    double dz0 = vectorZ[i + 1] - vectorZ[i];
    //    double r1 = sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0);
    //    double cx1 = (IRArray * (vectorX[i] - vectorX[i + 1])) / r1 + vectorX[i + 1];
    //    double cy1 = (IRArray * (vectorY[i] - vectorY[i + 1])) / r1 + vectorY[i + 1];
    //    double cz1 = (IRArray * (vectorZ[i] - vectorZ[i + 1])) / r1 + vectorZ[i + 1];
    //    double r2 = sqrt((vectorX[i + 1] - vectorX[i + 2]) * (vectorX[i + 1] - vectorX[i + 2]) + (vectorY[i + 1] - vectorY[i + 2]) * (vectorY[i + 1] - vectorY[i + 2]) + (vectorZ[i + 1] - vectorZ[i + 2]) * (vectorZ[i + 1] - vectorZ[i + 2]));
    //    double cx2 = (IRArray * (vectorX[i + 2] - vectorX[i + 1])) / r1 + vectorX[i + 1];
    //    double cy2 = (IRArray * (vectorY[i + 2] - vectorY[i + 1])) / r1 + vectorY[i + 1];
    //    double cz2 = (IRArray * (vectorZ[i + 2] - vectorZ[i + 1])) / r1 + vectorZ[i + 1];
    //    //求垂足
    //    double dx1 = cx1 - cx2;
    //    double dy1 = cy1 - cy2;
    //    double dz1 = cz1 - cz2;
    //    //qDebug() << dx1 << dy1 << dz1 << endl;
    //    if (abs(dx1) < 0.00000001 && abs(dy1) < 0.00000001 && abs(dz1) < 0.00000001)
    //    {
    //        break;
    //    }
    //    double u = (vectorX[i + 1] - cx1) * (cx1 - cx2) +
    //        (vectorX[i + 1] - cy1) * (cy1 - cy2) + (vectorX[i + 1] - cz1) * (cz1 - cz2);
    //    u /= ((dx1 * dx1) + (dy1 * dy1) + (dz1 * dz1));
    //    //定义数组放垂足
    //    double* vector3 = new double[size1]();
    //    vector3[0] = cx1 + u * dx1;
    //    vector3[1] = cy1 + u * dy1;
    //    vector3[2] = cz1 + u * dz1;
    //    //虚焦点的对称坐标
    //    double* vector4 = new double[size1]();
    //    vector4[0] = 2 * vector3[0] - vectorX[i + 1];
    //    vector4[1] = 2 * vector3[1] - vectorY[i + 1];
    //    vector4[2] = 2 * vector3[2] - vectorZ[i + 1];
    //    //求圆环的夹角的
    //    GLfloat dir_x = vectorX[i + 1] - vector3[0];
    //    GLfloat dir_y = vectorY[i + 1] - vector3[1];
    //    GLfloat dir_z = vectorZ[i + 1] - vector3[2];
    //    double v = sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);//需焦点到垂足的长度
    //    double Rad = 2 * asin(v / IRArray);//得出的角是弧度
    //    //double Rad = 2 * acos(v / IRArray);//得出的角是弧度
    //    //计算圆环初始点与地面的夹角,先转换为角度求余角，在转换为弧度
    //    //double w = 90 - 2 * acos(v / IRArray);
    //   // double theta =(90- Rad *180/PI)*PI/180;
    //    double theta = acos(v / IRArray);
    //    //double theta = asin(v / IRArray);
    //    //弧度转换为角度
    //     //double theta2 = asin(v / IRArray) * 180/PI;
    //     //半圆弧旋转角度

    //    // double theta1 = asin(v / IRArray)*180/PI;
    //    //qDebug()<< theta1 <<endl;
    //    //double w= sqrt((cx2 - vector4[0]) * (cx2 - vector4[0]) + (cy2 - vector4[1]) * (cy2 - vector4[1]) + (cz2 - vector4[2]) * (cz2 - vector4[2]));
    //    //画图
    //    glPushMatrix();
    //    //double IRArray1 = IRArray - 0.075;
    //    //PointsCylinder(vectorX[i], vectorY[i], vectorZ[i], vectorX[i + 1], vectorY[i + 1], vectorZ[i + 1], D, IRArray);
    //    //PointsCylinder(vectorX[i + 2], vectorY[i + 2], vectorZ[i + 2], vectorX[i + 1], vectorY[i + 1], vectorZ[i + 1], D, IRArray);
    //    PointsCylinder(vectorX[i], vectorZ[i], vectorY[i], vectorX[i + 1], vectorZ[i + 1], vectorY[i + 1], D, IRArray);
    //    PointsCylinder(vectorX[i + 2], vectorZ[i + 2], vectorY[i + 2], vectorX[i + 1], vectorZ[i + 1], vectorY[i + 1], D, IRArray);
    //    glPushMatrix();
    //    glTranslatef(vector4[0], vector4[2], vector4[1]);
    //    //glTranslatef(vector4[0], vector4[1], vector4[2]);
    //    GLfloat length;
    //    length = sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);
    //    if (length < 0.0001) {
    //        dir_x = 0.0; dir_y = 0.0; dir_z = 1.0; length = 1.0;
    //    }
    //    dir_x /= length; dir_y /= length; dir_z /= length;
    //    GLdouble up_x, up_y, up_z;
    //    up_x = 0.0;
    //    up_y = 1.0;
    //    up_z = 0.0;
    //    GLdouble side_x, side_y, side_z;
    //    side_x = up_y * dir_z - up_z * dir_y;
    //    side_y = up_z * dir_x - up_x * dir_z;
    //    side_z = up_x * dir_y - up_y * dir_x;
    //    length = sqrt(side_x * side_x + side_y * side_y + side_z * side_z);
    //    if (length < 0.0001) {
    //        side_x = 1.0; side_y = 0.0; side_z = 0.0; length = 1.0;
    //    }
    //    side_x /= length; side_y /= length; side_z /= length;
    //    up_x = dir_y * side_z - dir_z * side_y;
    //    up_y = dir_z * side_x - dir_x * side_z;
    //    up_z = dir_x * side_y - dir_y * side_x;
    //    // 计算变换矩阵 
    //    GLdouble m[16] = { side_x, side_y, -side_z, 0.0,
    //      up_x,  up_y,  -up_z,  0.0,
    //      dir_x, dir_y, -dir_z, 0.0,
    //      0.0,  0.0,  0.0,  1.0 };
    //    glMultMatrixd(m);
    //    Rings(IRArray, D, Rad, theta);
    //    glPopMatrix();
    //    glPopMatrix();
    //}
for (int i = 0; i < InflectionCoordArraysplits.size();i++) {
        QStringList InflectionCoordArraysplits1 = InflectionCoordArraysplits[i].split(",");
        vectorX[i] = InflectionCoordArraysplits1[0].toDouble();
        vectorY[i] = InflectionCoordArraysplits1[1].toDouble();
        vectorZ[i] = InflectionCoordArraysplits1[2].toDouble();
        //
        double dx0 = vectorX[i] - vector1[0];
        double dy0 = vectorY[i] - vector1[1];
        double dz0 = vectorZ[i] - vector1[2];
        double r1 = sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0);
        double cx1 = (IRArray * (vector1[0] - vectorX[i])) / r1 + vectorX[i];
        double cy1 = (IRArray * (vector1[1] - vectorY[i])) / r1 + vectorY[i];
        double cz1 = (IRArray * (vector1[2] - vectorZ[i])) / r1 + vectorZ[i];
        double r2 = sqrt((vectorX[i] - vector2[0]) * (vectorX[i] - vector2[0]) + (vectorY[i] - vector2[1]) * (vectorY[i] - vector2[1]) + (vectorZ[i] - vector2[2]) * (vectorZ[i] - vector2[2]));
        double cx2 = (IRArray * (vector2[0] - vectorX[i])) / r1 + vectorX[i];
        double cy2 = (IRArray * (vector2[1] - vectorY[i])) / r1 + vectorY[i];
        double cz2 = (IRArray * (vector2[2] - vectorZ[i])) / r1 + vectorZ[i];
        //求垂足
        double dx1 = cx1 - cx2;
        double dy1 = cy1 - cy2;
        double dz1 = cz1 - cz2;
        if (abs(dx1) < 0.00000001 && abs(dy1) < 0.00000001 && abs(dz1) < 0.00000001)
        {
             
            return;
        }
        double u = (vectorX[i] - cx1) * (cx1 - cx2) +
            (vectorX[i] - cy1) * (cy1 - cy2) + (vectorX[i] - cz1) * (cz1 - cz2);
        u /= ((dx1 * dx1) + (dy1 * dy1) + (dz1 * dz1));
        //定义数组放垂足
        double* vector3 = new double[size1]();
        vector3[0] = cx1 + u * dx1;
        vector3[1] = cy1 + u * dy1;
        vector3[2] = cz1 + u * dz1;
        //虚焦点的对称坐标
        double* vector4 = new double[size1]();
        vector4[0] = 2 * vector3[0] - vectorX[i];
        vector4[1] = 2 * vector3[1] - vectorY[i];
        vector4[2] = 2 * vector3[2] - vectorZ[i];
        //求圆环的夹角的
        GLfloat dir_x = vectorX[i] - vector3[0];
        GLfloat dir_y = vectorY[i] - vector3[1];
        GLfloat dir_z = vectorZ[i] - vector3[2];
        double v = sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);//需焦点到垂足的长度
        double Rad = 2 * acos(v / IRArray);//得出的角是弧度
        //计算圆环初始点与地面的夹角,先转换为角度求余角，在转换为弧度
        //double w = 90 - 2 * acos(v / IRArray);
       // double theta =(90- Rad *180/PI)*PI/180;
        double theta = asin(v / IRArray);
        //弧度转换为角度
         //double theta2 = asin(v / IRArray) * 180/PI;
         //半圆弧旋转角度
        // double theta1 = asin(v / IRArray)*180/PI;
        //qDebug()<< theta1 <<endl;
        //double w= sqrt((cx2 - vector4[0]) * (cx2 - vector4[0]) + (cy2 - vector4[1]) * (cy2 - vector4[1]) + (cz2 - vector4[2]) * (cz2 - vector4[2]));
        //画图
        glPushMatrix();
        double IRArray1 = IRArray - 0.05;
        PointsCylinder(vector1[0], vector1[2], vector1[1], vectorX[i], vectorZ[i], vectorY[i], D, IRArray1);
        PointsCylinder(vector2[0], vector2[2], vector2[1], vectorX[i], vectorZ[i], vectorY[i], D, IRArray1);
        glPushMatrix();
        glTranslatef(vector4[0], vector4[2], vector4[1]);
        GLfloat length;
        length = sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);
        if (length < 0.0001) {
            dir_x = 0.0; dir_y = 0.0; dir_z = 1.0; length = 1.0;
        }
        dir_x /= length; dir_y /= length; dir_z /= length;
        GLdouble up_x, up_y, up_z;
        up_x = 0.0;
        up_y = 1.0;
        up_z = 0.0;
        GLdouble side_x, side_y, side_z;
        side_x = up_y * dir_z - up_z * dir_y;
        side_y = up_z * dir_x - up_x * dir_z;
        side_z = up_x * dir_y - up_y * dir_x;
        length = sqrt(side_x * side_x + side_y * side_y + side_z * side_z);
        if (length < 0.0001) {
            side_x = 1.0; side_y = 0.0; side_z = 0.0; length = 1.0;
        }
        side_x /= length; side_y /= length; side_z /= length;
        up_x = dir_y * side_z - dir_z * side_y;
        up_y = dir_z * side_x - dir_x * side_z;
        up_z = dir_x * side_y - dir_y * side_x;
        // 计算变换矩阵 
        GLdouble m[16] = { side_x, side_y, -side_z, 0.0,
          up_x,  up_y,  -up_z,  0.0,
          dir_x, dir_y, -dir_z, 0.0,
          0.0,  0.0,  0.0,  1.0 };
        glMultMatrixd(m);
        Rings(IRArray, D, Rad, theta);
        glPopMatrix();
        glPopMatrix();
    }
       
}
void myopengl::PointsCylinder(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat D, GLfloat IRArray)
{
    GLfloat radius = D / 2;
    GLfloat dir_x = x1 - x0;
    GLfloat dir_y = y1 - y0;
    GLfloat dir_z = z1 - z0;
    GLfloat length1 = sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);
    GLfloat length2 = length1 - IRArray;
    GLUquadricObj* qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);

    glPushMatrix();

    // 平移到起始点 
    glTranslated(x0, y0, z0);
    // 计算长度 
    GLfloat length;
    length = sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);
    if (length < 0.0001) {
        dir_x = 0.0; dir_y = 0.0; dir_z = 1.0; length = 1.0;
    }
    dir_x /= length; dir_y /= length; dir_z /= length;
    GLdouble up_x, up_y, up_z;
    up_x = 0.0;
    up_y = 1.0;
    up_z = 0.0;
    GLdouble side_x, side_y, side_z;
    side_x = up_y * dir_z - up_z * dir_y;
    side_y = up_z * dir_x - up_x * dir_z;
    side_z = up_x * dir_y - up_y * dir_x;
    length = sqrt(side_x * side_x + side_y * side_y + side_z * side_z);
    if (length < 0.0001) {
        side_x = 1.0; side_y = 0.0; side_z = 0.0; length = 1.0;
    }
    side_x /= length; side_y /= length; side_z /= length;
    up_x = dir_y * side_z - dir_z * side_y;
    up_y = dir_z * side_x - dir_x * side_z;
    up_z = dir_x * side_y - dir_y * side_x;
    // 计算变换矩阵 
    GLdouble m[16] = { side_x, side_y, side_z, 0.0,
      up_x,  up_y,  up_z,  0.0,
      dir_x, dir_y, dir_z, 0.0,
      0.0,  0.0,  0.0,  1.0 };
    glMultMatrixd(m);
    //Cylinder(radius, length2);
    //glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(qobj, D, D, length2, 32, 32);
    gluDeleteQuadric(qobj);
    glPopMatrix();

}
void myopengl::RectangularFixedPlate(GLfloat L, GLfloat W, GLfloat T, GLfloat CS, GLfloat RS, int CN, int RN, int MH, GLfloat D, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ)
{
    glPushMatrix();
    clearPrimtives();
    GLfloat m = T + 0.5;
    GLfloat n = (CN - 1) / 2;
    GLfloat p = (RN - 1) / 2;
    GLfloat q = CN / 2;
    GLfloat r = RN / 2;
    if (!glIsList((GLuint)(1300))) {
        glNewList(1300, GL_COMPILE);
        //GLuint id100000007 = glGenLists(1);
       //glNewList(id100000007, GL_COMPILE);
        glPushMatrix();
        glScalef(ScalefX, ScalefY, ScalefZ);
        glTranslatef(X, Z, Y);
        Cuboid(L, W, T);//长，宽，高
        glPopMatrix();
        glEndList();
    }
    primitives.push_back(new OpenCSG::DisplayListPrimitive(1300, OpenCSG::Intersection, 1));

    if (CN % 2 != 0 && RN % 2 != 0) {
        //int a = 1;
        for (int x = -n; x <= n; ++x) {
            //int i = a;
            for (int z = -p; z <= p; ++z) {
                if (MH == 1) {
                    //int b = 1100 + z + i;
                    if (!glIsList((GLuint)(1301))) {
                        glNewList(1301, GL_COMPILE);
                        //GLuint id100000008 = glGenLists(1);
                        //glNewList(id100000008, GL_COMPILE);
                        glPushMatrix();
                        glScalef(ScalefX, ScalefY, ScalefZ);
                        glTranslatef(X, Z, Y);
                        glTranslatef(x * CS, m, z * RS);
                        //glRotated(-90, 1, 0, 0);
                        //glRotatef(90, 1.0F, 0.0F, 0.0F);
                        Cylinder(D, T + 1);
                        glPopMatrix();
                        glEndList();
                    }
                    primitives.push_back(new OpenCSG::DisplayListPrimitive(1301, OpenCSG::Subtraction, 1));
                }
                else {
                    if (x == 0 && z == 0) {
                        continue;

                    }
                    //int b = 1100 + z + i;
                    if (!glIsList((GLuint)(1302))) {
                        glNewList(1302, GL_COMPILE);
                        //GLuint id100000009 = glGenLists(1);
                        //glNewList(id100000009, GL_COMPILE);
                        glPushMatrix();
                        glScalef(ScalefX, ScalefY, ScalefZ);
                        glTranslatef(X, Z, Y);
                        glTranslatef(x * CS, m, z * RS);
                        //glRotatef(90, 1.0F, 0.0F, 0.0F);
                        Cylinder(D, T + 1);
                        glPopMatrix();
                        glEndList();
                    }
                    primitives.push_back(new OpenCSG::DisplayListPrimitive(1302, OpenCSG::Subtraction, 1));

                }

            }
            //a = a + RN;
        }
    }

    else {



        for (int x = -q; x < q; ++x) {
            for (int z = -r; z < q; ++z) {
                GLfloat c = (2 * x + 1) * CS / 2;
                GLfloat d = (2 * z + 1) * RS / 2;
                if (MH == 0) {
                    if (!glIsList((GLuint)(1303))) {
                        glNewList(1303, GL_COMPILE);
                        //GLuint id100000010 = glGenLists(1);
                       //glNewList(id100000010, GL_COMPILE);
                        glPushMatrix();
                        glScalef(ScalefX, ScalefY, ScalefZ);
                        glTranslatef(X, Z, Y);
                        glTranslatef(d, m, c);
                        //glRotatef(90, 1.0F, 0.0F, 0.0F);
                        Cylinder(D, T + 1);
                        glPopMatrix();
                        glEndList();
                    }
                    primitives.push_back(new OpenCSG::DisplayListPrimitive(1303, OpenCSG::Subtraction, 1));
                    continue;
                }
                else if (x == 0 && z == 0) {
                    if (!glIsList((GLuint)(1304))) {
                        glNewList(1304, GL_COMPILE);
                        GLuint id100000011 = glGenLists(1);
                        glNewList(id100000011, GL_COMPILE);
                        glPushMatrix();
                        glScalef(ScalefX, ScalefY, ScalefZ);
                        glTranslatef(X, Z, Y);
                        glTranslatef(0, m, 0);
                        glRotatef(90, 1.0F, 0.0F, 0.0F);
                        Cylinder(D, T + 1);
                        glPopMatrix();
                        glEndList();
                    }



                    primitives.push_back(new OpenCSG::DisplayListPrimitive(1304, OpenCSG::Subtraction, 1));



                }
                if (!glIsList((GLuint)(1305))) {
                    glNewList(1305, GL_COMPILE);
                    //GLuint id100000012 = glGenLists(1);
                   // glNewList(id100000012, GL_COMPILE);
                    glPushMatrix();
                    glScalef(ScalefX, ScalefY, ScalefZ);
                    glTranslatef(X, Z, Y);
                    glTranslatef(d, m, c);
                    //glRotatef(90, 1.0F, 0.0F, 0.0F);
                    Cylinder(D, T + 1);
                    glPopMatrix();
                    glEndList();
                }
                primitives.push_back(new OpenCSG::DisplayListPrimitive(1305, OpenCSG::Subtraction, 1));
            }
        }
    }
    glEnable(GL_DEPTH_TEST);
    OpenCSG::render(primitives, OpenCSG::Algorithm::Goldfeather, OpenCSG::DepthComplexityAlgorithm::NoDepthComplexitySampling);

    glDepthFunc(GL_EQUAL);

    for (std::vector<OpenCSG::Primitive*>::const_iterator i = primitives.begin(); i != primitives.end(); ++i) {

        (*i)->render();

    }
    glDepthFunc(GL_LESS);
    glPopMatrix();
}
void myopengl::CircularFixedPlate(GLfloat L, GLfloat W, GLfloat T, GLfloat CS, GLfloat N, int MH, GLfloat D, GLfloat X, GLfloat Y, GLfloat Z, GLfloat rX, GLfloat rY, GLfloat rZ)
{
    glPushMatrix();
    clearPrimtives();

    GLfloat n = T + 0.5;
    GLfloat m = 2 * PI / N;
    //if (!glIsList((GLuint)(100000013))) {
    GLuint id100000013 = glGenLists(1);
    glNewList(id100000013, GL_COMPILE);
    glPushMatrix();
    glScalef(ScalefX, ScalefY, ScalefZ);
    glTranslatef(X, Z, Y);
    Cuboid(L, W, T);//长，宽，高
    glPopMatrix();
    glEndList();
    //}
    primitives.push_back(new OpenCSG::DisplayListPrimitive(id100000013, OpenCSG::Intersection, 1));

    for (int x = 1; x <= N; ++x) {
        if (MH == 1) {
            //if (!glIsList((GLuint)(100000014))) {
            GLuint id100000014 = glGenLists(1);
            glNewList(id100000014, GL_COMPILE);
            glPushMatrix();
            glScalef(ScalefX, ScalefY, ScalefZ);
            glTranslatef(X, Z, Y);
            glTranslatef(0, n, 0);
            glRotatef(90, 1.0F, 0.0F, 0.0F);
            Cylinder(D, T + 1);
            glPopMatrix();
            glEndList();
            // }

             //if (!glIsList((GLuint)(100000015))) {
            GLuint id100000015 = glGenLists(1);
            glNewList(id100000015, GL_COMPILE);
            glPushMatrix();
            glScalef(ScalefX, ScalefY, ScalefZ);
            glTranslatef(X, Z, Y);
            glTranslatef(CS * cos(m * x), n, CS * sin(m * x));
            glRotatef(90, 1.0F, 0.0F, 0.0F);
            Cylinder(D, T + 1);
            glPopMatrix();
            glEndList();
            //}
            primitives.push_back(new OpenCSG::DisplayListPrimitive(id100000014, OpenCSG::Subtraction, 1));
            primitives.push_back(new OpenCSG::DisplayListPrimitive(id100000015, OpenCSG::Subtraction, 1));
        }
        else {
            //if (!glIsList((GLuint)(100000016))) {
            GLuint id100000016 = glGenLists(1);
            glNewList(id100000016, GL_COMPILE);
            glPushMatrix();
            glScalef(ScalefX, ScalefY, ScalefZ);
            glTranslatef(X, Z, Y);
            glTranslatef(CS * cos(m * x), n, CS * sin(m * x));
            glRotatef(90, 1.0F, 0.0F, 0.0F);
            Cylinder(D, T + 1);
            glPopMatrix();
            glEndList();
            //}
            primitives.push_back(new OpenCSG::DisplayListPrimitive(id100000016, OpenCSG::Subtraction, 1));

        }
    }

    glEnable(GL_DEPTH_TEST);
    OpenCSG::render(primitives, OpenCSG::Algorithm::Goldfeather, OpenCSG::DepthComplexityAlgorithm::NoDepthComplexitySampling);

    glDepthFunc(GL_EQUAL);

    for (std::vector<OpenCSG::Primitive*>::const_iterator i = primitives.begin(); i != primitives.end(); ++i) {

        (*i)->render();

    }
    glDepthFunc(GL_LESS);
    glPopMatrix();
}
void myopengl::processHits(GLint hits, GLuint selectBuffer[])
{
    GLint i;
    GLuint name;
    for (i = 0; i < hits; i++)
    {
        name = selectBuffer[3 + i * 4];
        select_point = name;//每个选中物体有占用名字栈中4个单位，第4个是物体名字值
        qDebug() << "第" << name << "个点" << endl;
    }
}





