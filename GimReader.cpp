#ifdef WIN32  
#pragma execution_character_set("utf-8")
#endif
#include "GimReader.h"
#include<QtCore/qdatetime.h>
#include <iostream>

#include <QtXml/QDomDocument>
#include <QtCore/QXmlStreamReader>
#include<QtCore/qtextcodec.h>
#include<QtCore/qdiriterator.h>
#include <QtCore/qurl.h>
#define  PI 3.1415926
#include<xkeycheck.h>
#include <gl/GL.h>
//#include"stdafx.h"
#include<QtCore/qlist.h>
#include "Qt8.h"
using namespace std;

QList<ModFile> gimModFileList;
ObjectModel objectModel;
QList<TripletPara> sysParas;

QString extractPath; //创建7z解压之后的路径文件夹:G:/Example C/example11/gimUncompress
QString sevenzPath; //创建gim7z文件夹:G:/Example C/example11/gim7zFiles
QString path;//7z文件解压位置，包含.7z文件:gimUncompress/测试工程
QString gimName;//gim文件名（不包括后缀）
GimReader::GimReader()
{
    extractPath = "E:/QT/Qt8/gimUncompress"; //创建7z解压之后的路径文件夹
    sevenzPath = "E:/QT/Qt8/gim7zFiles";//创建gim7z文件夹


}

GimReader::~GimReader()
{
    //qDebug() << f1System.getSubSystems() << endl;
}
//导入GIM
void GimReader::ImportGim(QString gimPath)
{
    QFile gimfile(gimPath);
    //  指定打开方式
    bool isOk = gimfile.open(QFile::ReadOnly);
    if (!isOk) {
        throw"file open failed";
    }
    QByteArray gimBytes = gimfile.readAll();//读取gim文件到字节数组中
    gimfile.close();
    if (gimBytes.size() == 0)
    {
        throw "gimBytes.size == 0";
    }
    QFileInfo gim(gimPath);
    gimName = gim.baseName();//获取.gim文件不带后缀的文件名
    RemoveGimHeaders(gimName, gimBytes);//移除gimheader 获得7z

    //创建文件夹
    QDir dir(extractPath);
    if (!dir.exists()) {
        dir.mkpath(extractPath);
    }

    QDir sevenz(sevenzPath);
    if (!sevenz.exists()) {
        sevenz.mkpath(sevenzPath);
    }
    path = extractPath + "/" + gimName;
    QDir extractpath(path);
    if (!extractpath.exists()) {
        extractpath.mkpath(path);
    }
    //解压到gimUncompress目录下---------解压路径到gimUncompress就可以了
    //FSevenZHelper sevenzipextract;
    //sevenzipextract.Extract(sevenzPath + "/" + gimName + ".7z", path);//解压7z文件
    //7z压缩包解压之后的路径
    qDebug() << "解压完成" << endl;
}
//导出GIM
void GimReader::ExportGim(QString outPath)
{
    FSevenZHelper sevenzipcompress;
    sevenzipcompress.Compress(path, sevenzPath + "/" + gimName + ".7z");
    WriteGimFile(sevenzPath + "/" + gimName + ".7z", outPath);
}
//生成.7z文件
void GimReader::RemoveGimHeaders(QString gimName, QByteArray gimBytes)
{
    if (gimBytes.size() < 876)
    {
        throw "gim文件的字节数过少" + gimBytes.size();
    }
    qDebug() << "文件标识：" << gimBytes.mid(0, 16).data() << endl;
    qDebug() << "文件名称：" << gimBytes.mid(16, 256).data() << endl;
    qDebug() << "设计者：" << gimBytes.mid(272, 64).data() << endl;
    qDebug() << "组织单位：" << gimBytes.mid(336, 256).data() << endl;
    qDebug() << "软件名称：" << gimBytes.mid(592, 128).data() << endl;
    qDebug() << "创建时间：" << gimBytes.mid(720, 16).data() << endl;
    qDebug() << "软件主版本号：" << gimBytes.mid(736, 8).data() << endl;
    qDebug() << "软件次版本号：" << gimBytes.mid(744, 8).data() << endl;
    qDebug() << "标准主版本号：" << gimBytes.mid(752, 8).data() << endl;
    qDebug() << "标准次版本号：" << gimBytes.mid(760, 8).data() << endl;
    qDebug() << "存储域大小：";
    for (int i = 768; i < 776; i++) {
        int t = (int)gimBytes[i];
        cout << t << " ";
    }
    qDebug() << endl;
    qDebug() << "存储域前100Byte（7z开始）：";
    for (int i = 776; i < 876; i++) {
        int t = (int)gimBytes[i];
        cout << t << " ";
    }
    qDebug() << endl;
    QByteArray gim7zBytes;
    gim7zBytes.resize(gimBytes.size() - 776);
    for (int i = 776, j = 0; i < gimBytes.size(); i++, j++)
    {
        gim7zBytes[j] = gimBytes[i];
    }

    //如果文件已存在 删除文件
    QString gim7zPath = sevenzPath + "/" + gimName + ".7z";
    QFile gim7zfile(gim7zPath);
    if (gim7zfile.exists()) {
        gim7zfile.remove();
    }
    //写7z
    gim7zfile.open(QFile::WriteOnly);
    gim7zfile.write(gim7zBytes);
    gim7zfile.close();
}
//生成.gim文件
void GimReader::WriteGimFile(QString gim7zPath, QString outPath)
{
    QFile gim7zfile(gim7zPath);
    if (!gim7zfile.exists()) {
        throw"gim.7z不存在";
    }
    QByteArray gim7zBytes = gim7zfile.readAll();
    qint32 size = gim7zBytes.size();
    QByteArray gimBytes;
    gimBytes.resize(size + 776);
    WriteGimHeaders(gimBytes, size);
    for (int i = 776, j = 0; j < gim7zBytes.size(); i++, j++)
    {
        gimBytes[i] = gim7zBytes[j];
    }
    QFile gimfile(outPath);
    if (gimfile.open(QFile::WriteOnly)) {
        gimfile.write(gimBytes);
    }
}
//写头部信息
void GimReader::WriteGimHeaders(QByteArray gimBytes, int values)
{
    //标识,0
    SetHeaders(gimBytes, QByteArray("GIMPKGS"), 0);

    //文件名称,16
    SetHeaders(gimBytes, QByteArray("腾讯"), 16);

    //设计者,272
    SetHeaders(gimBytes, QByteArray("陈然"), 272);

    //组织单位,336
    SetHeaders(gimBytes, QByteArray("南京邮电大学"), 336);

    //软件名称,592
    SetHeaders(gimBytes, QByteArray("软件名称"), 592);

    //创建时间,720
    QDateTime date = QDateTime::currentDateTime();
    QString datetime = date.toString("yyyy-MM-dd hh:mm:ss");
    SetHeaders(gimBytes, datetime.toUtf8(), 720);


    //软件主版本号,736
    SetHeaders(gimBytes, QByteArray("V1"), 736);

    //软件次版本号,744
    SetHeaders(gimBytes, QByteArray("01"), 744);


    //标准主版本号,752
    SetHeaders(gimBytes, QByteArray("01"), 752);


    //标准次版本号,760
    SetHeaders(gimBytes, QByteArray("01"), 760);


    //存储域大小,768
    SetHeaders(gimBytes, intToByte(values), 768);
}

