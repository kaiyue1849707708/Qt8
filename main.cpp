#include "Qt8.h"
#include <QtWidgets/QApplication>

void initQss() {
    QFile file("E:/QT/Qt2/orange-dark.qss");
    if (!file.open(QIODevice::ReadOnly))
        exit(0);

    QTextStream in(&file);
    QString css = in.readAll();
    qApp->setStyleSheet(css);
    //qApp->setFont(QFont("Î¢ÈíÑÅºÚ", 9));
    
    return;
}
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    initQss();
    
    Qt8 w;
   
    w.show();

    return a.exec();

}
