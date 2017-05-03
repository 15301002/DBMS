#pragma once
#include "Data Structure.h"
#include "CFieldEntity.h"

class CTableEntity : public CObject{
private :
	CString		strName;
	int			nRecordNum;
	CString		strTdPath;
	CString		strTrdPath;
	CString		strTicPath;
	CString		strTidPath;
	SYSTEMTIME	tCtTime;
	SYSTEMTIME	tLMTime;
	FIELDARRAY	arrFields;
public :
	CTableEntity(CString strName);
	CTableEntity();
	~CTableEntity();
public :
	CFieldEntity* AddField(CFieldEntity &field);
	CFieldEntity* GetFieldAt(int index);

};
