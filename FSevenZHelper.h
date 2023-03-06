#pragma once
#pragma warning(disable : 4530)

//7Z类型

//enum class ESPSevenZType
//{
//	OpType_None,
//	OpType_Compress,		//压缩
//	OpType_Decompression,	//解压
//};


#include <iostream>
#include <string>
#include <functional>
#include "E:/QT/bit7z-master/include/bit7z.hpp"
#include "E:/QT/bit7z-master/include/bit7zlibrary.hpp"
#include <QtCore/qstring.h>

using namespace bit7z;

class FSevenZHelper
{
private:


public:


	//ESPSevenZType m_OpType;		//当前是解压还是压缩
	FSevenZHelper();
	~FSevenZHelper();
	void Compress(const QString& Src, const QString& Dest);	//压缩
	void Extract(const QString& Src, const QString& Dest);		//解压
	void GetFileSuffix(const QString& Path);//获取文件后缀

	static std::wstring StringToWString(const std::string& str);
	/*
	*	外部调用这个函数进行解压缩
	*
	*	参数1:	ESPSevenZType 传入是解压还是压缩的枚举
	*	参数2:	const FString& Src 你要压缩或解压的全路径
	*	参数3:	你的最终路径
	*			如果该参数传值的时候为空的话
	*			1>解压时候会在同级文件夹下创建一个根据Src去掉压缩文件后缀的文件夹
	*			2>压缩的话会在同级文件夹下默认压缩成一个.gspp的文件, 其实就是7z格式
	*
	*	Notes:不支持压缩成rar
	*/
	//void CompressDecompression(ESPSevenZType type, const QString& Src, const QString& Dest);



private:

	QString m_SourcePath;		//源文件路径
	QString m_DestDir;			//目标路径
	QString m_FileSuffix;		//根据原路径拆出来的文件后缀
	QString DefaultSuffix;		//默认后缀
};
//#endif

