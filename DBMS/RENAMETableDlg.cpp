// ALTERTableDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "RENAMETableDlg.h"
#include "afxdialogex.h"


// CALTERTableDlg �Ի���

IMPLEMENT_DYNAMIC(CRENAMETableDlg, CDialogEx)

CRENAMETableDlg::CRENAMETableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RENAME_TABLE, pParent)
	, newTableName(_T(""))
{

}

CRENAMETableDlg::~CRENAMETableDlg()
{
}

void CRENAMETableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEW_TABLE_NAME, newTableName);
}

CString CRENAMETableDlg::GetNewTableName(){
	return newTableName;
}


BEGIN_MESSAGE_MAP(CRENAMETableDlg, CDialogEx)
END_MESSAGE_MAP()


// CALTERTableDlg ��Ϣ�������
