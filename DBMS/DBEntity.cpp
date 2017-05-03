#include "stdafx.h"
#include "DBEntity.h"

CDBEntity::CDBEntity(Database & db) {
}

CDBEntity::CDBEntity(CString strName) {
}

CDBEntity::CDBEntity() {

}

CDBEntity::~CDBEntity(){}

void CDBEntity::SetName(CString name) {
	strName = name;
}

CString CDBEntity::GetName() {
	return strName;
}

void CDBEntity::SetType(bool type) {
	bType = type;
}

bool CDBEntity::GetType() {
	return bType;
}

void CDBEntity::SetPath(CString path) {
	strFilePath = path;
}

CString CDBEntity::GetPath() {
	return strFilePath;
}

void CDBEntity::SetCrtTime(SYSTEMTIME time) {
	tCtTime = time;
}

SYSTEMTIME CDBEntity::GetCrtTime() {
	return tCtTime;
}
