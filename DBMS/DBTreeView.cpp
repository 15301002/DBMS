#include "stdafx.h"
#include "DBTreeView.h"
#include "DBMSDoc.h"
#include "Global.h"

IMPLEMENT_DYNCREATE(CDBTreeView, CTreeView)
CDBTreeView::CDBTreeView()
{
}

CDBTreeView::~CDBTreeView(){}

BEGIN_MESSAGE_MAP(CDBTreeView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDBTreeView::OnTvnSelchanged)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CDBTreeView::OnNMRClick)
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

	pDoc->LoadDatabase();
	int count = pDoc->GetDBNum();
	for (int i = 0; i < count; i++) {
		//	Get the database name
		CString strDBName = pDoc->GetDBAt(i)->GetName();

		//	Add root item
		HTREEITEM hRoot = pTreeCtrl->InsertItem(strDBName, 0, 0, NULL);

		pTreeCtrl->SetItemData(hRoot, MENU_DATABASE);
		pTreeCtrl->Expand(hRoot, TVE_EXPAND);

	}

}


void CDBTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pSender == NULL)
	{
		switch (lHint)
		{
		case UPDATE_CREATE_DATABASE: {
			//	Get the database name
			CString strDBName = ((CDBEntity*)pHint)->GetName();

			//	Add root item
			HTREEITEM hRoot = pTreeCtrl->InsertItem(strDBName, 0, 0, NULL);
			pTreeCtrl->SetItemData(hRoot, MENU_DATABASE);

			pTreeCtrl->SelectItem(hRoot);
			break;
		}
		case UPDATE_DROP_DATABASE: {

			break;
		}
		case UPDATE_USE_DATABASE: {
			pTreeCtrl->DeleteAllItems();
			CDBMSDoc* pDoc = (CDBMSDoc*)this->GetDocument();
			int count = pDoc->GetDBNum();
			for (int i = 0; i < count; i++) {
				//	Get the database name
				CString strDBName = pDoc->GetDBAt(i)->GetName();

				//	Add root item
				HTREEITEM hRoot = pTreeCtrl->InsertItem(strDBName, 0, 0, NULL);

				pTreeCtrl->SetItemData(hRoot, MENU_DATABASE);
				pTreeCtrl->Expand(hRoot, TVE_EXPAND);

			}
			int nCount = pDoc->GetTableNum();
			for (int i = 0; i < nCount; i++)
			{
				CTableEntity* pTableEntity = pDoc->GetTBAt(i);
				AddTableNode(pTableEntity);
				pTreeCtrl->SelectItem(pTreeCtrl->GetRootItem());
			}
			break;
		}
		}

	}
}

HTREEITEM CDBTreeView::AddTableNode(CTableEntity* pTable)
{
	// Get root item
	HTREEITEM hRootNode = pTreeCtrl->GetRootItem();
	if (hRootNode != NULL)
	{
		// Add child item
		HTREEITEM hTableNode = pTreeCtrl->InsertItem(pTable->GetName(), 1, 1, hRootNode);

		if (hTableNode != NULL)
		{
			// Add number to the table item
			pTreeCtrl->SetItemData(hTableNode, MENU_TABLE);

			// Add leaf item
			HTREEITEM hColNode = pTreeCtrl->InsertItem(_T("Column"), 2, 2, hTableNode);       // Column

																								// Add number to the column item
			pTreeCtrl->SetItemData(hColNode, MENU_RCLICK);

			// Show field	
			int nFieldNum = pTable->GetFieldNum();
			for (int i = 0; i < nFieldNum; i++)
			{
				CFieldEntity* pField = pTable->GetFieldAt(i);
				AddFieldNode(pField, hTableNode);
			}

			// Expand table item
			pTreeCtrl->Expand(hTableNode, TVE_EXPAND);
			// Expand database item
			pTreeCtrl->Expand(hRootNode, TVE_EXPAND);

			return hTableNode;
		}
	}
	return NULL;
}

HTREEITEM CDBTreeView::AddFieldNode(CFieldEntity* pField, HTREEITEM hTableItem)
{
	// Get the child item of the table item
	HTREEITEM hItem = pTreeCtrl->GetChildItem(hTableItem);

	if (hItem != NULL)
	{
		// Traverse the child items of the table item
		do
		{
			// Get column item
			if (pTreeCtrl->GetItemText(hItem).CompareNoCase(_T("Column")) == 0)
			{
				break;
			}
		} while ((hItem = pTreeCtrl->GetNextSiblingItem(hItem)) != NULL);
	}

	HTREEITEM hFieldNode = pTreeCtrl->InsertItem(pField->GetName(), 1, 1, hItem);       // Field

																						  // Add a number to the field item
	pTreeCtrl->SetItemData(hFieldNode, MENU_FIELD);

	return hFieldNode;
}

void CDBTreeView::OnTvnSelchanged (NMHDR *pNMHDR, LRESULT *pResult){
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// Get the object of the document
	CDBMSDoc* pDoc = (CDBMSDoc*)this->GetDocument();

	// Get the selected item
	HTREEITEM hSelectedItem = pTreeCtrl->GetSelectedItem();

	if (hSelectedItem != NULL) {
	}
	*pResult = 0;
}

void CDBTreeView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// Get the clicked position
	CPoint point;
	GetCursorPos(&point);
	// Convert the location of the cursor to client coordinates
	pTreeCtrl->ScreenToClient(&point);
	// Decide whether the clicked location is on the tree control
	UINT nFlag = TVHT_ONITEM;
	HTREEITEM hSelectedItem = pTreeCtrl->HitTest(point, &nFlag);


	if (NULL != hSelectedItem)	// Uncheck the new node, to return
	{
		DWORD dwVal = pTreeCtrl->GetItemData(hSelectedItem);
		if (dwVal != MENU_RCLICK)
		{
			// Convert the selected coordinates into the coordinates relative to screen
			pTreeCtrl->ClientToScreen(&point);
			// Load the menu resource
			CMenu* pMenu = this->GetParentFrame()->GetMenu()->GetSubMenu(dwVal);
			// Show the menu on the clicked position
			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
		}

	}

	*pResult = 0;
}