#include "Qt8.h"
#include<QtCore/qdebug.h>
#include<QtWidgets/QFileDialog>
#include <stdio.h>
#include <algorithm>    // find

int flag1 = 1;
int flag2 = 0;
Qt8::Qt8(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    // 隐藏标题栏
    setWindowFlags(Qt:: Window | Qt::FramelessWindowHint);
    //setWindowFlags(Qt::FramelessWindowHint);
    //全屏显示
    //showFullScreen();
    showMaximized();
    //// 设置背景图片
    //setAutoFillBackground(true);    // 这句要加上, 否则可能显示不出背景图.
    //QPalette palette = this->palette();
    ////palette.setColor(QPalette::Window, Qt::red);  // 设置背景色
    ////palette.setBrush(this->backgroundRole(), Qt::black);// 设置背景色
    //palette.setBrush(QPalette::Window,
    //    QBrush(QPixmap("G:/Example C/example12/picture/变电站3.jpg").scaled(    // 缩放背景图.
    //        this->size(),
    //        Qt::IgnoreAspectRatio,
    //        Qt::SmoothTransformation)));    // 使用平滑的缩放方式
    //this->setPalette(palette);
    ////属性栏底色透明
    //QPalette pll = ui.tableWidget->palette();
    //pll.setBrush(QPalette::Base, QBrush(QColor(190, 190, 190, 255)));
    //ui.tableWidget->setPalette(pll);

    ui.pushButton1->setIcon(QPixmap("E:/QT/Qt8/picture/导入.png"));
    ui.pushButton2->setIcon(QPixmap("E:/QT/Qt8/picture/导出.png"));
    ui.pushButton3->setIcon(QPixmap("E:/QT/Qt8/picture/关闭.png"));
    ui.pushButton4->setIcon(QPixmap("E:/QT/Qt8/picture/显示.png"));
    connect(ui.pushButton1, SIGNAL(clicked()), this, SLOT(slotOpenFile()));
    connect(ui.pushButton2, SIGNAL(clicked()), this, SLOT(slotSaveFile()));
    connect(ui.pushButton3, SIGNAL(clicked()), this, SLOT(close()));

    ui.pushButton1->setFixedSize(100, 34);
    ui.pushButton2->setFixedSize(100, 34);
    ui.pushButton3->setFixedSize(100, 34);
    ui.pushButton4->setFixedSize(100, 34);
    ui.pushButton1->setStyleSheet("font-size : 15px");
    ui.pushButton2->setStyleSheet("font-size : 15px");
    ui.pushButton3->setStyleSheet("font-size : 15px");
    ui.pushButton4->setStyleSheet("font-size : 15px");
    /*ui.pushButton1->setFont(QFont("song", 20));
    ui.pushButton2->setFont(QFont("song", 20));
    ui.pushButton3->setFont(QFont("song", 20));*/

    //创建下拉复选按钮
    m_menu = new QMenu();
    m_mainAction = new QAction(m_menu);
    m_boolAction = new QAction(m_menu);
    m_mainAction->setText("主体图");
    m_boolAction->setText("布尔复杂图");
    m_mainAction->setCheckable(true);//是否可以check
    m_boolAction->setCheckable(true);//是否可以check
    m_mainAction->setChecked(true);//默认主图是选中的
    m_mainAction->setFont(QFont("song", 12, 50));
    m_boolAction->setFont(QFont("song", 12, 50));
    m_menu->addAction(m_mainAction);
    m_menu->addAction(m_boolAction);
    connect(m_mainAction, &QAction::triggered, this, &Qt8::mainFunc);
    connect(m_boolAction, &QAction::triggered, this, &Qt8::boolFunc);
    ui.pushButton4->setMenu(m_menu);//设置菜单
  /*  connect(m_menu, SIGNAL(triggered(QAction* m_mainAction)),this, SLOT(mainFunc(QAction* m_mainAction)));
    connect(m_menu, SIGNAL(triggered(QAction * m_boolAction)), this, SLOT(boolFunc(QAction* m_boolAction)));*/

    /*  connect(m_menu, SIGNAL(), this, SLOT(setstatus(QAction*)));
      connect(m_mainAction, SIGNAL(), this, SLOT(mainFunc()));
      connect(m_boolAction, SIGNAL(), this, SLOT(boolFunc()));*/
      //ui.pushButton4->setStyleSheet("QPushButton::menu-indicator{image:none;}");//不显示下拉三角图标


    label1->setFont(QFont("song", 10, 50));
    label1->setText("文件名：");
    label1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label1->setMinimumSize(5, 10);

    label3->setFont(QFont("song", 10, 50));
    label3->setText("设备名：");
    label3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label3->setMinimumSize(5, 10);

    label5->setFont(QFont("song", 10, 50));
    label5->setText("部件索引数量：");
    label5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label5->setMinimumSize(5, 10);

    label7->setFont(QFont("song", 10, 50));
    label7->setText("逻辑模型数量：");
    label7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label7->setMinimumSize(5, 10);

    ui.gridLayout->setSpacing(10);
    ui.gridLayout->addWidget(label1, 0, 0);
    ui.gridLayout->addWidget(label2, 0, 1);
    ui.gridLayout->addWidget(label3, 1, 0);
    ui.gridLayout->addWidget(label4, 1, 1);
    ui.gridLayout->addWidget(label5, 2, 0);
    ui.gridLayout->addWidget(label6, 2, 1);
    ui.gridLayout->addWidget(label7, 3, 0);
    ui.gridLayout->addWidget(label8, 3, 1);

    pTimer = new QTimer(this); //创建一个定时器
     //将定时器的计时信号与updateGL()绑定
    connect(pTimer, SIGNAL(timeout()), this, SLOT(call()));
    pTimer->start(10);//以10ms为一个计时周期
}
void Qt8::slotOpenFile()
{
    QString s = QFileDialog::getOpenFileName(this, "打开文件", "G:/gim文件", "Files(*.gim)");
    qDebug() << s << endl;//得到gim文件所在路径
    qDebug() << "开始读取GIM" << endl;
    GimReader gimreaderopen;
    gimreaderopen.ImportGim(s);
    //gimreaderopen.GetGimModFileList2();
    gimreaderopen.run();
    //gimreaderopen.readXmlPara("G:/idea/gim/src/main/resources/gimUncompress/正方体/MOD/03aa690f-f38c-4bd9-97cf-c4b97e896294.mod");
    qDebug() << "读取GIM结束" << endl;
}
void Qt8::slotSaveFile()
{
    QString s = QFileDialog::getSaveFileName(this, "保存文件", "G:/gim文件", "Files(*.gim)");
    GimReader gimreadersave;
    gimreadersave.ExportGim(s);
}
void Qt8::close()
{
    QWidget::close();
}
void Qt8::mainFunc()
{
    if (m_mainAction->isChecked()) {
        flag1 = 1;
        qDebug() << "显示主图！" << "" << "flag1:" << flag1;
    }
    else {
        flag1 = 0;
        qDebug() << "flag1:" << flag1;
    }
}
void Qt8::boolFunc()
{
    if (m_boolAction->isChecked()) {
        flag2 = 1;
        qDebug() << "显示布尔图！" << "" << "flag2:" << flag2;
    }
    else {
        flag2 = 0;
        qDebug() << "flag2:" << flag2;
    }
}

