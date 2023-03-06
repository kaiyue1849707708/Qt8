#pragma once
#include <QtCore/qstring.h>
#include"GimFile.h"
#include"QtCore/qlist.h"
using namespace std;
class F2System :public GimFile
{
public:

    //void display() {
    //    qDebug() << "二级全站级cbm的文件名:   " << f2FileName << endl;
    //    qDebug() << "二级系统级的类型:  " << sysClassifyName << endl;
    //    qDebug() << "二级系统级fam的内容↓" << f1FileName << endl;
    //
    //    if (f2Paras.size() != QString::null) {
    //        for (TripletPara f2Para : f2Paras) {
    //
    //            qDebug() << " " << &f2Para << endl;
    //        }
    //    }
    //
    //    qDebug() << "三级子系统级cbm的数量:    " << subSystems.size() << endl;
    //    for (F3System f3System : subSystems) {
    //
    //        qDebug() << &f3System << endl;
    //    }
    //
    //
    //    qDebug() << "补充材料单：" << materialSheet << endl;
    //
    //}
    QString getfamFileName() {
        return famFileName;
    }
    void setfamFileName(QString famFileName) {
        this->famFileName = famFileName;
    }
    QString getSysClassifyName() {
        return sysClassifyName;
    }
    void setSysClassifyName(QString sysClassifyName) {
        this->sysClassifyName = sysClassifyName;
    }

    QList<QString> getSubSystems() {
        return subSystems;
    }
    void setSubSystems(QList<QString> subSystems) {
        this->subSystems = subSystems;
    }
    QList< QString> getIfcFiles()
    {
        return ifcFiles;
    }
    void setIfcFiles(QList<QString> ifcFiles) {
        this->ifcFiles = ifcFiles;
    }
    QString getMaterialSheet() {
        return materialSheet;
    }
    void setMaterialSheet(QString materialSheet) {
        this->materialSheet = materialSheet;
    }

private:
    //********** 一级全站级.cbm下读取内容
    //F1System parent;

    // 二级系统级.cbm的文件名
    QString famFileName;

    //********** 二级系统级.cbm下读取内容

    //二级系统级的类型
    QString sysClassifyName;

    //二级系统级.fam的内容
    //QList<TripletPara> f2Paras;

    //引用的三级子系统级
    QList<QString> subSystems;

    //引用的ifc文件
    QList<QString> ifcFiles;

    //补充材料xml
    QString materialSheet;




};




