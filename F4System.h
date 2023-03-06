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
    //********** ������ϵͳ��.cbm�¶�ȡ����
   // F3System parent;
    // �ļ��豸��.cbm���ļ���
    //QString f4FileName;

    //********** �ļ��豸��.cbm�¶�ȡ����

    //�ļ��豸��������
    QString sysClassifyName;

    //�豸����ڱ��վԭ��Ŀռ�任����
    QString transformMatrix;

    //�ļ��豸��.fam������
    QString famFileName;

    //���õ�����ģ��dev
    QString  objectModel;
    //���õĲ�������cbm

    QList<QString> subDevice;

    //���õ��߼�ģ��cbm
    QList<QString> subLogicalModels;

};










