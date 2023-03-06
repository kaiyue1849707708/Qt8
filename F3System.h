#pragma once
#include <QtCore/QDebug.h>
#include"QtCore/qlist.h"
#include"GimFile.h"
using namespace std;
class  F3System : public GimFile
{
public:

    //void display() {
    //    qDebug() << "������ϵͳ��cbm���ļ���:    " << f3FileName << endl;
    //    qDebug() << "������ϵͳ��������:   " << sysClassifyName << endl;
    //    qDebug() << "������ϵͳ��������1: " << sysName1 << endl;
    //    qDebug() << "������ϵͳ��������2:  " << sysName2 << endl;
    //    qDebug() << "������ϵͳ��������3: " << sysName3 << endl;
    //    qDebug() << "������ϵͳ��fam1�����ݡ�" << endl;
    //
    //    if (f3Paras1.size() != QString::null) {
    //        for (TripletPara f3Para : f3Paras1) {
    //
    //            qDebug() << "  " << &f3Para << endl;
    //        }
    //    }
    //
    //    qDebug() << "������ϵͳ��fam1�����ݡ�" << endl;
    //    if (f3Paras2.size() != QString::null) {
    //        for (TripletPara f3Para : f3Paras2) {
    //            qDebug() << "  " << &f3Para << endl;
    //        }
    //    }
    //    qDebug() << "������ϵͳ��fam1�����ݡ�" << endl;
    //    if (f3Paras3.size() != QString::null) {
    //        for (TripletPara f3Para : f3Paras3) {
    //            qDebug() << "  " << &f3Para << endl;
    //        }
    //    }
    //
    //
    //    qDebug() << "�ļ��豸��cbm������:    " << subSystems.size() << endl;
    //    for (F4System subSystemFileName : subSystems) {
    //
    //        qDebug() << &subSystemFileName << endl;
    //    }
    //
    //
    //    qDebug() << "������ϵ���" << materialSheet << endl;
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
    //********** ����ϵͳ��.cbm�¶�ȡ����
   // F2System parent;
    // ������ϵͳ��.cbm���ļ���
    //QString f3FileName;

    //********** ������ϵͳ��.cbm�¶�ȡ����

    //������ϵͳ��������
    QString sysClassifyName;


    //������ϵͳ��������
    QString sysName1;
    QString sysName2;
    QString sysName3;

    //������ϵͳ��.fam������
    QString famFileName1;
    QString famFileName2;
    QString famFileName3;

    //���õ��ļ��豸��
    QList<QString> subSystems;

    //���õ�ifc�ļ�
    QList<QString> ifcFiles;

    //�������xml
    QString materialSheet;
    //�ڶ������**************

        //������ϵͳ��.fam������
       // private List<TripletPara> f3Paras;
    QString famFileName;

    //�豸����ڱ��վԭ��Ŀռ�任����
    QString transformMatrix;

    //���õ�����ģ��dev
    QString objectModel;

    //���õĲ�������cbm
    QList<QString> subDevice;

    //���õ��߼�ģ��cbm
    QList<QString> subLogicalModels;
};










