#pragma once
class CFileLogic
{
public:
	CFileLogic();
	~CFileLogic();
	CString GetDBFolder(CString strName);
	CString GetDBFile();
	CString GetAbsolutePath(const CString strRelativePath);
};

