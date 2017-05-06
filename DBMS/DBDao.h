#pragma once
#include "DBEntity.h"
class CDBDao
{
public:
	CDBDao();
	~CDBDao();
	bool Create(CString strFilepath, CDBEntity & e);
	bool GetDatabase(CString name, CDBEntity & e);
};