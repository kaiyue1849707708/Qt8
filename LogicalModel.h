#pragma once

#include"GimFile.h"
#include <QtCore/QDebug.h>
#include"QtCore/qlist.h"

class LogicalModel :public GimFile
{
public:

    //void display() {
    //    qDebug() << "�߼�ģ��cbm���ļ���:   " << logicModelFileName << endl;
    //    if (schFiles.size() != QString::null) {
    //        qDebug() << "sch�ļ�����:   " << schFiles.size() << endl;
    //        for (SchFile schFile : schFiles) {
    //            qDebug() << &schFile << endl;
    //        }
    //    }
    //}
    //QString getLogicModelFileName() {
    //    return logicModelFileName;
    //}
    //void setLogicModelFileName(QString logicModelFileName) {
    //    this->logicModelFileName = logicModelFileName;
    //}
    QList<QString> getSchFiles() {
        return schFiles;
    }
    void setSchFiles(QList<QString> schFiles) {
        this->schFiles = schFiles;
    }

private:
    //********** һ��ȫվ��.cbm/�ļ��豸��.cbm�¶�ȡ����
   // T  parent;
    // �߼�ģ��.cbm���ļ���
   // QString logicModelFileName;

    //********** �߼�ģ��.cbm�¶�ȡ����

    //���õ�sch�ļ�
    QList<QString> schFiles;
};





