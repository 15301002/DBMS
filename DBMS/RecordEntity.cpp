#include "stdafx.h"
#include "RecordEntity.h"
#include "TimeUtil.h"

CRecordEntity::CRecordEntity() {

}

CRecordEntity::CRecordEntity(CRecordEntity &e) {
	POSITION pos = e.mapData.GetStartPosition();
	CString strFieldName, strValue;
	while (pos)
	{
		e.mapData.GetNextAssoc(pos, strFieldName, strValue);
		mapData.SetAt(strFieldName, strValue);
	}
}

CRecordEntity::~CRecordEntity(){}

CRecordEntity &CRecordEntity::operator =(const CRecordEntity &e)
{
	CString strFieldName, strValue;
	POSITION ipos = e.mapData.GetStartPosition();
	while (ipos != NULL)
	{
		e.mapData.GetNextAssoc(ipos, strFieldName, strValue);
		mapData.SetAt(strFieldName, strValue);
	}

	return *this;
}

void CRecordEntity::PutVARCHAR(CString strKey, CString value) {
	mapData.SetAt(strKey, value);
}

void CRecordEntity::PutINT(CString strKey, int value) {

	CString strValue;
	strValue.Format(_T("%d"), value);
	mapData.SetAt(strKey, strValue);
}

void CRecordEntity::PutDOUBLE(CString strKey, double value) {

	CString strValue;
	strValue.Format(_T("%f"), value);
	mapData.SetAt(strKey, strValue);
}

void CRecordEntity::PutDATETIME(CString strKey, SYSTEMTIME value) {
	mapData.SetAt(strKey, CTimeUtil::ToLDatetimeString(value));
}

void CRecordEntity::PutBOOL(CString strKey, BOOL value)
{
	CString strValue;
	if (value == TRUE) 
		strValue.Format(_T("%d"), 1);
	else 
		strValue.Format(_T("%d"), 0);
	mapData.SetAt(strKey, strValue);
}

CString CRecordEntity::Get(CString strKey) {

	CString strVal;
	if (mapData.Lookup(strKey, strVal) == FALSE)
	{
		// Get the default value
		strVal = _T("");
	}
	return strVal;
}
