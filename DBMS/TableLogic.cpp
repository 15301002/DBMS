#include "stdafx.h"
#include "TableLogic.h"
#include "AppException.h"

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