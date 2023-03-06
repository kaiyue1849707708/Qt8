
#pragma once
#include <QtCore/qstring.h>
class TripletPara
{
public:


    QString getParaNameCH() {
        return QString(paraNameCH);
    }
    void setParaNameCH(QString paraNameCH) {
        this->paraNameCH = paraNameCH;
    }
    QString getParaNameEN() {
        return QString(paraNameEN);
    }
    void setParaNameEN(QString paraNameEN) {
        this->paraNameEN = paraNameEN;
    }

    QString getParameter() {
        return QString(parameter);
    }
    void setParameter(QString parameter) {
        this->parameter = parameter;
    }
private:
    QString paraNameEN;
    QString paraNameCH;
    QString parameter;

};