void GimReader::SetHeaders(QByteArray headerContent, QByteArray item, int begin)
{
    for (int i = 0; i < item.size(); i++)
    {
        headerContent[begin] = item[i];
        begin++;
    }
}

QByteArray GimReader::intToByte(int values)
{
    QByteArray arr = QByteArray::number(values, 16);
    return arr;
    /* QByteArray abyte0;
     abyte0.resize(4);
     abyte0[0] = (uchar)(0xff & values);
     abyte0[1] = (uchar)((0xff00 & values) >> 8);
     abyte0[2] = (uchar)((0xff0000 & values) >> 16);
     abyte0[3] = (uchar)((0xff000000 & values) >> 24);
     return abyte0;*/
}

void GimReader::run()
{
    //ReadProjectFile();
    //qDebug() << projectFile.getSubSystem() << endl;
    //qDebug() << f1System.getSubSystems() << endl;
    //qDebug() << f2System.getSubSystems() << endl;
    //qDebug() << f3System.getSysName1() << endl;
    //qDebug() << f4System.getSubDevice() << endl;
    //qDebug() << partIndex.getPartName() << endl;
    //qDebug() << getmodfile().size() << endl;
    //GetGimModFileList2();

    getFlSystemNode();
    GetGimModFileList1();
    //qDebug() << FlSystemNode << endl;
    //qDebug() << F2SystemNode << endl;
   //qDebug() << "f3toObj:"<<F3toObjNode<< endl;
    //qDebug() << "F4:"<<F4SystemNode.size() << endl;
    //qDebug() << havasubdevices.size() << endl;
    //GetGimModFileList1();
    //qDebug() << "MOD:"<<gimModFileList.size() << endl;
    //readModFile("G:/idea/gim/src/main/resources/gimUncompress/正方体/MOD/03aa690f-f38c-4bd9-97cf-c4b97e896294.mod");

    /*ModFile modFile=readModFile("G:/idea/gim/src/main/resources/gimUncompress/正方体/MOD/03aa690f-f38c-4bd9-97cf-c4b97e896294.mod");
    ModFileList.append(modFile);*/

    //qDebug() << ModFileList.size() << endl;

    //for (ModFile modFile : ModFileList) {
    //    //qDebug() << modFile.getSimpleEntities().length() << endl;
    //    //qDebug() <<111111<< endl;
    //    for (SimpleEntity simpleEntity : modFile.getSimpleEntities()) {
    //        //qDebug() << 111111 << endl;
    //        if (!simpleEntity.getGraphicElement().isNull()) {
    //            //qDebug() << 111111 << endl;
    //            //qDebug() << simpleEntity.getGraphicElement().nodeName() << endl;
    //            if (simpleEntity.getGraphicElement().nodeName() == ("Cuboid")) {
    //                //qDebug() << 111111 << endl;
    //                QString  vs = simpleEntity.getTransformMatrix();
    //                //qDebug() << vs << endl;
    //                QStringList splits = vs.split(",");
    //                float mat[16];
    //                for (int i = 0; i < 16; i++)
    //                {
    //                    mat[i] = (splits[i]).toFloat();
    //                    //qDebug() << mat[i] << endl;
    //
    //                }
    //                ////获取旋转角度
    //                float rX = (atan2(mat[9], mat[10])) * PI / 180;
    //                float rY = (atan2(-mat[8], sqrt(pow(mat[9], 8) + pow(mat[10], 8)))) * PI / 180;
    //                float rZ = (atan2(mat[4], mat[0])) * PI / 180;
    //                //获取坐标
    //                float X = mat[12];
    //                float Y = mat[13];
    //                float Z = mat[14];
    //                //获取颜色
    //                float R = (float)simpleEntity.getR() / 255;
    //                float G = (float)simpleEntity.getG() / 255;
    //                float B = (float)simpleEntity.getB() / 255;
    //                float A = (float)simpleEntity.getA() / 255;
    //                //获取长宽高
    //                QDomElement n = simpleEntity.getGraphicElement().toElement();
    //                float L = (n.attribute("L")).toFloat();
    //                float W = (n.attribute("W")).toFloat();
    //                float H = (n.attribute("H")).toFloat();

    //                GLuint id1 = glGenLists(1);
    //                glNewList(id1, GL_COMPILE);
    //                glPushMatrix();
    //                Cuboid(L, W, H);
    //                glPopMatrix();
    //                glEndList();
    //                 //qDebug() << L << " " << H << "" << W << " " << endl;
    //            }
    //        }
    //    }
    //}

    //setmodfile(ModFileList);
    //qDebug() << getmodfile().size() << endl;
    //readXmlPara("G:/idea/gim/src/main/resources/gimUncompress/正方体/MOD/03aa690f-f38c-4bd9-97cf-c4b97e896294.mod");
}
//读取project.cbm  --- 获取一个ProjectFile对象
ProjectFile GimReader::ReadProjectFile()
{
    ProjectFile  projectFile;
    //读取解压后的文件内容 从project.cbm开始
    QString readPath = path + "/CBM/" + "project.cbm";
    //qDebug() << readPath << endl;
    QMap<QString, QString> content = readDoublePara(readPath);
    if (content.isEmpty()) {
        qDebug() << "读取project.cbm失败" << endl;
    }
    //ProjectFile projectFile= NULL; 

    if (!content.isEmpty()) {
        projectFile.setentityName(EntityName::ProjectFile);
        projectFile.setfileName("project.cbm");
        projectFile.setBLHA(content.value("BLHA"));
        projectFile.setSubSystem(content.value("SUBSYSTEM"));
    }
    //readF1System(content.value("SUBSYSTEM"));

    /*QMapIterator<QString, QString> iterator(content);
    while (iterator.hasNext()) {
        iterator.next();
        qDebug() << iterator.key() << ":" << iterator.value();
    }*/
    qDebug() << projectFile.getSubSystem() << endl;
    return  projectFile;

}
//一级.cbm
F1System GimReader::readF1System(QString fileName)
{
    F1System f1System;
    if (fileName.isEmpty()) {
        throw"一级cbm文件不存在";
    }
    //读取对应的全站级.cbm
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);
    //qDebug() << content << endl;
    //把获得的content装进entity

    if (!content.isEmpty()) {
        //检验标识
        if (content.value("ENTITYNAME") != ("F1System")) {
            qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;
            throw "CODE_ERROR";
        }
        //开始组装entity
        //F1System f1System;

        f1System.setentityName(EntityName::F1System);

        //*** 1 *** 一级全站级.cbm的文件名
        f1System.setfileName(fileName);
        //*** 2 *** 一级全站级fam的内容
        f1System.setfamFileName(content.value("BASEFAMILY"));

        //*** 3 *** 引用的二级系统级
        QList<F2System>subSysyems;
        if (content.count("SUBSYSTEMS.NUM") > 0) {
            if (content.value("SUBSYSTEMS.NUM") != "0") {
                int i;
                QList<QString> subsystems;
                for (i = 0; i < (content.value("SUBSYSTEMS.NUM")).toInt(); i++) {
                    qDebug() << content.value("SUBSYSTEM" + QString::number(i)) << endl;
                    //f1System.setSubSystems(subsystems);
                    subsystems.append(content.value("SUBSYSTEM" + QString::number(i)));
                    //readF2System(content.value("SUBSYSTEM" + QString::number(i)));
                }
                f1System.setSubSystems(subsystems);
                //qDebug() << subsystems[0] << endl;
            }
        }
        //*** 4 *** 引用的逻辑模型
        if (content.count("SUBLOGICALMODELS.NUM") > 0) {
            if (content.value("SUBLOGICALMODELS.NUM") != "0") {
                int i;
                QList<QString> sublogicalmodels;
                for (i = 0; i < (content.value("SUBLOGICALMODELS.NUM")).toInt(); i++) {
                    sublogicalmodels.append(content.value("SUBLOGICALMODEL" + QString::number(i)));
                }
                f1System.setSubLogicalModels(sublogicalmodels);
            }
        }
        //*** 5 *** 引用的补充材料xml
        f1System.setMaterialSheet(content.value("MATERIALSHEET"));
        //*** 6 *** 引用的ifc
        if (content.count("IFC.NUM") > 0) {
            if (content.value("IFC.NUM") != "0") {
                int i;
                QList<QString> ifcfiles;
                for (i = 0; i < (content.value("IFC.NUM")).toInt(); i++) {

                    ifcfiles.append(content.value("IFC" + QString::number(i)));
                }
                f1System.setIfcFiles(ifcfiles);
            }
        }
    }
    //qDebug() << f1System.getSubSystems() << endl;
    return f1System;
}
//二级.cbm
F2System GimReader::readF2System(QString fileName)
{
    F2System f2System;
    if (fileName.isEmpty()) {
        throw"二级cbm文件不存在";
    }
    //读取对应的二级系统级.cbm
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);
    //qDebug() << content << endl;
    //把获得的content装进entity
    if (!content.isEmpty()) {
        if (content.value("ENTITYNAME") != ("F2System")) {
            qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;

            throw "CODE_ERROR";
        }
        //开始组装entity
        //F2System f2System;
        f2System.setentityName(EntityName::F2System);
        //*** 1 *** 二级系统级.cbm的文件名
        f2System.setfileName(fileName);
        //*** 2 *** 二级系统级的类型
        f2System.setSysClassifyName(content.value("SYSCLASSIFYNAME"));
        //*** 3 *** 二级系统级.fam的内容
       //QList<TripletPara> basefamily = readTripletPara(path + "/CBM/" + content.key("BASEFAMILY"));
        f2System.setfamFileName(content.value("BASEFAMILY"));
        //*** 4 *** 引用的三级子系统级
        //QList<F3System> subSystems;
        if (content.count("SUBSYSTEMS.NUM") > 0) {
            if (content.value("SUBSYSTEMS.NUM") != ("0")) {
                QList<QString> subsystems;
                for (int i = 0; i < (content.value("SUBSYSTEMS.NUM")).toInt(); i++) {
                    //F3System f3System = this->readF3System(content.key("SUBSYSTEM" + i));
                    subsystems.append(content.value("SUBSYSTEM" + QString::number(i)));
                    //readF3System(content.value("SUBSYSTEM" + QString::number(i)));

                }
                f2System.setSubSystems(subsystems);
            }
        }
        //*** 5 *** 引用的ifc文件
        if (content.count("IFC.NUM") > 0) {
            if (content.value("IFC.NUM") != "0") {
                int i;
                QList<QString> ifcfiles;
                for (i = 0; i < (content.value("IFC.NUM")).toInt(); i++) {
                    ifcfiles.append(content.value("IFC" + QString::number(i)));
                }
                f2System.setIfcFiles(ifcfiles);
            }
        }
        //*** 6 *** 补充材料xml
        f2System.setMaterialSheet(content.value("MATERIALSHEET"));
    }
    //qDebug() << f2System.getSubSystems() << endl;
    return f2System;
}
//三级.cbm
F3System GimReader::readF3System(QString fileName)
{
    F3System f3System;
    if (fileName.isEmpty()) {
        throw"三级cbm文件不存在";
    }
    //读取对应的三级子系统级.cbm
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);
    //qDebug() << content << endl;
    //把获得的content装进entity
    if (!content.isEmpty()) {
        if (content.value("ENTITYNAME") != ("F3System")) {
            qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;
            throw "CODE_ERROR";
        }
        //开始组装entity
        f3System.setentityName(EntityName::F3System);
        //*** 1 *** 三级子系统级.cbm的文件名
        f3System.setfileName(fileName);
        //*** 2 *** 三级子系统级的类型
        f3System.setSysClassifyName(content.value("SYSCLASSIFYNAME"));
        //判断是子系统是F4还是部件索引
        if (content.count("BASEFAMILY1") > 0) {
            //是f4
            GetF3System(content, f3System);
        }
        else {
            //是部件索引

            GetF3SystemAsF4(content, f3System);
        }
    }
    return f3System;
}
//四级.cbm
F4System GimReader::readF4System(QString fileName)
{
    F4System f4System;
    if (fileName.isEmpty()) {
        throw"四级cbm文件不存在";
    }
    //读取对应的四级设备级.cbm
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);
    //把获得的content装进entity
    if (!content.isEmpty()) {
        //检验标识
        if (content.value("ENTITYNAME") != ("F4System")) {
            qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;
            throw "CODE_ERROR";
        }
        //开始组装entity
        f4System.setentityName(EntityName::F4System);
        //*** 1 *** 四级设备级.cbm的文件名
        f4System.setfileName(fileName);

        //*** 2 *** 四级设备级的类型
        f4System.setsysClassifyName(content.value("SYSCLASSIFYNAME"));

        //*** 3 *** 四级设备级.fam的内容
        //QList<TripletPara> basefamily = readTripletPara(path + "/CBM/" + content.key("BASEFAMILY"));
        f4System.setfamFileName(content.value("BASEFAMILY"));

        //*** 4 *** 设备相对于变电站原点的空间变换矩阵
        f4System.setTransformMatrix(content.value("TRANSFORMMATRIX"));

        //*** 5 *** 引用的物理模型dev

        f4System.setObjectModel(content.value("OBJECTMODELPOINTER"));

        //*** 6 *** 引用的部件索引
        //QList<PartIndex> partIndices();
        if (content.count("SUBDEVICES.NUM") > 0) {
            if (content.value("SUBDEVICES.NUM") != ("0")) {
                QList<QString> subdevices;
                for (int i = 0; i < (content.value("SUBDEVICES.NUM")).toInt(); i++) {
                    subdevices.append(content.value("SUBDEVICE" + QString::number(i)));
                    //readPartIndex(content.value("SUBDEVICE" + QString::number(i)));
                }
                f4System.setSubDevice(subdevices);
            }
        }
        //*** 7 *** 引用的逻辑模型cbm
        if (content.count("SUBLOGICALMODELS.NUM") > 0) {
            if (content.value("SUBLOGICALMODELS.NUM") != ("0")) {
                QList<QString> sublogicalmodels;
                for (int i = 0; i < content.value("SUBLOGICALMODELS.NUM"); i++) {
                    sublogicalmodels.append(content.value("SUBLOGICALMODEL" + QString::number(i)));
                }
                f4System.setSubLogicalModels(sublogicalmodels);
            }
        }
    }
    //qDebug() << f4System.getSubDevice() << endl;
    return f4System;
}

