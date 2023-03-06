#include "FSevenZHelper.h"
#include <QtCore/qfileinfo.h>
#include<QtCore/qdebug.h>
FSevenZHelper::FSevenZHelper()
{
}

FSevenZHelper::~FSevenZHelper()
{
}

void FSevenZHelper::Compress(const QString& Src, const QString& Dest)
{
	if (Src.isEmpty()) return;

	//1>源文件(路径或者单个文件) 你要对其压缩
	QFileInfo dir(Src);
	m_SourcePath = dir.absoluteFilePath();

	//2>获取文件后缀
	GetFileSuffix(Dest);

	//3>判断当前传入的文件路径是否和解析的后缀一样
	if (!Dest.isEmpty())
	{
		QFileInfo dir(Dest);
		m_DestDir = dir.absoluteFilePath();
		QFile file(m_DestDir);
		if (file.exists()) {
			file.remove();
		}
		file.open(QIODevice::ReadWrite);
		file.close();
		if (!m_DestDir.endsWith(m_FileSuffix))
		{
			m_DestDir.append(".");
			m_DestDir.append(m_FileSuffix);
		}
	}
	else
	{
		//3>如果目标路径不设置的话, 会根据当前的压缩文件名称或者压缩文件路径名称创建一个.gspp(7z)的压缩文件出来
		m_DestDir = m_SourcePath;
		if (!m_FileSuffix.isEmpty())
		{
			//创建一个同级文件夹路径
			QString RemoveEndStr = (".");
			RemoveEndStr.append(m_FileSuffix);
			m_DestDir.remove(RemoveEndStr);
		}
		m_DestDir.append(".");
		m_DestDir.append(DefaultSuffix);
	}

	try {
		bit7z::Bit7zLibrary lib(L"7z.dll");
		std::shared_ptr<BitCompressor> compressor = nullptr;
		if (m_FileSuffix.compare(TEXT("7z")) == 0)
		{
			//后缀L".7z"
			compressor = std::make_shared<BitCompressor>(lib, BitFormat::SevenZip);
		}

		//将QString转换为std::string
		std::string msSourcePath = m_SourcePath.toStdString();
		std::string msDestDir = m_DestDir.toStdString();

		std::wstring src = StringToWString(msSourcePath.c_str());
		std::wstring dest = StringToWString(msDestDir.c_str());

		compressor->compressDirectory(src, dest);
		compressor->setUpdateMode(true);
	}
	catch (const BitException& ex) {
		//do something with ex.what()...
		qDebug() << ex.what() << endl;

	}
}

void FSevenZHelper::Extract(const QString& Src, const QString& Dest)
{//Src不能为空
	if (Src.isEmpty()) return;

	//1>源文件(压缩文件格式) 你要对其解压,获取绝对路径
	QFileInfo dir(Src);
	m_SourcePath = dir.absoluteFilePath();

	//2>获取文件后缀
	GetFileSuffix(Src);

	//3>设置目标路径
	if (!Dest.isEmpty())
	{
		QFileInfo dir(Dest);
		m_DestDir = dir.absoluteFilePath();
		QFile file(m_DestDir);
		if (file.exists()) {
			file.remove();
		}
		file.open(QIODevice::ReadWrite);
		file.close();
	}
	else
	{
		//3>如果目标路径不设置的话, 则会在同级目录创建一个同级文件夹出来
		m_DestDir = m_SourcePath;
		if (!m_FileSuffix.isEmpty())
		{
			//创建一个同级文件夹路径
			QString RemoveEndStr = (".");
			RemoveEndStr.append(m_FileSuffix);
			m_DestDir.remove(RemoveEndStr);
		}

	}

	try {
		bit7z::Bit7zLibrary lib(L"7z.dll");
		std::shared_ptr<bit7z::BitExtractor> extractor = nullptr;
		if (m_FileSuffix.compare(TEXT("7z")) == 0)//7z大小写不敏感
		{
			//后缀L".7z"
			extractor = std::make_shared<bit7z::BitExtractor>(lib, bit7z::BitFormat::SevenZip);
		}
		//将QString转换为std::string
		std::string msSourcePath = m_SourcePath.toStdString();
		std::string msDestDir = m_DestDir.toStdString();

		std::wstring src = StringToWString(msSourcePath.c_str());
		std::wstring dest = StringToWString(msDestDir.c_str());
		extractor->extract(src, dest);
	}
	catch (const BitException& ex) {
		//do something with ex.what()...
		qDebug() << ex.what() << endl;

	}
}
void FSevenZHelper::GetFileSuffix(const QString& Path)
{
	QFileInfo fileinfo;
	fileinfo = QFileInfo(Path);
	m_FileSuffix = fileinfo.suffix();
	////默认后缀格式
	//m_FileSuffix = DefaultSuffix;
	//QString Temp = FPaths::ConvertRelativePathToFull(Path);
	////获取文件后缀
	////将其按照路径拆分开
	//TArray<QString> arrSplit;
	//Temp.ParseIntoArray(arrSplit, TEXT("/"), true);
	//if (arrSplit.Num() > 1)
	//{
	//	Temp.RemoveFromEnd(arrSplit[arrSplit.Num() - 1]);
	//	//拿到最后一个, 再按照.拆分
	//	std::string Fin = arrSplit[arrSplit.Num() - 1];
	//	TArray<std::string> arrSplitPoint;
	//	Fin.ParseIntoArray(arrSplitPoint, TEXT("."), true);
	//	if (arrSplitPoint.Num() == 2)
	//	{
	//		m_FileSuffix = arrSplitPoint[1];
	//	}
	//}
}
std::wstring FSevenZHelper::StringToWString(const std::string& str) {
	int num = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* wide = new wchar_t[num];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wide, num);
	std::wstring w_str(wide);
	delete[] wide;
	return std::wstring(w_str);
}
