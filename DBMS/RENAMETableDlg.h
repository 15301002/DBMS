#pragma once


// CREANAMETableDlg �Ի���

class CRENAMETableDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRENAMETableDlg)

public:
	CRENAMETableDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRENAMETableDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALTER_TABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString newTableName;
public:
	CString GetNewTableName();
};