void GimReader::GetF3System(QMap<QString, QString> content, F3System& f3System)
{
    //qDebug() << content << endl;
    //F3
    f3System.setentityName(EntityName::F3System);
    //*** 3 *** 三级子系统级的名称 1 2 3
    f3System.setSysName1(content.value("SYSTEMNAME1"));
    //qDebug() << f3System.getSysName1() << endl;
    f3System.setSysName2(content.value("SYSTEMNAME2"));
    f3System.setSysName3(content.value("SYSTEMNAME3"));

    //*** 4 *** 三级子系统级.fam的内容 1 2 3

    f3System.setFamFileName1(content.value("BASEFAMILY1"));
    f3System.setFamFileName2(content.value("BASEFAMILY2"));
    f3System.setFamFileName3(content.value("BASEFAMILY3"));

    //*** 5 *** 引用的四级设备级
    if (content.count("SUBSYSTEMS.NUM") > 0)
    {
        if (content.value("SUBSYSTEMS.NUM") != ("0"))
        {
            QList<QString> subsystems;
            for (int i = 0; i < (content.value("SUBSYSTEMS.NUM")).toInt(); i++)
            {
                subsystems.append(content.value("SUBSYSTEM" + QString::number(i)));
                //readF4System(content.value("SUBSYSTEM" + QString::number(i)));
            }
            f3System.setSubSystems(subsystems);
        }
    }
    //*** 6 *** 引用的ifc文件
    if (content.count("IFC.NUM") > 0)
    {
        if (content.value("IFC.NUM") != ("0"))
        {
            QList<QString> ifcfiles;
            for (int i = 0; i < (content["IFC.NUM"]).toInt(); i++)
            {
                ifcfiles.append(content.value("IFC" + QString::number(i)));
            }
            f3System.setIfcFiles(ifcfiles);
        }
    }

    //*** 7 *** 补充材料xml
    f3System.setMaterialSheet(content.value("MATERIALSHEET"));
}

