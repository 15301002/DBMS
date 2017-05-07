#include "stdafx.h"
#include "FieldEntity.h"

CFieldEntity::CFieldEntity()
{
}

CFieldEntity::CFieldEntity(CFieldEntity &)
{
}

CFieldEntity::CFieldEntity(CString, int, int, int)
{
}

CFieldEntity::~CFieldEntity(){}

void CFieldEntity::SetField(Field fd)
{
	strName = CCharUtil::ToString(fd.name, sizeof(VARCHAR));
	tLMTime = fd.lmtime;
	nType = fd.type;
	nParam = fd.param;
	nIntegrities = fd.integrities;
}

Field CFieldEntity::GetField()
{
	Field fd;
	memset(&fd, 0, sizeof(Field));

	CCharUtil::ToChars(fd.name, strName, sizeof(VARCHAR));
	fd.lmtime = tLMTime;
	fd.type = nType;
	fd.param = nParam;
	fd.integrities = nIntegrities;
	return fd;
}

void CFieldEntity::SetName(CString name) {
	strName = name;
}

void CFieldEntity::SetType(int type){
	nType = type;
}

void CFieldEntity::SetParam(int param){
	nParam = param;
}

void CFieldEntity::SetLMTime(SYSTEMTIME time){
	tLMTime = time;
}

CString CFieldEntity::GetName() {
	return strName;
}

int CFieldEntity::GetType() {
	return nType;
}

int CFieldEntity::GetParam() {
	return nParam;
}

SYSTEMTIME CFieldEntity::GetLMTime() {
	return tLMTime;
}
