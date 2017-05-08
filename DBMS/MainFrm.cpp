
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "DBMS.h"
#include "DBTreeView.h"
#include "DBMSView.h"
#include "MainFrm.h"
#include "DBEntity.h"
#include "DBMSDoc.h"
#include "CREATEDatabaseDlg.h"
#include "CREATETableDlg.h"
#include "DBLogic.h"
#include "TableLogic.h"
#include "AppException.h"
#include "Global.h"
#include "RENAMETableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_DATABASE_CREATE, &CMainFrame::OnDatabaseCreate)
	ON_COMMAND(ID_DATABASES_DROP, &CMainFrame::OnDatabasesDrop)
	ON_COMMAND(ID_DATABASES_OPEN, &CMainFrame::OnDatabasesOpen)
	ON_COMMAND(ID_TABLE_CREATE, &CMainFrame::OnTableCreate)
	ON_COMMAND(ID_TABLE_ALTER, &CMainFrame::OnTableAlter)
END_MESSAGE_MAP()

static UINT indicators[] = {
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame(){
	openDatabase = FALSE;
}

CMainFrame::~CMainFrame(){}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)){
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this)){
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs){
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext){
	if (!m_wndSpliter.CreateStatic(this, 1, 2)){
		AfxMessageBox(_T("Failed to create split window��"));
		return FALSE;
	}

	if (!m_wndSpliter.CreateView(0, 0, RUNTIME_CLASS(CDBTreeView), CSize(200, 0), pContext)){
		return FALSE;
	}

	if (!m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CDBMSView), CSize(0, 0), pContext)){
		return FALSE;
	}
	return TRUE;
}
// CMainFrame ��Ϣ�������

void CMainFrame::OnDatabaseCreate(){
	CCREATEDatabaseDlg dlg;
	int res = dlg.DoModal();
	if (res == IDOK) {
		CDBEntity* e = new CDBEntity(dlg.GetDatabaseName());
		//	Get the object of document
		CDBMSDoc* pDoc = (CDBMSDoc*)this->GetActiveDocument();
		pDoc->SetDBEntity(*e);
		pDoc->CreateDatabase();
		CString strTitle;
		strTitle.Format(_T("Database(%s)"), e->GetName());
		pDoc->SetTitle(strTitle);
		delete e;
		pDoc->UpdateAllViews(NULL, UPDATE_CREATE_DATABASE, & (pDoc->GetDBEntity()));
	}
}

void CMainFrame::OnDatabasesDrop(){
	CDBMSDoc* pDoc = (CDBMSDoc*)this->GetActiveDocument();
	int res = MessageBoxA(NULL, "Are you sure to DROP the selected database?", "DROP DATABASE", MB_OKCANCEL);
	if (res == MB_OK) {
		pDoc->UpdateAllViews(NULL, UPDATE_DROP_DATABASE, NULL);
	}
}


void CMainFrame::OnDatabasesOpen(){
	CDBMSDoc* pDoc = (CDBMSDoc*)this->GetActiveDocument();

	CString strError = pDoc->GetError();
	if (strError.GetLength() > 0)
	{
		AfxMessageBox(strError);
		pDoc->SetError(_T(""));
	}

	openDatabase = TRUE;

	pDoc->UpdateAllViews(NULL, UPDATE_OPEN_DATABASE, NULL);
	
}


void CMainFrame::OnTableCreate(){
	if (openDatabase == TRUE) {
		CCREATETableDlg dlg;
		int res = dlg.DoModal();
		if (res == IDOK) {
			CDBMSDoc* pDoc = (CDBMSDoc*)this->GetActiveDocument();

			int nCount = pDoc->GetTableNum();
			for (int i = 0; i < nCount; i++){
				CString strName = pDoc->GetTBAt(i)->GetName();
				if (dlg.GetTableName() == strName){
					AfxMessageBox(_T("The table has been existed��"));
					return;
				}
			}

			CTableEntity* pTable = pDoc->CreateTable(dlg.GetTableName());

			CString strError = pDoc->GetError();

			if (strError.GetLength() != 0){
				AfxMessageBox(strError);
				pDoc->SetError(_T(""));
				return;
			}
			if (pTable != NULL){
				//SwitchView(TABLE);
				pDoc->UpdateAllViews(NULL, UPDATE_CREATE_TABLE, pTable);
			}
		}
	} else {
		AfxMessageBox(_T("You should open the databases first!"));
	}
}

CTableEntity* CDBMSDoc::CreateTable(CString strName){
	CTableEntity* pTable = new CTableEntity();
	pTable->SetName(strName);
	CTableLogic tbLogic;
	try{
		// Decide whether creates table successfully
		if (tbLogic.CreateTable(dbEntity.GetName(), *pTable) == true){
			// If creates table successfully, the created table information would be saved to the array.
			arrTB.Add(pTable);
		} else {
			// If creates failure, release the memory allocated by new
			delete pTable;
			pTable = NULL;
		}
	}
	catch (CAppException* e){	// Catch exception
		// If there is exception, release the memory allocated by new
		if (pTable != NULL){
			delete pTable;
			pTable = NULL;
		}
		// Get exception information
		strError = e->GetErrorMessage();
		// Delete exception
		delete e;
	}
	return pTable;
}

void CMainFrame::OnTableAlter()
{
	// TODO: �ڴ���������������
	CRENAMETableDlg dlg;
	int res = dlg.DoModal();
	if (res == IDOK) {
		CDBMSDoc* pDoc = (CDBMSDoc*)this->GetActiveDocument();

	}
}
