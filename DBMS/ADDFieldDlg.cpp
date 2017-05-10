// ADDFieldDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DBMS.h"
#include "ADDFieldDlg.h"
#include "afxdialogex.h"


// CADDFieldDlg �Ի���

IMPLEMENT_DYNAMIC(CADDFieldDlg, CDialogEx)

CADDFieldDlg::CADDFieldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADD_FIELD, pParent)
	, fieldName(_T(""))
	, defaultVal(_T(""))
	, isNotNull(false)
	, isPrimaryKey(false)
{

}

CADDFieldDlg::~CADDFieldDlg()
{
}

void CADDFieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FIELD_NAME, fieldName);
	DDX_Text(pDX, IDC_DEFAULT, defaultVal);
}

CString CADDFieldDlg::GetFieldName()
{
	return fieldName;
}

CString CADDFieldDlg::GetDefaultVal()
{
	return defaultVal;
}

bool CADDFieldDlg::IsNotNull()
{
	return isNotNull;
}

bool CADDFieldDlg::IsPrimaryKey()
{
	return isPrimaryKey;
}


BEGIN_MESSAGE_MAP(CADDFieldDlg, CDialogEx)
	ON_BN_CLICKED(IDC_NOT_NULL, &CADDFieldDlg::OnBnClickedNotNull)
	ON_BN_CLICKED(IDC_PRIMARY_KEY, &CADDFieldDlg::OnBnClickedPrimaryKey)
	ON_BN_CLICKED(IDOK, &CADDFieldDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CADDFieldDlg ��Ϣ�������


void CADDFieldDlg::OnBnClickedNotNull()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	isNotNull = ((CButton*)GetDlgItem(IDC_NOT_NULL))->GetCheck();
}


void CADDFieldDlg::OnBnClickedPrimaryKey()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	isPrimaryKey = ((CButton*)GetDlgItem(IDC_PRIMARY_KEY))->GetCheck();
}


void CADDFieldDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemTextW(IDC_FIELD_NAME, fieldName);
	if (fieldName.IsEmpty()) {
		AfxMessageBox(_T("Field name can not be empty!"));

		return;
	}
	else {
	}
	CDialogEx::OnOK();
}
