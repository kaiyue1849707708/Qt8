#pragma once
//#include<glm/mat4x4.hpp>
#include <QtCore/qstring.h>
//#include <QtCore/QDebug>
using namespace std;
class BoolEntity
{
public:


    void setEntityId(int entityId) {
        this->entityId = entityId;
    }
    int getEntityId() {
        return entityId;
    }


    void setVisible(QString visible) {
        this->visible = visible;
    }
    QString getVisible() {
        return visible;
    }
    void setTransformMatrix(QString transformMatrix) {
        this->transformMatrix = transformMatrix;
    };
    QString getTransformMatrix() {
        return transformMatrix;
    }
    void setBoolType(QString boolType) {
        this->boolType = boolType;
    }
    QString getBoolType() {
        return boolType;
    }

    void setBoolEntityId1(int boolEntityId1) {
        this->boolEntityId1 = boolEntityId1;
    }
    int getBoolEntityId1() {
        return boolEntityId1;
    }

    void setBoolEntityId2(int boolEntityId2) {
        this->boolEntityId2 = boolEntityId2;
    }
    int getBoolEntityId2() {
        return boolEntityId2;
    }
    void setR(int R) {
        this->R = R;
    }
    int getR() {
        return R;
    }
    void setG(int G) {
        this->G = G;
    }
    int getG() {
        return G;
    }
    void setB(int B) {
        this->B = B;
    }
    int getB() {
        return B;
    }
    void setA(int A) {
        this->A = A;
    }
    int getA() {
        return A;
    }


private:
    int entityId;

    QString visible;

    QString transformMatrix;

    QString boolType; //Intersection——求交，Union——求并，Difference——求差
    int boolEntityId1;
    int boolEntityId2;

    int R;
    int G;
    int B;
    int A;

};



