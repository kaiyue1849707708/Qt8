#pragma once

#include <QtCore/qstring.h>
#include "QtCore/qlist.h"
#include"GimFile.h"
using namespace std;
class F1System :public GimFile
{
public:


    QString getfamFileName() {
        return famFileName;
    }
    void setfamFileName(QString famFileName) {
        this->famFileName = famFileName;
    }


    QList<QString> getSubSystems() {
        return subSystems;
    }
    void setSubSystems(QList<QString> subSystems) {
        this->subSystems = subSystems;
    }
    QList<QString> getSubLogicalModels() {
        return subLogicalModels;
    }
    void setSubLogicalModels(QList<QString> subLogicalModels) {
        this->subLogicalModels = subLogicalModels;
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

private:
    //********** project.cbm�¶�ȡ����
   // ProjectFile parent;


    //һ��ȫվ��fam������
    QString famFileName;

    //********** һ��ȫվ��.cbm�¶�ȡ����

    //һ��ȫվ��fam������
    //QList<TripletPara> f1Paras;

    //���õĶ���ϵͳ��
    QList< QString> subSystems;

    //���õ��߼�ģ��
    QList< QString> subLogicalModels;

    //���õ�ifc�ļ�
    QList< QString> ifcFiles;

    //�������xml
    QString materialSheet;

};




