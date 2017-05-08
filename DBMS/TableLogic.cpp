#include "stdafx.h"
#include "TableLogic.h"
#include "AppException.h"
#include "FileUtil.h"
CTableLogic::CTableLogic()
{
	}


CTableLogic::~CTableLogic()
{
}

int CTableLogic::GetTables(const CString strDBName, TABLEARR &arrTables)
{
	int nCount = 0;

	try
	{
		// Get the table description file
		CString strTableFile = fileLogic.GetTableFile(strDBName);

		// Query talbe information
		nCount = daoTB.GetTables(strTableFile, arrTables);

		// Read the table structure from the table definition file one by one
		for (int i = 0; i < nCount; i++)
		{
			CTableEntity* pTable = arrTables.GetAt(i);
			//daoTB.GetFields(pTable->GetTdPath(), *pTable);
		}
	}
	catch (CAppException e)
	{
		throw e;
	}

	return nCount;
}

bool CTableLogic::CreateTable(const CString strDBName, CTableEntity &te)
{
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString strTableFile = fileLogic.GetTableFile(strDBName);
		if (CFileUtil::IsValidFile(strTableFile) == false)
		{
			if (CFileUtil::CreateFile(strTableFile) == false)
			{
				return false;
			}
		}

		// Set the path of the table definition file
		te.SetTdPath(fileLogic.GetTbDefineFile(strDBName, te.GetName()));
		// Set the path of the record file
		te.SetTrdPath(fileLogic.GetTbRecordFile(strDBName, te.GetName()));

		// Create table and save table information
		if (daoTB.Create(strTableFile, te) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException* e)
	{
		throw e;
	}

	return false;
}