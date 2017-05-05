#pragma once
#include "DBEntity.h"
class CDBDao
{
public:
	CDBDao();
	~CDBDao();
	bool Create(CString name, CDBEntity & e);
	bool GetDatabase(CString name, CDBEntity & e);
};