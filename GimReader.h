#pragma once

#include<QtCore/qobject.h>
#include <QtCore/qdir.h>
#include<QtCore/qdebug.h>
#include "FSevenZHelper.h"
#include "ProjectFile.h"
#include "F1System.h"
#include "F2System.h"
#include "F3System.h"
#include "F4System.h"
#include "PartIndex.h"
#include "ObjectModel.h"
#include "ModFile.h"
#include "SolidModel.h"
#include"IfcFile.h"
#include"StlFile.h"
#include"SchFile.h"
#include"TripletPara.h"
#include "LogicalModel.h"
#include"myopengl.h"

using namespace std;

extern QList<ModFile> gimModFileList;
extern ObjectModel objectModel;
extern QList<TripletPara> sysParas;

extern QString extractPath; //创建7z解压之后的路径文件夹:G:/Example C/example11/gimUncompress
extern QString sevenzPath; //创建gim7z文件夹:G:/Example C/example11/gim7zFiles
extern QString path;//7z文件解压位置，包含.7z文件:gimUncompress/测试工程
extern QString gimName;//gim文件名（不包括后缀）
class GimReader :public QObject
{
    Q_OBJECT
public:
    GimReader();
    ~GimReader();

    void ImportGim(QString gimPath);
    void ExportGim(QString outPath);
    void RemoveGimHeaders(QString gimName, QByteArray gimBytes);
    void WriteGimFile(QString gim7zPath, QString outPath);
    void WriteGimHeaders(QByteArray gimBytes, int values);
    void SetHeaders(QByteArray headerContent, QByteArray item, int begin);
    QByteArray  intToByte(int values);

    ProjectFile ReadProjectFile();
    F1System readF1System(QString fileName);
    F2System readF2System(QString fileName);
    F3System readF3System(QString fileName);
    F4System readF4System(QString fileName);
    void GetF3System(QMap<QString, QString> content, F3System& f3System);
    void GetF3SystemAsF4(QMap<QString, QString> content, F3System& f3System);
    PartIndex readPartIndex(QString fileName);
    ObjectModel readObjectModel(QString fileName);
    SolidModel readSolidModel(QString fileName);
    LogicalModel readLogicalModel(QString fileName);
    ModFile readModFile(QString fileName);
    IfcFile readIfcFile(QString fileName);
    StlFile readStlFile(QString fileName);
    SchFile readSchFile(QString fileName);

    QList<TripletPara> readTripletPara(QString fileName, EntityName entityName);
    QDomNodeList readXmlPara(QString readPath);
    QMap<QString, QString> readDoublePara(QString readPath);
    //直接获取所有的.mod文件，用于画图
    QList<ModFile> GetGimModFileList2();
    //从dev开始读取所有的mod
    void run();
    QList<ModFile> GetGimModFileList();

    QList<QString> getFlSystemNode();

    QList<QString> getF2SystemNode(QString fileName);

    QList<QString> getF3SystemNode(QString fileName);

    void F3asF4(QString fileName);

    QList<QString> getF4SystemNode(QString fileName);

    QList<QString> getPartIndexNode(QString fileName);

    QList<ModFile> GetGimModFileList1();

    void read();

public:

private:
    //一个path对应一个gim文件 由一个gimReader实例管理
    //QString path;
    QList<QString> FlSystemNode;
    QList<QString> F2SystemNode;
    QList<QString> F3SystemNode;
    QList<QString> F3toObjNode;
    QList<QString> F3toF4Node;
    QList<QString> allF4SystemNode;
    QList<QString> F4SystemNode;
    QList<QString> PartIndexNode;
    QList<QString> havasubdevices;

    QTimer* pTimer;


};