void Qt8::call()
{
    getInfo(objectModel, sysParas);
}
//设备级（DEV）属性显示
void Qt8::getInfo(ObjectModel objectModel, QList<TripletPara> sysParas)
{
    //qDebug() << "创建属性" << endl;
    if (sysParas.size() != 0) {
        label2->setFont(QFont("song", 10, 50));
        label2->setText(objectModel.getfileName());//dev编号
        label2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        label2->setMinimumSize(5, 10);

        label4->setFont(QFont("song", 10, 50));
        label4->setText(objectModel.getSymbolName());
        label4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        label4->setMinimumSize(5, 10);

        label6->setFont(QFont("song", 10, 50));
        label6->setText(QString::number(objectModel.getSubObjectModels().size()));
        label6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        label6->setMinimumSize(5, 10);

        label8->setFont(QFont("song", 10, 50));
        label8->setText(QString::number(objectModel.getSolidModels().size()));
        label8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        label8->setMinimumSize(5, 10);

        ui.tableWidget->setColumnCount(3);//设置列数
        int i = sysParas.size();
        ui.tableWidget->setRowCount(i);//设置行数
        ui.tableWidget->horizontalHeader()->setVisible(false);//隐藏水平表头
        ui.tableWidget->verticalHeader()->setVisible(false);//隐藏垂直表头
        ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui.tableWidget->setFont(QFont("song", 10, 50));
        for (int i = 0; i < sysParas.size(); i++) {
            ui.tableWidget->setItem(i, 0, new QTableWidgetItem(sysParas[i].getParaNameEN()));
            ui.tableWidget->setItem(i, 1, new QTableWidgetItem(sysParas[i].getParaNameCH()));
            ui.tableWidget->setItem(i, 2, new QTableWidgetItem(sysParas[i].getParameter()));
        }
    }
}
