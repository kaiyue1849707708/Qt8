#pragma once

#include"GimFile.h"
#include <QtCore/QDebug.h>
#include"QtCore/qlist.h"

class LogicalModel :public GimFile
{
public:

    //void display() {
    //    qDebug() << "逻辑模型cbm的文件名:   " << logicModelFileName << endl;
    //    if (schFiles.size() != QString::null) {
    //        qDebug() << "sch文件数量:   " << schFiles.size() << endl;
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
    //********** 一级全站级.cbm/四级设备级.cbm下读取内容
   // T  parent;
    // 逻辑模型.cbm的文件名
   // QString logicModelFileName;

    //********** 逻辑模型.cbm下读取内容

    //引用的sch文件
    QList<QString> schFiles;
};





