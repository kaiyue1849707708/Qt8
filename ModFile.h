#pragma once
#include "SimpleEntity.h"
#include "BoolEntity.h"
#include"GimFile.h"
#include"QtCore/qlist.h"
class ModFile :public GimFile
{
public:




    QString getf1SysFileName() {
        return f1SysFileName;
    }
    void setf1SysFileName(QString f1SysFileName) {
        this->f1SysFileName = f1SysFileName;
    }
    QList<SimpleEntity> getSimpleEntities() {
        return simpleEntities;
    }
    void setSimpleEntities(QList<SimpleEntity> simpleEntities) {
        this->simpleEntities = simpleEntities;
    }
    QList<BoolEntity> getBoolEntities() {
        return boolEntities;
    }

    void setBoolEntities(QList<BoolEntity> boolEntities) {
        this->boolEntities = boolEntities;
    }
    QString getf2SysFileName() {
        return f2SysFileName;
    }
    void setParent(QString f2SysFileName) {
        this->f2SysFileName = f2SysFileName;
    }
    QString getpartIndexFileName() {
        return partIndexFileName;
    }
    void setpartIndexFileName(QString partIndexFileName) {
        this->partIndexFileName = partIndexFileName;
    }
    QString getf3SysFileName() {
        return f3SysFileName;
    }
    void setf3SysFileName(QString f3SysFileName) {
        this->f3SysFileName = f3SysFileName;
    }
    QString getf4SysFileName() {
        return f4SysFileName;
    }
    void setf4SysFileName(QString f4SysFileName) {
        this->f4SysFileName = f4SysFileName;
    }
    QString getobjFileName() {
        return objFileName;
    }
    void setobjFileName(QString objFileName) {
        this->objFileName = objFileName;
    }
    QString getSymbolName() {
        return SymbolName;
    }
    void setSymbolName(QString SymbolName) {
        this->SymbolName = SymbolName;
    }
    void settransformMatrix1(QString transformMatrix1) {
        this->transformMatrix1 = transformMatrix1;
    };
    QString gettransformMatrix1() {
        return transformMatrix1;
    }
    void settransformMatrix2(QString transformMatrix2) {
        this->transformMatrix2 = transformMatrix2;
    };
    QString gettransformMatrix2() {
        return transformMatrix2;
    }
private:
    ////********** phm下读取内容
    //SolidModel<class T> parent;
    ////mod的文件名
    //QString modFileName;
    //
    ////空间变换矩阵
    //QString transformMatrix;
    ////颜色
    //QString color;
     //********** .mod下读取内容
     //类型为simple的entity
    QList<SimpleEntity> simpleEntities;
    //类型为boolean的entity
    QList<BoolEntity> boolEntities;
    QString SymbolName;
    QString transformMatrix1;
    QString transformMatrix2;

    QString f1SysFileName;
    QString f2SysFileName;
    QString f3SysFileName;
    QString f4SysFileName;
    QString partIndexFileName;
    QString objFileName;
};





