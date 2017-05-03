
#pragma once
#include "Data Structure.h"

class CDBEntity {
private :
	CString		strName;
	CString		strFilePath;
	bool		bType;
	SYSTEMTIME	tCtTime;
public :
	CDBEntity(Database &db);
	CDBEntity(CString strName);
	CDBEntity();
	~CDBEntity();
public:
	void SetName(CString name);
	void SetType(bool type);
	void SetPath(CString path);
	void SetCrtTime(SYSTEMTIME time);

	CString GetName();
	bool GetType();
	CString GetPath();
	SYSTEMTIME GetCrtTime();

	Database GetBlock();
	void SetBlock(Database db);
};