#pragma once
#include "DataStructure.h"
#include "CharUtil.h"
class CFieldEntity : public CObject{
private :
	CString		strName;
	int			nType;
	int			nParam;
	SYSTEMTIME	tLMTime;
	int			nIntegrities;
public :
	CFieldEntity();
	CFieldEntity(CFieldEntity&);
	CFieldEntity(CString, int, int, int);
	~CFieldEntity();
	void SetField(Field fd);
	Field GetField();
public :
	
	void SetName(CString name);
	void SetType(int type);
	void SetParam(int param);
	void SetLMTime(SYSTEMTIME time);

	CString GetName();
	int GetType();
	int GetParam();
	SYSTEMTIME GetLMTime();
};
typedef CTypedPtrArray<CPtrArray, CFieldEntity*> FIELDARRAY;