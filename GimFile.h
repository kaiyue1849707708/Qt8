#pragma once
#include"QtCore/qlist.h"
#include "EntityName.h"
#include <QtCore/qstring.h>
using namespace std;
class GimFile
{
public:

	QString getParameter() {
		return QString(parentName);
	}
	void setParameter(QString parentName) {
		this->parentName = parentName;
	}
	QString getfileName() {
		return QString(fileName);
	}
	void setfileName(QString fileName) {
		this->fileName = fileName;
	}
	EntityName getentityName() {
		return entityName;
	}
	void setentityName(EntityName entityName) {
		this->entityName = entityName;
	}
private:

	QString parentName;
	EntityName entityName;
	QString fileName;
};
