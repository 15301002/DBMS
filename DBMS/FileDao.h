#pragma once
#include "DBEntity.h"
class CFileDao
{
public:
	CFileDao();
	~CFileDao();
	CString GetDBFile();
	CString GetDBFolder();
	CString GetInfoFile();
	bool ProduceDBFile(CDBEntity & e);
};