void GimReader::GetF3SystemAsF4(QMap<QString, QString> content, F3System& f3System)
{
    //F4
    f3System.setentityName(EntityName::F3SystemAsF4);
    //*** 3 *** 四级设备级.fam的内容
    // List<TripletPara> basefamily = ReadTripletPara(gimDirectory + @"\CBM\" + content["BASEFAMILY"]);
    f3System.setFamFileName(content.value("BASEFAMILY"));

    //*** 4 *** 设备相对于变电站原点的空间变换矩阵
    f3System.setTransformMatrix(content.value("TRANSFORMMATRIX"));

    //*** 5 *** 引用的物理模型dev
    f3System.setObjectModel(content.value("OBJECTMODELPOINTER"));


    //*** 6 *** 引用的部件索引
    if (content.count("SUBDEVICES.NUM") > 0)
    {
        if (content.value("SUBDEVICES.NUM") != ("0"))
        {
            QList<QString> subdevices;
            for (int i = 0; i < (content.value("SUBDEVICES.NUM")).toInt(); i++)
            {
                subdevices.append(content.value("SUBDEVICE" + QString::number(i)));
                //readPartIndex(content.value("SUBDEVICE" + QString::number(i)));
            }
            f3System.setSubDevice(subdevices);
        }
    }
}
//部件索引.cbm
PartIndex GimReader::readPartIndex(QString fileName)
{
    PartIndex partIndex;
    if (fileName.isEmpty()) {
        throw"部件索引cbm文件不存在";
    }
    //读取对应的部件索引.cbm
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);
    //qDebug() << content << endl;
    //把获得的content装进entity
    if (!content.isEmpty()) {
        //检验标识
        if ((content.value("ENTITYNAME") == ("PartIndex"))
            || content.value("ENTITYNAME") == ("PARTINDEX")) { //文档内是全大写，案例内是大小写


        //开始组装entity
        //PartIndex partIndex();
            partIndex.setentityName(EntityName::PartIndex);

            //*** 1 *** 部件索引.cbm的文件名
            partIndex.setfileName(fileName);

            //*** 2 *** 部件索引的类型
            partIndex.setPartName(content.value("PARTNAME"));

            //*** 3 *** 部件索引.fam的内容
           // QList<TripletPara> basefamily = readTripletPara(path + "/CBM/" + content.key("BASEFAMILY"));
            partIndex.setPartName(content.value("BASEFAMILY"));

            //*** 5 *** 引用的物理模型dev
            partIndex.setObjectModel(content.value("OBJECTMODELPOINTER"));
        }
        else {
            qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;
            throw "CODE_ERROR";
        }

    }
    return partIndex;
}
//.dev
ObjectModel GimReader::readObjectModel(QString fileName) {
    //qDebug() << 11111 << endl;
    ObjectModel objectModel;
    QString readPath = path + "/DEV/" + fileName;
    //qDebug() << readPath << endl;
    if (readPath.isEmpty()) {
        qDebug() << "dev文件不存在" << endl;
        throw"obj文件不存在";
    }
    //读取对应的物理模型.dev

    QMap<QString, QString> content = readDoublePara(readPath);

    //把获得的content装进entity

    if (!content.isEmpty()) {

        //开始组装entity
       // ObjectModel<class T> objectModel;
        objectModel.setentityName(EntityName::ObjectModel);
        //*** 1 *** 物理模型.dev的文件名
        objectModel.setfileName(fileName);
        //*** 2 *** 物理模型.fam的内容
        //qDebug() << "famfile"<<content.value("BASEFAMILYPOINTER") << endl;
        objectModel.setfamFileName(content.value("BASEFAMILYPOINTER"));
        //*** 3 *** 物理模型dev对应的电气设备的模型名字
        objectModel.setSymbolName(content.value("SYMBOLNAME"));
        //*** 4 *** 引用的次级物理模型dev 和 次级物理模型的空间变换矩阵
        //QList<ObjectModel<class T>> subObjectModel();
        if (content.count("SUBDEVICES.NUM") > 0) {
            if (content.value("SUBDEVICES.NUM") != ("0")) {
                QList<QString> subobjmodels;
                QList<QString> subobjtransformmatrix;
                for (int i = 0; i < (content.value("SUBDEVICES.NUM")).toInt(); i++) {
                    subobjmodels.append(content.value("SUBDEVICE" + QString::number(i)));
                    subobjtransformmatrix.append(content.value("TRANSFORMMATRIX" + QString::number(i)));
                }
                objectModel.setSubObjectModels(subobjmodels);
                objectModel.setsubObjTransformMatrix(subobjtransformmatrix);
            }
        }
        //*** 5 *** 引用的phm文件 和 phm模型的空间变换矩阵
        if (content.count("SOLIDMODELS.NUM") > 0) {
            if (content.value("SOLIDMODELS.NUM") != ("0")) {
                QList<QString> subsolidmodels;
                QList<QString> subsolidtransformmatrix;
                for (int i = 0; i < (content.value("SOLIDMODELS.NUM")).toInt(); i++) {
                    //SolidModel<class T> solidModel = this->readSolidModel(content.key("SOLIDMODEL" + i));
                    subsolidmodels.append(content.value("SOLIDMODEL" + QString::number(i)));
                    subsolidtransformmatrix.append(content.value("#TRANSFORMMATRIX" + QString::number(i)));
                }
                objectModel.setSolidModels(subsolidmodels);
                objectModel.setsolidTransformMatrix(subsolidtransformmatrix);


            }
        }
    }
    return objectModel;
}
//.phm
SolidModel GimReader::readSolidModel(QString fileName)
{
    if (fileName.isEmpty()) {
        qDebug() << "phm文件不存在" << endl;
        throw "phm文件不存在";
    }
    //读取对应的组合模型文件phm
    QString readPath = path + "/PHM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);

    //把获得的content装进entity
    SolidModel solidModel;
    if (!content.isEmpty()) {
        //SolidModel<class T> solidModel;
        //*** 1 *** 组合模型文件phm的文件名
        solidModel.setfileName(fileName);
        //*** 2 *** 引用的phm，mod，stl文件
        if (content.count("SOLIDMODELS.NUM") > 0) {
            if (content.value("SOLIDMODELS.NUM") != ("0")) {
                QList<QString> colorList;
                QList<QString> transformMatrixList;
                QList<QString> children;
                for (int i = 0; i < (content.value("SOLIDMODELS.NUM")).toInt(); i++) {
                    colorList.append(content.value("COLOR" + QString::number(i)));
                    transformMatrixList.append(content.value("TRANSFORMMATRIX" + QString::number(i)));
                    children.append(content.value("SOLIDMODEL" + QString::number(i)));
                }
                solidModel.setcolorList(colorList);
                solidModel.settransformMatrixList(transformMatrixList);
                solidModel.setchildren(children);
            }
        }
    }
    return solidModel;
}
//.cbm
LogicalModel GimReader::readLogicalModel(QString fileName)
{
    LogicalModel logicalModel;
    if (fileName.isEmpty()) {
        throw "cbm文件不存在";
    }
    //读取对应的逻辑模型.cbm
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);

    //把获得的content装进entity
    if (!content.isEmpty()) {
        if (content.value("ENTITYNAME") != ("LOGICALMODEL")) { //文档内是全大写，案例无
            qDebug() << extractPath << "/DEV/" << fileName << "标识错误" << endl;

            throw "CODE_ERROR";
        }
        //开始组装entity
        //*** 1 *** 逻辑模型.cbm的文件名
        logicalModel.setfileName(fileName);
        //*** 2 *** 引用的sch文件
        if (content.count("LOGICALMODELS.NUM") > 0) {
            QList<QString> schFiles;
            if (content.value("LOGICALMODELS.NUM") != ("0")) {
                for (int i = 0; i < (content.value("LOGICALMODELS.NUM")).toInt(); i++) {
                    schFiles.append(content.value("LOGICALMODEL" + QString::number(i)));
                }
                logicalModel.setSchFiles(schFiles);
            }
        }

    }
    return logicalModel;

}
//.ifc
IfcFile GimReader::readIfcFile(QString fileName)
{
    IfcFile ifcFile;
    if (fileName.isEmpty()) {
        throw "ifc文件不存在";
    }
    return ifcFile;
}
//.stl
StlFile GimReader::readStlFile(QString fileName)
{
    StlFile stlFile;
    if (fileName.isEmpty()) {
        throw "stl文件不存在";
    }
    return stlFile;
}
//.sch
SchFile GimReader::readSchFile(QString fileName)
{
    SchFile schFile;
    if (fileName.isEmpty()) {
        throw "sch文件不存在";
    }
    return schFile;
}
//mod
ModFile GimReader::readModFile(QString fileName)
{
    if (fileName.isEmpty()) {
        qDebug() << "mod文件找不到" << endl;
        throw ".mod文件不存在";
    }
    //读取对应的xml
    QString readPath = path + "/MOD/" + fileName;
    QDomNodeList content = readXmlPara(readPath);//////测试，记得改地址
    ModFile modFile;
    if (!content.isEmpty()) {
        modFile.setfileName(fileName);
        //因为<Entities>只有一个，直接获取这一个
        QDomNode entities = content.item(0);
        //再获取<Entities>中所有的下级标签List 即<Entity>,<Entity>,<Entity>,...
        QDomNodeList entityList = entities.childNodes();
        //qDebug() << entityList.size() << endl;
        QList<SimpleEntity> simpleentitylist;
        QList<BoolEntity> boolentitylist;
        //遍历一个xml中的entity
        int i;
        for (int i = 0; i < entityList.size(); i++) {
            //获取第i个<Entity>
            //转换为元素
            QDomElement entity = entityList.item(i).toElement();
            QString  type = entity.attribute("Type");

            if (type == ("simple")) {

                SimpleEntity simpleEntity;

                simpleEntity.setEntityId((entity.attribute("ID")).toInt());
                //QVariant t = entity.attribute("Visible");
                simpleEntity.setVisible(entity.attribute("Visible"));
                //获取<Entity>中的下级标签List 即<图元/>,<Color/>,<TransformMatrix/>
                QDomNodeList entityParas = entity.childNodes();
                //遍历<图元/>,<Color/>,<TransformMatrix/>
                int j;
                for (int j = 0; j < entityParas.size(); j++) {
                    QDomElement item = entityParas.item(j).toElement();
                    if (item.nodeName() == ("Color")) {
                        simpleEntity.setR((item.attribute("R")).toInt());
                        simpleEntity.setG((item.attribute("G")).toInt());
                        simpleEntity.setB((item.attribute("B")).toInt());
                        simpleEntity.setA((item.attribute("A")).toInt());
                    }
                    else if (item.nodeName() == ("TransformMatrix")) {
                        simpleEntity.setTransformMatrix(item.attribute("Value"));
                    }
                    else {
                        simpleEntity.setGraphicElement(item);
                    }

                }
                simpleentitylist.append(simpleEntity);
                // modFile.setSimpleEntities(simpleentitylist);
                  //qDebug() << modFile.getSimpleEntities().length() << endl;
            }
            else if (type == ("boolean")) {
                BoolEntity boolEntity;
                boolEntity.setEntityId((entity.attribute("ID")).toInt());
                //QVariant t = entity.attribute("Visible");
                boolEntity.setVisible(entity.attribute("Visible"));
                //获取<Entity>中的下级标签List 即<Boolean/>,<Color/>,<TransformMatrix/>
                QDomNodeList entityChildren = entity.childNodes();
                //遍历<Boolean/>,<Color/>,<TransformMatrix/>
                int j;
                for (int j = 0; j < entityChildren.size(); j++) {
                    QDomElement item = entityChildren.item(j).toElement();

                    if (item.nodeName() == ("Color")) {
                        boolEntity.setR((item.attribute("R")).toInt());
                        boolEntity.setG((item.attribute("G")).toInt());
                        boolEntity.setB((item.attribute("B")).toInt());
                        boolEntity.setA((item.attribute("A")).toInt());
                    }
                    else if (item.nodeName() == ("TransformMatrix")) {
                        QString mat = item.attribute("Value");
                        boolEntity.setTransformMatrix(item.attribute("Value"));
                    }
                    else if (item.nodeName() == ("Boolean")) {
                        boolEntity.setBoolEntityId1((item.attribute("Entity1")).toInt());
                        boolEntity.setBoolEntityId2((item.attribute("Entity2")).toInt());
                        boolEntity.setBoolType(item.attribute("Type"));

                    }

                }
                boolentitylist.append(boolEntity);
                //modFile.setBoolEntities(boolentitylist);
            }


            //qDebug() << modFile.getSimpleEntities().length() << endl;
        }
        modFile.setSimpleEntities(simpleentitylist);

        modFile.setBoolEntities(boolentitylist);

        //qDebug() <<"SimpleEntities:" << modFile.getSimpleEntities().length() << "BoolEntities:"<< modFile.getBoolEntities().size() << endl;

    //qDebug() << modFile.getBoolEntities().size()<< endl;
   // boolEntity.getBoolType() == ("Difference")
    }
    //qDebug() << modFile << endl;
    return modFile;
}

