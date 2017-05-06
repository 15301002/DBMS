#include "stdafx.h"
#include "DBTreeView.h"
#include "DBMSDoc.h"

IMPLEMENT_DYNCREATE(CDBTreeView, CTreeView)
CDBTreeView::CDBTreeView()
{
}

CDBTreeView::~CDBTreeView(){}

BEGIN_MESSAGE_MAP(CDBTreeView, CTreeView)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CDBTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDBTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif

void CDBTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//	Get the document object
	CDBMSDoc* pDoc = (CDBMSDoc*)this->GetDocument();

	//	Get the exceptionl information
	CString strError = pDoc->GetError();

	//	Decide whether there are exceptions
	if (strError.GetLength() != 0)
	{
		//	Prompt exception information
		AfxMessageBox(strError);

		//	Set the exception information to empty
		pDoc->SetError(_T(""));
		return;
	}


	//	Get tree control
	pTreeCtrl = &this->GetTreeCtrl();

	// Get the style of the tree control
	DWORD dwStyle = ::GetWindowLong(pTreeCtrl->m_hWnd, GWL_STYLE);

	// Set the style of the tree control
	dwStyle |= TVS_HASBUTTONS	// Expand or collapse the child items
		| TVS_HASLINES		// Draw lines linked child items to their corresponding parent item
		| TVS_LINESATROOT;	// Draw lines linked child items to the root item
	::SetWindowLong(pTreeCtrl->m_hWnd, GWL_STYLE, dwStyle);

	//	Get the database name
	CString strDBName = pDoc->GetDBEntity().GetName();

	//	Add root item
	HTREEITEM hRoot = pTreeCtrl->InsertItem(strDBName, 0, 0, NULL);

}
