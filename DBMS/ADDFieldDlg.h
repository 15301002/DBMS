#pragma once

#include "FieldEntity.h"
// CADDFieldDlg 对话框

class CADDFieldDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CADDFieldDlg)

public:
	CADDFieldDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CADDFieldDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_FIELD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString fieldName;
	CString defaultVal;
	bool isNotNull;
	bool isPrimaryKey;

public:
	CString GetFieldName();
	CString GetDefaultVal();

	bool IsNotNull();
	bool IsPrimaryKey();

	
	afx_msg void OnBnClickedNotNull();
	afx_msg void OnBnClickedPrimaryKey();
	afx_msg void OnBnClickedOk();
};
