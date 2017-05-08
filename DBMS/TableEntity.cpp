#include "stdafx.h"
#include "TableEntity.h"
#include "CharUtil.h"

CTableEntity::CTableEntity(CString strName){}

CTableEntity::CTableEntity(){}

CTableEntity::~CTableEntity(){}

Table CTableEntity::GetTable(){
	Table tb;
	CCharUtil::ToChars(tb.name, strName, sizeof(VARCHAR));
	tb.field_num = arrFields.GetCount();
	tb.record_num = nRecordNum;
	CCharUtil::ToChars(tb.tdf, strTdPath, sizeof(VARCHAR));
	CCharUtil::ToChars(tb.trd, strTrdPath, sizeof(VARCHAR));
	tb.crtime = tCtTime;
	tb.lmtime = tLMTime;

	return tb;
}

void CTableEntity::SetTable(Table tb)
{
	strName = CCharUtil::ToString(tb.name, sizeof(VARCHAR));
	nRecordNum = tb.record_num;
	strTdPath = CCharUtil::ToString(tb.tdf, sizeof(VARCHAR));
	strTrdPath = CCharUtil::ToString(tb.trd, sizeof(VARCHAR));
	tCtTime = tb.crtime;
	tLMTime = tb.lmtime;
}

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

int CTableEntity::GetFieldNum()
{
	return arrFields.GetCount();
}
