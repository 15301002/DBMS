#pragma once
#include "Data Structure.h"
class CRecordEntity {
private :
	CMapStringToString mapData;

public :
	CRecordEntity();
	CRecordEntity(CRecordEntity &e);
	~CRecordEntity();
public :
	void PutVARCHAR(CString strKey, VARCHAR value);
	void PutINT(CString strKey, INTEGER value);
	void PutDOUBLE(CString strKey, DOUBLE value);
	void PutDATETIME(CString strKey, DATETIME value);
	CString Get(CString strKey);
};