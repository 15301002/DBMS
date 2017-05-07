
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "DBMS.h"
#include "DBTreeView.h"
#include "DBMSView.h"
#include "MainFrm.h"
#include "DBEntity.h"
#include "DBMSDoc.h"
#include "CREATEDatabaseDlg.h"
#include "DBLogic.h"
#include "AppException.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_DATABASE_CREATE, &CMainFrame::OnDatabaseCreate)
	ON_COMMAND(ID_DATABASES_DROP, &CMainFrame::OnDatabasesDrop)
	ON_COMMAND(ID_DATABASES_USE, &CMainFrame::OnDatabasesUse)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// Create a static split window, the view can be divided into two columns
	if (!m_wndSpliter.CreateStatic(this, 1, 2))
	{
		AfxMessageBox(_T("Failed to create split window！"));
		return FALSE;
	}

	// Add view for the separated window.
	if (!m_wndSpliter.CreateView(0, 0, RUNTIME_CLASS(CDBTreeView), CSize(200, 0), pContext))
	{
		return FALSE;
	}

	if (!m_wndSpliter.CreateView(0, 1, RUNTIME_CLASS(CDBMSView), CSize(0, 0), pContext))
	{
		return FALSE;
	}


	return TRUE;

}
// CMainFrame 消息处理程序



void CMainFrame::OnDatabaseCreate()
{
	// TODO: 在此添加命令处理程序代码
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




void CMainFrame::OnDatabasesDrop()
{
	// TODO: 在此添加命令处理程序代码
	CDBMSDoc* pDoc = (CDBMSDoc*)this->GetActiveDocument();
	int res = MessageBoxA(NULL, "Are you sure to DROP the selected database?", "DROP DATABASE", MB_OKCANCEL);
	if (res == MB_OK) {
		pDoc->UpdateAllViews(NULL, UPDATE_DROP_DATABASE, NULL);
	}
}


void CMainFrame::OnDatabasesUse()
{
	// TODO: 在此添加命令处理程序代码
	// Get the pointer to the document
	CDBMSDoc* pDoc = (CDBMSDoc*)this->GetActiveDocument();

	// Read table
	pDoc->LoadTables();

	// Decide whether has exception
	CString strError = pDoc->GetError();
	if (strError.GetLength() > 0)
	{
		AfxMessageBox(strError);
		pDoc->SetError(_T(""));
	}

	// The database has been opened
	useDatabase = TRUE;

	// Update view
	pDoc->UpdateAllViews(NULL, UPDATE_USE_DATABASE, NULL);
	
}
