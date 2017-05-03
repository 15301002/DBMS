#include "stdafx.h"
#include "RecordEntity.h"

CRecordEntity::CRecordEntity() {

}

CRecordEntity::CRecordEntity(CRecordEntity &e) {

}

CRecordEntity::~CRecordEntity(){}

void CRecordEntity::PutVARCHAR(CString strKey, VARCHAR value) {
}

void CRecordEntity::PutINT(CString strKey, INTEGER value) {
}

void CRecordEntity::PutDOUBLE(CString strKey, DOUBLE value) {
}

void CRecordEntity::PutDATETIME(CString strKey, DATETIME value) {
}

CString CRecordEntity::Get(CString strKey) {
	return CString();
}
