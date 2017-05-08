#pragma once
#include "TableDao.h"
#include "FileLogic.h"
#include "TableEntity.h"
class CTableLogic{
private:
	CTableDao daoTB;
	CFileLogic fileLogic;
public:
	CTableLogic();
	~CTableLogic();
	int GetTables(const CString strDBName, TABLEARR & arrTables);
	bool CreateTable(const CString strDBName, CTableEntity & te);
};

