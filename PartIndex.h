#pragma once
#include <QtCore/qstring.h>

#include"GimFile.h"
#include <QtCore/QDebug>




class PartIndex : public GimFile
{
public:


    QString getPartName() {
        return partName;
    }

    void setPartName(QString partName) {
        this->partName = partName;
    }



    QString getObjectModel() {
        return objectModel;
    }

    void setObjectModel(QString objectModel) {
        this->objectModel = objectModel;
    }
    QString getfamFileName() {
        return famFileName;
    }

    void setfamFileName(QString famFileName) {
        this->famFileName = famFileName;
    }


private:
    //********** 四级设备级.cbm下读取内容
   // F4System parent;
    // 部件索引.cbm的文件名
    //QString partIndexFileName;

    //********** 部件索引.cbm下读取内容

    //部件索引的类型
    QString partName;

    //部件索引.fam的内容
    QString famFileName;

    //引用的物理模型dev
    QString objectModel;


};


