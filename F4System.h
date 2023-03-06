#pragma once
#include <QtCore/QDebug.h>
#include"GimFile.h"
#include "QtCore/qlist.h"
using namespace std;
class  F4System : public GimFile
{
public:


    QString getsysClassifyName() {
        return sysClassifyName;
    }
    void setsysClassifyName(QString sysClassifyName) {
        this->sysClassifyName = sysClassifyName;
    }
    QString getfamFileName() {
        return famFileName;
    }
    void setfamFileName(QString famFileName) {
        this->famFileName = famFileName;
    }

    QString getTransformMatrix() {
        return transformMatrix;
    }
    void setTransformMatrix(QString transformMatrix) {
        this->transformMatrix = transformMatrix;
    }
    QString getObjectModel() {
        return objectModel;
    }
    void setObjectModel(QString objectModel) {
        this->objectModel = objectModel;
    }
    QList<QString> getSubDevice() {
        return subDevice;
    }
    void setSubDevice(QList<QString> subDevice) {
        this->subDevice = subDevice;
    }
    QList<QString> getSubLogicalModels() {
        return subLogicalModels;
    }
    void setSubLogicalModels(QList<QString> subLogicalModels) {
        this->subLogicalModels = subLogicalModels;
    }

private:
    //********** 三级子系统级.cbm下读取内容
   // F3System parent;
    // 四级设备级.cbm的文件名
    //QString f4FileName;

    //********** 四级设备级.cbm下读取内容

    //四级设备级的类型
    QString sysClassifyName;

    //设备相对于变电站原点的空间变换矩阵
    QString transformMatrix;

    //四级设备级.fam的内容
    QString famFileName;

    //引用的物理模型dev
    QString  objectModel;
    //引用的部件索引cbm

    QList<QString> subDevice;

    //引用的逻辑模型cbm
    QList<QString> subLogicalModels;

};










