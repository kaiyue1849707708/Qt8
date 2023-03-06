#pragma once

#include"GimFile.h"
#include"QtCore/qlist.h"
class SolidModel : public GimFile
{
public:
    SolidModel()
    {
        QList<QString> colorList;
        QList<QString> transformMatrixList;
        QList<QString> children;

    }
    QList<QString> getcolorList() {
        return colorList;
    }

    void setcolorList(QList<QString> colorList) {
        colorList = colorList;
    }

    QList<QString> gettransformMatrixList() {
        return transformMatrixList;
    }

    void settransformMatrixList(QList<QString> transformMatrixList) {
        this->transformMatrixList = transformMatrixList;
    }
    QList<QString> getchildren() {
        return children;
    }

    void setchildren(QList<QString> children) {
        this->children = children;
    }
private:
    //********** 物理模型.dev下/组合模型文件.phm读取内容
   // ObjectModel parent;
    //组合模型文件phm的文件名
    //QString phmFileName;

    //phm模型的空间变换矩阵
   // QString transformMatrix;

    //颜色
    //QString color;

    //********** 组合模型文件.phm下读取内容

    //phm
   // QList<SolidModel> solidModelList;

    //mod
   // QList<ModFile> modFileList;

    //stl
   // QList<StlFile> stlFileList;
    QList<QString> colorList;
    QList<QString> transformMatrixList;
    QList<QString> children;


};


