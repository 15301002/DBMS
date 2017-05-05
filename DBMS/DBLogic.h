#pragma once
#include "DBEntity.h"
class CDBLogic
{
public:
	CDBLogic();
	~CDBLogic();
	bool CreateDatabase(CDBEntity & e);
	bool GetDatabase(CDBEntity & e);
};

