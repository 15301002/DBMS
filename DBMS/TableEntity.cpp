#include "stdafx.h"
#include "TableEntity.h"

CTableEntity::CTableEntity(CString strName)
{
}

CTableEntity::CTableEntity()
{
}

CTableEntity::~CTableEntity(){}

CFieldEntity * CTableEntity::AddField(CFieldEntity & field)
{
	return nullptr;
}

CFieldEntity * CTableEntity::GetFieldAt(int index)
{
	return nullptr;
}

void CTableEntity::SetName(CString name) {
	strName = name;
}

void CTableEntity::SetTdPath(CString path) {
	strTdPath = path;
}

void CTableEntity::SetTrdPath(CString path) {
	strTrdPath = path;
}

void CTableEntity::SetTicPath(CString path) {
	strTicPath = path;
}

void CTableEntity::SetTidPath(CString path) {
	strTidPath = path;
}

void CTableEntity::SetCtTime(SYSTEMTIME time) {
	tCtTime = time;
}

void CTableEntity::SetLMTime(SYSTEMTIME time) {
	tLMTime = time;
}

CString CTableEntity::GetName() {
	return strName;
}

CString CTableEntity::GetTdPath() {
	return strTdPath;
}

CString CTableEntity::GetTrdPath() {
	return strTrdPath;
}

CString CTableEntity::GetTicPath() {
	return strTicPath;
}

CString CTableEntity::GetTidPath() {
	return strTidPath;
}

SYSTEMTIME CTableEntity::GetCtTime() {
	return tCtTime;
}

SYSTEMTIME CTableEntity::GETLMTime() {
	return tLMTime;
}