//读内容是三元组数据的文件,fam
QList<TripletPara> GimReader::readTripletPara(QString fileName, EntityName entityName)
{
    if (fileName.isEmpty()) {
        qDebug() << "fam文件不存在" << endl;
        throw"fam不存在";
    }

    QString readPath;

    if (entityName == EntityName::ObjectModel)
    {
        readPath = path + "/DEV/" + fileName;
        //qDebug() << "进入dev中的fam文件" << endl;
    }
    else
    {
        readPath = path + "/CBM/" + fileName;
    }
    QList<TripletPara> content;
    QFile file(readPath);
    try {
        if (file.open(QIODevice::ReadOnly)) {
            //qDebug() << "开始读取fam数据" << endl;
            QTextStream reader(&file);
            QTextCodec* code = QTextCodec::codecForName("utf8");//本人采用的是UTF8格式 显示的
            reader.setCodec(code);
            //QBuffer reader(&file.readAll());
            QString tStr;
            while (!reader.atEnd()) {
                tStr = reader.readLine();
                if (tStr.isEmpty() || tStr == ("[设计参数]")) {
                    continue;
                }
                QStringList splits = tStr.split("=");

                if (splits.length() == 3) {
                    TripletPara para;

                    para.setParaNameEN(splits[0]);
                    para.setParaNameCH(splits[1]);
                    para.setParameter(splits[2]);
                    content.append(para);
                    //TripletPara tripletPara(splits[0], splits[1], splits[2]);
                }
                else if (splits.length() == 2) {
                    TripletPara para;
                    para.setParaNameEN(splits[0]);
                    para.setParaNameCH(splits[1]);
                    para.setParameter("");
                    content.append(para);

                }

            }
        }
    }
    catch (std::exception e) {
        qDebug() << "文件读取失败" << endl;
        throw ("exception", path + "文件读取失败");
        throw ("exception", e.what());

    }
    return content;
}
//读内容是二元组数据的文件,cbm
QMap<QString, QString> GimReader::readDoublePara(QString readPath)
{


    if (readPath.isEmpty()) {
        qDebug() << "读取二元组文件失败" << endl;
        throw"project.cbm不存在";
    }
    //qDebug() << readPath << endl;
    QFile file(readPath);

    //QBuffer reader;
    QMap<QString, QString> content;
    try {
        // QBuffer reader(&file.readAll());
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream reader(&file);
            QTextCodec* code = QTextCodec::codecForName("utf8");//本人采用的是UTF8格式 显示的
            reader.setCodec(code);
            QString tStr;
            int flag = 0;  //判断是否是solidmodel+i
            while (!reader.atEnd()) {
                tStr = reader.readLine();
                //qDebug() << tStr << endl;
                QStringList splits = tStr.split("=");

                if (flag == 1 && splits[0] == "TRANSFORMMATRIX0")
                {
                    content.insert("#" + splits[0], splits[1]);
                }
                else
                {
                    if (splits[0] == "TRANSFORMMATRIX0")
                    {
                        flag = 1;
                    }
                    content.insert(splits[0], splits[1]);
                }
            }

        }
    }
    catch (std::exception e) {
        qDebug() << e.what() << endl;
    }
    return content;
}
//读取xml格式的文件,mod
QDomNodeList GimReader::readXmlPara(QString readPath)
{
    if (readPath.isEmpty())
    {
        throw "文件不存在";
    }
    QFile file(readPath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {  // 以只读模式打开
        qDebug() << QString("Cannot read file %1(%2).").arg(readPath).arg(file.errorString());

    }
    QDomDocument doc;
    //将文件内容读到doc中
    QDomNodeList entitiesList;
    if (!doc.setContent(&file)) {
        qDebug() << "parse file failed at line" << endl;
        file.close();

    }
    else {

        //然后用firstChild得到根的结点
        QDomElement entity = doc.documentElement();
        //获取该节点的所有子结点
        entitiesList = entity.childNodes();//子结点是Entities 只有一个 他的子结点是Entity
       // qDebug() << entitiesList.length() << endl;
    }

    return  entitiesList;
}
//直接读取全部mod文件，用于画图
QList<ModFile> GimReader::GetGimModFileList2()
{
    /*QString a= path+"/MOD";
    QDir dir(a);
    QString filter;
    QStringList nameFilters;
    nameFilters << "*.mod" ;
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);*/
    //qDebug() << files.size() << endl;
    //qDebug() << files << endl;

    //for (int i = 0; i < files.size(); i++) {
        //QString ap=files[i];

        //qDebug() << ap << endl;
        //QString p = a +"/" + ap;
        //qDebug() << p << endl;
    QList<ModFile> ModFileList;
    /* ModFile modFile = readModFile("da247fc1-443b-4e56-9596-5f8755f0852c.mod");

     ModFileList.append(modFile);
     objectModel = readObjectModel("25fd64c8-0475-49d2-b8bc-bfda6e72141d.dev");
     sysParas = readTripletPara("16e3c189-4538-4f44-bff0-2434039fbe2a.fam", EntityName::ObjectModel);*/

     /*qDebug() << sysParas[1].getParaNameEN() << endl;
     qDebug() << sysParas[1].getParaNameCH() << endl;
     qDebug() << sysParas[1].getParameter() << endl;*/
     //}
     /*QString ap;
     ModFile modFile=readModFile(ap);
     ModFileList.append(modFile);*/
     //qDebug() << ModFileList.size() << endl;

    return ModFileList;
}
//从dev文件（设备）往下读
void GimReader::read()
{
    if (name > 0) {
        QString devname;
        if (name <= gimModFileList.size()) {
            devname = gimModFileList[name - 1].getobjFileName();//设备dev文件名
        }
        //else {
        //    devname = gimModFileList[name - gimModFileList.size() - 1].getobjFileName();//设备dev文件名
        //}
        //qDebug() << "devname:"<<devname << endl;
        objectModel = readObjectModel(devname);//读设备
        QString famname = objectModel.getfamFileName();
        //qDebug() << "fam:" << famname << endl;
        sysParas = readTripletPara(famname, EntityName::ObjectModel);
        //qDebug() << "选中sys:" << sysParas.size() << endl;
    }
}
//由一个dev获取对应的mod文件
QList<ModFile> GimReader::GetGimModFileList()
{
    //QList<ModFile> gimModFileList;
    //找出所有的dev文件，即所有的设备
    QString a = path + "/DEV";
    QDir dir(a);
    QString filter;
    QStringList nameFilters;
    nameFilters << "*.dev";
    QStringList files = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    //qDebug() << files.size() << endl;
    //qDebug() << files << endl;
    //遍历所有的dev文件
    for (int i = 0; i < files.size(); i++) {
        QString ap = files[i];                  //  一个dev文件名
        ObjectModel objectModel = readObjectModel(ap);        //读取dev文件
        //qDebug() << objectModel.getSymbolName() << endl;
        QList<QString> solidModels = objectModel.getSolidModels();  //获取dev引用的phm文件
        for (int i = 0; i < solidModels.size(); i++)
        {
            SolidModel solidModel = readSolidModel(solidModels[i]); //读取phm文件
            QList<QString> children = solidModel.getchildren();     //获取phm引用的mod文件
            for (int i = 0; i < children.size(); i++) {
                if (children[i].endsWith(".mod")) {
                    ModFile modFile = readModFile(children[i]);
                    modFile.setobjFileName(objectModel.getfileName());//将mod文件与dev对应上
                    gimModFileList.append(modFile);
                }
            }
        }

    }
    //qDebug() <<"mod文件的个数:"<< gimModFileList.size();
     //for (int i = 0; i < gimModFileList.size(); i++) {
     //    //qDebug() << i << endl;
     //    QString modname=gimModFileList[i].getFileName();
     //    QString devname=gimModFileList[i].getObjFileName();
     //    ObjectModel objectModel = readObjectModel(devname);
     //    QString famname=objectModel.getFamFileName();
     //    //QList<TripletPara> sysParas=readTripletPara(famname, objectModel.getEntityName());
     //    //qDebug() << "mod:" << modname <<" "<<"dev:"<<devname<< " " << "fam:" << famname << endl;
     //    qDebug() << "mod:" << modname<<" "<<objectModel.getSymbolName() << endl;
     //}
     //qDebug() << "dev" << gimModFileList[0].getObjFileName();
     //qDebug() << devname << endl;
     //ObjectModel objectModel1=readObjectModel(gimModFileList[0].getObjFileName());
     //qDebug() << objectModel1.getFamFileName() << endl;
    return gimModFileList;
}

//读project.cbm得f1文件名
QList<QString> GimReader::getFlSystemNode()
{

    QString readPath = path + "/CBM/" + "project.cbm";
    //qDebug() << readPath << endl;
    QMap<QString, QString> content = readDoublePara(readPath);
    if (!content.isEmpty()) {
        FlSystemNode.append(content.value("SUBSYSTEM"));
        getF2SystemNode(content.value("SUBSYSTEM"));
    }
    else {
        qDebug() << "读取project.cbm失败" << endl;
    }
    //readF1System(content.value("SUBSYSTEM"));

    //qDebug() << "f1文件名："<<FlSystemNode << endl;
    return FlSystemNode;
}
//读f1.cbm得f2文件名
QList<QString> GimReader::getF2SystemNode(QString fileName)
{
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);
    if (!content.isEmpty()) {
        //检验标识
        if (content.value("ENTITYNAME") != ("F1System")) {
            qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;
            throw "CODE_ERROR";
        }
        if (content.count("SUBSYSTEMS.NUM") > 0) {
            if (content.value("SUBSYSTEMS.NUM") != "0") {
                for (int i = 0; i < (content.value("SUBSYSTEMS.NUM")).toInt(); i++) {
                    //qDebug() << content.value("SUBSYSTEM" + QString::number(i)) << endl;
                    //f1System.setSubSystems(subsystems);
                    F2SystemNode.append(content.value("SUBSYSTEM" + QString::number(i)));
                    getF3SystemNode(content.value("SUBSYSTEM" + QString::number(i)));
                    //qDebug() << "f2文件名：" << content.value("SUBSYSTEM" + QString::number(i)) << endl;
                }
            }
        }
    }
    else {
        qDebug() << "读取一级.cbm失败" << endl;
    }
    return F2SystemNode;
}
//读f2.cbm得f3文件名
QList<QString> GimReader::getF3SystemNode(QString fileName)
{
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);
    if (!content.isEmpty()) {
        //检验标识
        if (content.value("ENTITYNAME") != ("F2System")) {
            qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;
            throw "CODE_ERROR";
        }
        if (content.count("SUBSYSTEMS.NUM") > 0) {
            if (content.value("SUBSYSTEMS.NUM") != "0") {
                for (int i = 0; i < (content.value("SUBSYSTEMS.NUM")).toInt(); i++) {
                    //qDebug() << content.value("SUBSYSTEM" + QString::number(i)) << endl;
                    //f1System.setSubSystems(subsystems);
                    F3SystemNode.append(content.value("SUBSYSTEM" + QString::number(i)));
                    F3asF4(content.value("SUBSYSTEM" + QString::number(i)));
                    //qDebug() << "f3文件名：" << content.value("SUBSYSTEM" + QString::number(i)) << endl;
                }
            }
        }
    }
    else {
        qDebug() << "读取二级.cbm失败" << endl;
    }
    return F3SystemNode;
}
//读f3.cbm得f4文件名
void GimReader::F3asF4(QString fileName)
{
    //读三级.cbm
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);
    if (!content.isEmpty()) {
        //检验标识
        if (content.value("ENTITYNAME") != ("F3System")) {
            qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;
            throw "CODE_ERROR";
        }
        if (content.count("BASEFAMILY1") > 0) {
            //F3toF4
            F3toF4Node.append(fileName);
            if (content.count("SUBSYSTEMS.NUM") > 0) {
                if (content.value("SUBSYSTEMS.NUM") != "0") {
                    for (int i = 0; i < (content.value("SUBSYSTEMS.NUM")).toInt(); i++) {
                        allF4SystemNode.append(content.value("SUBSYSTEM" + QString::number(i)));
                        getF4SystemNode(content.value("SUBSYSTEM" + QString::number(i)));
                    }
                }
            }
        }
        else {
            //F3toObj
            F3toObjNode.append(fileName);
        }
    }
    else {
        qDebug() << "读取三级.cbm失败" << endl;
    }
}
//读f4.cbm剔除
QList<QString> GimReader::getF4SystemNode(QString fileName)
{
    QString readPath = path + "/CBM/" + fileName;
    QMap<QString, QString> content = readDoublePara(readPath);
    if (!content.isEmpty()) {
        //检验标识
        if (content.value("ENTITYNAME") != ("F4System")) {
            qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;
            throw "CODE_ERROR";
        }
        F4SystemNode.append(fileName);
        if (content.count("SUBDEVICES.NUM") > 0)
        {
            if (content.value("SUBDEVICES.NUM") != ("0"))
            {
                havasubdevices.append(fileName);
                for (int i = 0; i < (content.value("SUBDEVICES.NUM")).toInt(); i++)
                {
                    PartIndexNode.append(content.value("SUBDEVICE" + QString::number(i)));
                    //readPartIndex(content.value("SUBDEVICE" + QString::number(i)));
                }
            }
        }
    }
    else {
        qDebug() << "四级.cbm为空：" + fileName << endl;
    }
    return F4SystemNode;
}

