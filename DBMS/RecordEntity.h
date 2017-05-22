#pragma once

class CRecordEntity : public CObject{
private :
	CMapStringToString mapData;

public :
	CRecordEntity();
	CRecordEntity(CRecordEntity &e);
	~CRecordEntity();
	CRecordEntity & operator=(const CRecordEntity & e);

public :
	void PutVARCHAR(CString strKey, CString value);
	void PutINT(CString strKey, int value);
	void PutDOUBLE(CString strKey, double value);
	void PutDATETIME(CString strKey, SYSTEMTIME value);
	void PutBOOL(CString strKey, BOOL value);
	CString Get(CString strKey);
};

typedef CTypedPtrArray<CPtrArray, CRecordEntity*> RECORDARR;