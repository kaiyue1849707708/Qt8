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
    //********** �ļ��豸��.cbm/��������.cbm/����ģ��.dev�¶�ȡ����
    //F4System parent;

      //����ģ��fam������
    QString famFileName;



    //dev��Ӧ�ĵ����豸��ģ������
    QString symbolName;


    //���õĴμ�����ģ��dev
    QList<QString> subObjectModels;
    QList<QString> subObjTransformMatrix;

    //�μ�����ģ�͵Ŀռ�任����

//���õ�phm�ļ�
    QList<QString> solidModels;
    QList<QString> solidTransformMatrix;

    //    //phmģ�͵Ŀռ�任����
    //    private List<String> transformMatrixPHM;
};




