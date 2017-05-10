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
	void SetIntegerities(int integerites);

	CString GetName();
	int GetType();
	int GetParam();
	SYSTEMTIME GetLMTime();
	int GetIntegerities();
public:
	enum DataType
	{
		DT_NONE = 0,
		DT_INTEGER = 1,// Integer: 4byte  corresponding: int
		DT_BOOL = 2,// Boolean: 1byte, corresponding£ºbool
		DT_DOUBLE = 3,// Floating-point number: 2byte,  corresponding: double
		DT_VARCHAR = 4,// String: 256byte, corresponding: char[256]
		DT_DATETIME = 5// Data time: 16byte, corresponding: SYSTEMTIME type
	};
};
typedef CTypedPtrArray<CPtrArray, CFieldEntity*> FIELDARRAY;