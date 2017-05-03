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
