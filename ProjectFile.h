#pragma once
#include"GimFile.h"
class ProjectFile :public GimFile
{
public:

    QString getBLHA() {
        return BLHA;
    }

    void setBLHA(QString BLHA) {
        this->BLHA = BLHA;
    }

    QString getSubSystem() {
        return subSystem;
    }

    void setSubSystem(QString subSystem) {
        this->subSystem = subSystem;
    }

private:
    //纬度，经度，高，北方向偏角
    QString BLHA;

    //引用的一级全站级cbm
    QString subSystem;

};


