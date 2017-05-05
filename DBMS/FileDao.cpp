#include "stdafx.h"
#include "FileDao.h"

CFileDao::CFileDao(){

}


CFileDao::~CFileDao(){}

CString CFileDao::GetDBFile(){
	return CString();
}


CString CFileDao::GetDBFolder(){
	return CString();
}


CString CFileDao::GetInfoFile(){
	return CString();
}


bool CFileDao::ProduceDBFile(CDBEntity & e){
	return false;
}
