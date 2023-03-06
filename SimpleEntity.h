#pragma once
#include "BoolEntity.h"
#include "BoolEntity.h"
#include <winioctl.h>

#include<list>
#include <QtGui/qevent.h>
#include<iostream>
#include <QtXml/qdom.h>
using namespace std;
class SimpleEntity
{
public:

    // void display() {
    //     qDebug() << "id: " << entityId << endl;
    //     qDebug() << "�Ƿ���ʾ:   " << visible << endl;
    //     qDebug() << "����:    " << &transformMatrix << endl;
    //     qDebug() << "RGBA:" << R << G << B << A << endl;
    //     qDebug() << "ͼԪ: " << graphicElement.nodeName() << endl;
    //
    //
    //
    //     for (int i = 0; i < graphicElement.attributes().length(); i++) {
    //
    //         qDebug() << &graphicElement.attributes().item(i) << endl;
    //     }
    //
    // }


    int getEntityId() {

        return entityId;
    }

    void setEntityId(int entityId) {
        this->entityId = entityId;
    }

    QString getVisible() {
        return visible;
    }

    void setVisible(QString visible) {
        this->visible = visible;
    }


    QString getTransformMatrix() {
        return transformMatrix;
    }

    void setTransformMatrix(QString transformMatrix) {
        this->transformMatrix = transformMatrix;
    }

    QDomNode getGraphicElement() {
        return graphicElement;
    }

    void setGraphicElement(QDomNode graphicElement) {
        this->graphicElement = graphicElement;
    }

    int getR() {
        return R;
    }

    void setR(int R) {
        this->R = R;
    }

    int getG() {
        return G;
    }

    void setG(int G) {
        this->G = G;
    }

    int getB() {
        return B;
    }

    void setB(int B) {
        this->B = B;
    }

    int getA() {
        return A;
    }

    void setA(int A) {
        this->A = A;
    }

private:
    int entityId;

    QString visible;// �Ƿ���ʾ

    QString transformMatrix;

    QDomNode graphicElement;

    int R;
    int G;
    int B;
    int A;

};


