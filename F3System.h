#pragma once
#include <QtCore/QDebug.h>
#include"QtCore/qlist.h"
#include"GimFile.h"
using namespace std;
class  F3System : public GimFile
{
public:

    //void display() {
    //    qDebug() << "三级子系统级cbm的文件名:    " << f3FileName << endl;
    //    qDebug() << "三级子系统级的类型:   " << sysClassifyName << endl;
    //    qDebug() << "三级子系统级的名称1: " << sysName1 << endl;
    //    qDebug() << "三级子系统级的名称2:  " << sysName2 << endl;
    //    qDebug() << "三级子系统级的名称3: " << sysName3 << endl;
    //    qDebug() << "三级子系统级fam1的内容↓" << endl;
    //
    //    if (f3Paras1.size() != QString::null) {
    //        for (TripletPara f3Para : f3Paras1) {
    //
    //            qDebug() << "  " << &f3Para << endl;
    //        }
    //    }
    //
    //    qDebug() << "三级子系统级fam1的内容↓" << endl;
    //    if (f3Paras2.size() != QString::null) {
    //        for (TripletPara f3Para : f3Paras2) {
    //            qDebug() << "  " << &f3Para << endl;
    //        }
    //    }
    //    qDebug() << "三级子系统级fam1的内容↓" << endl;
    //    if (f3Paras3.size() != QString::null) {
    //        for (TripletPara f3Para : f3Paras3) {
    //            qDebug() << "  " << &f3Para << endl;
    //        }
    //    }
    //
    //
    //    qDebug() << "四级设备级cbm的数量:    " << subSystems.size() << endl;
    //    for (F4System subSystemFileName : subSystems) {
    //
    //        qDebug() << &subSystemFileName << endl;
    //    }
    //
    //
    //    qDebug() << "补充材料单：" << materialSheet << endl;
    //}
    QString getFamFileName() {
        return famFileName;
    }
    void setFamFileName(QString famFileName) {
        this->famFileName = famFileName;
    }
    QString getSysClassifyName() {
        return sysClassifyName;
    }
    void setSysClassifyName(QString sysClassifyName) {
        this->sysClassifyName = sysClassifyName;
    }
    QString getSysName1() {
        return sysName1;
    }
    void setSysName1(QString sysName1) {
        this->sysName1 = sysName1;
    }
    QString getSysName2() {
        return sysName2;
    }
    void setSysName2(QString sysName2) {
        this->sysName2 = sysName2;
    }
    QString getSysName3() {
        return sysName3;
    }
    void setSysName3(QString sysName3) {
        this->sysName3 = sysName3;
    }
    QString getFamFileName1() {
        return famFileName1;
    }
    void setFamFileName1(QString famFileName1) {
        this->famFileName1 = famFileName1;
    }
    QString getFamFileName2() {
        return famFileName2;
    }

    void setFamFileName2(QString famFileName2) {
        this->famFileName2 = famFileName2;
    }
    QString getFamFileName3() {
        return famFileName3;
    }
    void setFamFileName3(QString famFileName3) {
        this->famFileName3 = famFileName3;
    }
    QList<QString> getSubSystems() {
        return subSystems;
    }
    void setSubSystems(QList<QString> subSystems) {
        this->subSystems = subSystems;
    }
    QList<QString> getIfcFiles() {
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
    QString getTransformMatrix() {
        return transformMatrix;
    }
    void setTransformMatrix(QString transformMatrix) {
        this->transformMatrix = transformMatrix;

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
    QString getObjectModel() {
        return objectModel;
    }
    void setObjectModel(QString objectModel) {
        this->objectModel = objectModel;

    }

private:
    //********** 二级系统级.cbm下读取内容
   // F2System parent;
    // 三级子系统级.cbm的文件名
    //QString f3FileName;

    //********** 三级子系统级.cbm下读取内容

    //三级子系统级的类型
    QString sysClassifyName;


    //三级子系统级的名称
    QString sysName1;
    QString sysName2;
    QString sysName3;

    //三级子系统级.fam的内容
    QString famFileName1;
    QString famFileName2;
    QString famFileName3;

    //引用的四级设备级
    QList<QString> subSystems;

    //引用的ifc文件
    QList<QString> ifcFiles;

    //补充材料xml
    QString materialSheet;
    //第二种情况**************

        //三级子系统级.fam的内容
       // private List<TripletPara> f3Paras;
    QString famFileName;

    //设备相对于变电站原点的空间变换矩阵
    QString transformMatrix;

    //引用的物理模型dev
    QString objectModel;

    //引用的部件索引cbm
    QList<QString> subDevice;

    //引用的逻辑模型cbm
    QList<QString> subLogicalModels;
};










