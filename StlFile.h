#pragma once
#include <QtCore/qstring.h>

#include"GimFile.h"

class StlFile :public GimFile
{
public:


    QString getColor() {
        return color;
    }

    void setColor(QString color) {
        this->color = color;
    }

    QString getTransformMatrix() {
        return transformMatrix;
    }

    void setTransformMatrix(QString transformMatrix) {
        this->transformMatrix = transformMatrix;
    }



private:


    QString color;

    QString transformMatrix;
};