//读F4得PartIndex
QList<QString> GimReader::getPartIndexNode(QString fileName)
{
    //QString readPath = path + "/CBM/" + fileName;
    //QMap<QString, QString> content = readDoublePara(readPath);
    //if (!content.isEmpty()) {
    //    //检验标识
    //    if (content.value("ENTITYNAME") != ("F4System")) {
    //        qDebug() << path << "/CBM/ " << fileName << "标识错误" << endl;
    //        throw "CODE_ERROR";
    //    }
    //    if (content.count("SUBDEVICES.NUM") > 0)
    //    {
    //        if (content.value("SUBDEVICES.NUM") != ("0"))
    //        {
    //            for (int i = 0; i < (content.value("SUBDEVICES.NUM")).toInt(); i++)
    //            {
    //                PartIndexNode.append(content.value("SUBDEVICE" + QString::number(i)));
    //                //readPartIndex(content.value("SUBDEVICE" + QString::number(i)));
    //            }
    //        }
    //    }
    //}
    //else {
    //    qDebug() << "读取四级.cbm失败"+ fileName << endl;
    //}
    return PartIndexNode;
}
//设备级与mod文件对应
QList<ModFile> GimReader::GetGimModFileList1()
{
    //1、设备级是F3.cbm
    if (!F3toObjNode.isEmpty()) {
        for (int i = 0; i < F3toObjNode.size(); i++) {
            //QString readPath = path + "/CBM/" + F3toObjNode[i];
            F3System f3System = readF3System(F3toObjNode[i]);//读f3.cbm文件
            QString f3objectModel = f3System.getObjectModel();//获得f3设备级对应的dev
            QString transformMatrix2 = f3System.getTransformMatrix();//获取f3设备对应的坐标
            //qDebug() << f3objectModel << endl;
            ObjectModel objectModel = readObjectModel(f3objectModel);//读dev文件
            QList<QString> solidModels = objectModel.getSolidModels();  //获取dev引用的phm文件
            for (int i = 0; i < solidModels.size(); i++)
            {
                SolidModel solidModel = readSolidModel(solidModels[i]); //读取phm文件
                QList<QString> children = solidModel.getchildren();     //获取phm引用的mod文件
                for (int i = 0; i < children.size(); i++) {
                    if (children[i].endsWith(".mod")) {
                        ModFile modFile = readModFile(children[i]);
                        modFile.setobjFileName(objectModel.getfileName());//将mod文件与dev文件名对应上
                        modFile.setSymbolName(objectModel.getSymbolName());//设备名
                        modFile.settransformMatrix2(transformMatrix2);//设备坐标
                        gimModFileList.append(modFile);
                        //devices.append(objectModel.getSymbolName());
                    }
                }
            }
        }
    }
    //2、设备级是F4.cbm
    if (!F4SystemNode.isEmpty()) {
        for (int i = 0; i < F4SystemNode.size(); i++) {
            F4System f4System = readF4System(F4SystemNode[i]);//读f4.cbm文件
            QString f4objectModel = f4System.getObjectModel();//获得f4设备级对应的dev
            QString transformMatrix2 = f4System.getTransformMatrix();//获取f4设备对应的设备坐标
            ObjectModel objectModel = readObjectModel(f4objectModel);//读dev文件
           // qDebug() << objectModel << endl;
            //1、不存在部件dev
            if (objectModel.getSubObjectModels().isEmpty()) {
                QList<QString> solidModels = objectModel.getSolidModels();  //获取dev引用的phm文件
                for (int i = 0; i < solidModels.size(); i++)
                {
                    SolidModel solidModel = readSolidModel(solidModels[i]); //读取phm文件
                    QList<QString> children = solidModel.getchildren();     //获取phm引用的mod文件
                    for (int i = 0; i < children.size(); i++) {
                        if (children[i].endsWith(".mod")) {
                            ModFile modFile = readModFile(children[i]);
                            modFile.setobjFileName(objectModel.getfileName());//将mod文件与dev文件名对应上
                            modFile.setSymbolName(objectModel.getSymbolName());//设备名
                            modFile.settransformMatrix2(transformMatrix2);//设备坐标
                            gimModFileList.append(modFile);
                            //devices.append(objectModel.getSymbolName());
                        }
                    }
                }
            }
            else {//2、存在部件dev
                QList<QString> subdevices = objectModel.getSubObjectModels();//获取部件dev
                QList<QString>transformMatrix1 = objectModel.getsubObjTransformMatrix();//获取部件坐标
               // qDebug() << subdevices << endl;
                for (int i = 0; i < subdevices.size(); i++) {
                    ObjectModel objectModel1 = readObjectModel(subdevices[i]);//读部件dev
                    QList<QString> solidModels1 = objectModel1.getSolidModels();  //获取dev引用的phm文件

                    for (int a = 0; a < solidModels1.size(); a++)
                    {
                        SolidModel solidModel1 = readSolidModel(solidModels1[a]); //读取phm文件
                        QList<QString> children1 = solidModel1.getchildren();     //获取phm引用的mod文件
                        for (int j = 0; j < children1.size(); j++) {
                            if (children1[j].endsWith(".mod")) {
                                ModFile modFile1 = readModFile(children1[j]);
                                modFile1.setobjFileName(objectModel.getfileName());//将mod文件与dev文件名对应上
                                modFile1.setSymbolName(objectModel.getSymbolName());//设备名
                                modFile1.settransformMatrix1(transformMatrix1[i]);//设备部件坐标
                                modFile1.settransformMatrix2(transformMatrix2);//设备坐标
                                gimModFileList.append(modFile1);
                                //devices.append(objectModel.getSymbolName());
                            }
                        }
                    }
                }
            }
        }
    }
    //qDebug() << "gimModFileList的个数：" << gimModFileList.size() << endl;
    //for (int i = 0; i < gimModFileList.size(); i++) {
        //qDebug() << "mod:" << gimModFileList[i].getfileName() << endl;
       // qDebug() << "设备名： " << gimModFileList[i].getSymbolName() << ";" << "mod:" << gimModFileList[i].getfileName() << "部件坐标：" << gimModFileList[i].gettransformMatrix1() << ";" << "设备坐标：" << gimModFileList[i].gettransformMatrix2() << endl;
    //}
    return gimModFileList;
}