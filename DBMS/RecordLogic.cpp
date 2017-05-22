#include "StdAfx.h"
#include "RecordLogic.h"
#include "AppException.h"
#include "FileUtil.h"

/**************************************************
[FunctionName]	Insert
[Function]	Create new rows in a table
[Argument]	CString strDBName: Database name
CTableEntity &te: Table information entity
CRecordEntity &re: Record information entity
[ReturnedValue]	bool: True if the operation is successful, otherwise false.
**************************************************/
bool CRecordLogic::Insert(const CString strDBName, CTableEntity &te, CRecordEntity &re)
{
	try
	{
		// Decide whether the file exists, if there is no,a file will be created.
		CString strTrdPath = te.GetTrdPath();
		if (CFileUtil::IsValidFile(strTrdPath) == false)
		{
			if (CFileUtil::CreateFile(strTrdPath) == false)
			{
				return false;
			}
		}

		// Insert a record
		if (m_daoRecord.Insert(te, re) == false)
		{
			return false;
		}

		// Modify record number
		int nRecordNum = te.GetRecordNum() + 1;
		te.SetRecordNum(nRecordNum);

		// Alert table information
		CString strTableFile = m_fileLogic.GetTableFile(strDBName);
		if (m_daoTable.AlterTable(strTableFile, te) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException *e)
	{
		throw e;
	}

	return false;
}

/**************************************************
[FunctionName]	SelectAll
[Function]	Retrieve all records from a specified table
[Argument]	CTableEntity &te: Table structure information
RECORDARR &data: Record information array
[ReturnedValue]	bool: True if the operation is successful otherwise false.
**************************************************/
bool CRecordLogic::SelectAll(CTableEntity &te, RECORDARR &data)
{
	try
	{
		// Read record
		if (m_daoRecord.SelectAll(te, data) == false)
		{
			return false;
		}

		return true;
	}
	catch (CAppException *e)
	{
		throw e;
	}

	return false;
}