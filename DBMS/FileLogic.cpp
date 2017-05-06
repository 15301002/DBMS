#include "stdafx.h"
#include "FileLogic.h"
#include "AppException.h"

CFileLogic::CFileLogic(){}


CFileLogic::~CFileLogic(){}

CString CFileLogic::GetDBFolder(CString strName)
{
	CString strFolder = _T("");
	try
	{
		// Get the path of the database folder
		strFolder.Format(_T("data\\%s"), strName);
		strFolder = GetAbsolutePath(strFolder);
	}
	catch (CAppException* e)
	{
		throw e;
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of the database folder!"));
	}

	return strFolder;
}

CString CFileLogic::GetDBFile()
{
	CString strPath = _T("");
	try
	{
		strPath = GetAbsolutePath(_T("DBMS.db"));
	}
	catch (CAppException* e)
	{
		throw e;
	}
	return strPath;
}

CString CFileLogic::GetAbsolutePath(const CString strRelativePath)
{
	CString strFolder = _T("");
	try
	{
		// Get the absolute path of the executable file
		wchar_t acExeFullPath[MAX_PATH];
		::GetModuleFileName(NULL, acExeFullPath, MAX_PATH);
		CString strFolder = acExeFullPath;
		// Get the folder path of the executable file
		int pos = strFolder.ReverseFind('\\');
		strFolder = strFolder.Left(pos + 1);
		// Return absolute path
		return strFolder + strRelativePath;
	}
	catch (CException* e)
	{
		e->Delete();
		throw new CAppException(_T("Failed to get the path of file!"));
	}
	catch (...)
	{
		throw new CAppException(_T("Failed to get the path of file!"));
	}

	return strFolder;
}
