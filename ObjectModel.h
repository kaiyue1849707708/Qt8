#pragma once
#include <QtCore/qstring.h>
#include"GimFile.h"
#include"QtCore/qlist.h"

class ObjectModel :public GimFile
{
public:


    QString getfamFileName() {
        return famFileName;
    }
    void setfamFileName(QString famFileName) {
        this->famFileName = famFileName;
    }
    QString getSymbolName() {
        return symbolName;
    }
    void setSymbolName(QString symbolName) {
        this->symbolName = symbolName;
    }
    QList<QString> getSubObjectModels() {
        return subObjectModels;
    }
    void setSubObjectModels(QList<QString> subObjectModels) {
        this->subObjectModels = subObjectModels;
    }
    QList<QString> getSolidModels() {
        return solidModels;
    }
    void setSolidModels(QList<QString> solidModels) {
        this->solidModels = solidModels;
    }
    QList<QString> getsubObjTransformMatrix() {
        return subObjTransformMatrix;
    }
    void setsubObjTransformMatrix(QList<QString> subObjTransformMatrix) {
        this->subObjTransformMatrix = subObjTransformMatrix;
    }
    QList<QString> getsolidTransformMatrix() {
        return solidTransformMatrix;
    }
    void setsolidTransformMatrix(QList<QString> solidTransformMatrix) {
        this->solidTransformMatrix = solidTransformMatrix;
    }
private:
    //********** 四级设备级.cbm/部件索引.cbm/物理模型.dev下读取内容
    //F4System parent;

      //物理模型fam的内容
    QString famFileName;



    //dev对应的电气设备的模型名称
    QString symbolName;


    //引用的次级物理模型dev
    QList<QString> subObjectModels;
    QList<QString> subObjTransformMatrix;

    //次级物理模型的空间变换矩阵

//引用的phm文件
    QList<QString> solidModels;
    QList<QString> solidTransformMatrix;

    //    //phm模型的空间变换矩阵
    //    private List<String> transformMatrixPHM;
};




