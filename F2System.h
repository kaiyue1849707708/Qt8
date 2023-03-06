#pragma once
#include <QtCore/qstring.h>
#include"GimFile.h"
#include"QtCore/qlist.h"
using namespace std;
class F2System :public GimFile
{
public:

    //void display() {
    //    qDebug() << "����ȫվ��cbm���ļ���:   " << f2FileName << endl;
    //    qDebug() << "����ϵͳ��������:  " << sysClassifyName << endl;
    //    qDebug() << "����ϵͳ��fam�����ݡ�" << f1FileName << endl;
    //
    //    if (f2Paras.size() != QString::null) {
    //        for (TripletPara f2Para : f2Paras) {
    //
    //            qDebug() << " " << &f2Para << endl;
    //        }
    //    }
    //
    //    qDebug() << "������ϵͳ��cbm������:    " << subSystems.size() << endl;
    //    for (F3System f3System : subSystems) {
    //
    //        qDebug() << &f3System << endl;
    //    }
    //
    //
    //    qDebug() << "������ϵ���" << materialSheet << endl;
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
    //********** һ��ȫվ��.cbm�¶�ȡ����
    //F1System parent;

    // ����ϵͳ��.cbm���ļ���
    QString famFileName;

    //********** ����ϵͳ��.cbm�¶�ȡ����

    //����ϵͳ��������
    QString sysClassifyName;

    //����ϵͳ��.fam������
    //QList<TripletPara> f2Paras;

    //���õ�������ϵͳ��
    QList<QString> subSystems;

    //���õ�ifc�ļ�
    QList<QString> ifcFiles;

    //�������xml
    QString materialSheet;




};




