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
    //********** �ļ��豸��.cbm�¶�ȡ����
   // F4System parent;
    // ��������.cbm���ļ���
    //QString partIndexFileName;

    //********** ��������.cbm�¶�ȡ����

    //��������������
    QString partName;

    //��������.fam������
    QString famFileName;

    //���õ�����ģ��dev
    QString objectModel;


};


