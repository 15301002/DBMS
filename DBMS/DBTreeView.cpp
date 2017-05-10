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

	CDBMSDoc* pDoc = (CDBMSDoc*)this->GetDocument();

	CString strError = pDoc->GetError();

	if (strError.GetLength() != 0)
	{
		AfxMessageBox(strError);

		pDoc->SetError(_T(""));
		return;
	}

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
		CString strDBName = pDoc->GetDBAt(i)->GetName();

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
		case UPDATE_OPEN_DATABASE: {
			pTreeCtrl->DeleteAllItems();
			CDBMSDoc* pDoc = (CDBMSDoc*)this->GetDocument();
			int k = pDoc->GetDBNum();
			for (int i = 0; i < k; i++) {

				CDBEntity *db = pDoc->GetDBAt(i);
				CString strDBName = db->GetName();

				pDoc->SetDBEntity(*db);
				pDoc->LoadTables();

				HTREEITEM hRoot = pTreeCtrl->InsertItem(strDBName, 0, 0, NULL);

				int l = pDoc->GetTableNum();
				for (int j = 0; j < l; j++){
					CTableEntity* pTableEntity = pDoc->GetTBAt(j);
					AddTableNode(hRoot, pTableEntity);
				}

				pTreeCtrl->SetItemData(hRoot, MENU_DATABASE);
				pTreeCtrl->Expand(hRoot, TVE_EXPAND);
			}
			pTreeCtrl->SelectItem(pTreeCtrl->GetRootItem());
			break;
		}
		case UPDATE_RENAME_TABLE: {
			CDBMSDoc* pDoc = (CDBMSDoc*)this->GetDocument();

			pDoc->UpdateAllViews(NULL, UPDATE_OPEN_DATABASE, NULL);
			break;
		}
		case UPDATE_CREATE_TABLE: {
			CTableEntity* pTable = (CTableEntity*)pHint;
			
			HTREEITEM hSelectItem = pTreeCtrl->GetSelectedItem();
			HTREEITEM hParentItem = pTreeCtrl->GetParentItem(hSelectItem);
			HTREEITEM hTableNode;
			if (hParentItem == NULL)
				hTableNode = AddTableNode(hSelectItem, pTable);
			else 
				hTableNode = AddTableNode(hParentItem, pTable);
			pTreeCtrl->SelectItem(hTableNode);
			break;
		}
		case UPDATE_ADD_FIELD: {
			CFieldEntity* pField = (CFieldEntity*)pHint;
			CDBMSDoc* pDoc = (CDBMSDoc*)this->GetDocument();
			CTableEntity* pTable = pDoc->GetSelectedTB();
			HTREEITEM hSelectedItem = pTreeCtrl->GetSelectedItem();
			HTREEITEM hParentItem = pTreeCtrl->GetParentItem(hSelectedItem);
			HTREEITEM hChildItem = pTreeCtrl->GetChildItem(hSelectedItem);
			HTREEITEM hTBItem = NULL;
			if (pTreeCtrl->GetItemText(hParentItem).CompareNoCase(_T("Column")) == 0) {
				hTBItem = pTreeCtrl->GetParentItem(hParentItem);
			}
			else if (pTreeCtrl->GetItemText(hChildItem).CompareNoCase(_T("Column")) == 0) {
				hTBItem = hSelectedItem;
			}
			if (hTBItem != NULL) {
				HTREEITEM hFieldItem = AddFieldNode(pField, hTBItem);
				pTreeCtrl->SelectItem(hFieldItem);
			}
			break;
		}
		}

	}
}

HTREEITEM CDBTreeView::AddTableNode(HTREEITEM hRootNode, CTableEntity* pTable){
	if (hRootNode != NULL){

		HTREEITEM hTableNode = pTreeCtrl->InsertItem(pTable->GetName(), 1, 1, hRootNode);

		if (hTableNode != NULL){
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

HTREEITEM CDBTreeView::AddFieldNode(CFieldEntity* pField, HTREEITEM hTableItem){
	// Get the child item of the table item
	HTREEITEM hItem = pTreeCtrl->GetChildItem(hTableItem);

	if (hItem != NULL){
		// Traverse the child items of the table item
		do{
			// Get column item
			if (pTreeCtrl->GetItemText(hItem).CompareNoCase(_T("Column")) == 0){
				break;
			}
		} while ((hItem = pTreeCtrl->GetNextSiblingItem(hItem)) != NULL);
	}

	HTREEITEM hFieldNode = pTreeCtrl->InsertItem(pField->GetName(), 1, 1, hItem);       // Field

																						  // Add a number to the field item
	pTreeCtrl->SetItemData(hFieldNode, MENU_FIELD);

	return hFieldNode;
}

HTREEITEM CDBTreeView::GetTableItem(CString strDBName, CString strTableName)
{
	// Get root item
	HTREEITEM hDBNode = pTreeCtrl->GetRootItem();

	// Get table item
	HTREEITEM hTableNode = pTreeCtrl->GetChildItem(hDBNode);

	CDBMSDoc* pDoc = (CDBMSDoc*)this->GetDocument();

	int count = pDoc->GetDBNum();
	int nCount = pDoc->GetTableNum();

	for (int i = 0; i < count; i++) {
		hDBNode = pTreeCtrl->GetNextItem(hDBNode, TVGN_NEXT);

		if (pTreeCtrl->GetItemText(hDBNode).CompareNoCase(strDBName) == 0) {
			CDBEntity *db = pDoc->GetDBAt(i);
			pDoc->SetDBEntity(*db);
		}

		for (int i = 0; i < nCount; i++) {
			hTableNode = pTreeCtrl->GetNextItem(hTableNode, TVGN_NEXT);
			if (pTreeCtrl->GetItemText(hTableNode).CompareNoCase(strTableName) == 0)
				pDoc->SetSelectedTB(pDoc->GetTBAt(i));
		}

	}
	pDoc->LoadTables();
	return NULL;
}

void CDBTreeView::OnTvnSelchanged (NMHDR *pNMHDR, LRESULT *pResult){
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	CDBMSDoc* pDoc = (CDBMSDoc*)this->GetDocument();

	HTREEITEM hSelectedItem = pTreeCtrl->GetSelectedItem();
	
	if (hSelectedItem != NULL) {
		DWORD dwVal = pTreeCtrl->GetItemData(hSelectedItem);
		if (dwVal == MENU_DATABASE) {
			HTREEITEM hFindItem = hSelectedItem;
			int nIndex = 0;
			while ((hFindItem = pTreeCtrl->GetNextItem(hFindItem, TVGN_PREVIOUS)) != NULL) {
				nIndex++;
			}			
			pDoc->SetDBEntity(* (pDoc->GetDBAt(nIndex)));
			pDoc->LoadTables();
		}
		else if (dwVal == MENU_TABLE) {
			HTREEITEM hFindItem = hSelectedItem;
			HTREEITEM hParentItem = pTreeCtrl->GetParentItem(hFindItem);
			int i = 0;
			while ((hFindItem = pTreeCtrl->GetNextItem(hFindItem, TVGN_PREVIOUS)) != NULL) {
				i++;
			}
			int j = 0;
			while ((hParentItem = pTreeCtrl->GetNextItem(hParentItem, TVGN_PREVIOUS)) != NULL) {
				j++;
			}
			pDoc->SetDBEntity(*(pDoc->GetDBAt(j)));
			pDoc->LoadTables();
			pDoc->SetSelectedTB(pDoc->GetTBAt(i));
		}
		else if (dwVal == MENU_FIELD) {
			HTREEITEM hColumnItem = pTreeCtrl->GetParentItem(hSelectedItem);
			if (pTreeCtrl->GetItemText(hColumnItem).CompareNoCase(_T("Column")) == 0) {
				HTREEITEM hTBItem = pTreeCtrl->GetParentItem(hColumnItem);
				HTREEITEM hDBItem = pTreeCtrl->GetParentItem(hTBItem);
				int i = 0;
				while ((hTBItem = pTreeCtrl->GetNextItem(hTBItem, TVGN_PREVIOUS)) != NULL) {
					i++;
				}
				int j = 0;
				while ((hDBItem = pTreeCtrl->GetNextItem(hDBItem, TVGN_PREVIOUS)) != NULL) {
					j++;
				}
				pDoc->SetDBEntity(*(pDoc->GetDBAt(j)));
				pDoc->LoadTables();
				pDoc->SetSelectedTB(pDoc->GetTBAt(i));
			}
		}
	}
	*pResult = 0;
}

void CDBTreeView::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult){
	CPoint point;
	GetCursorPos(&point);

	pTreeCtrl->ScreenToClient(&point);

	UINT nFlag = TVHT_ONITEM;
	HTREEITEM hSelectedItem = pTreeCtrl->HitTest(point, &nFlag);
	CString temp = pTreeCtrl->GetItemText(hSelectedItem);

	if (NULL != hSelectedItem){
		DWORD dwVal = pTreeCtrl->GetItemData(hSelectedItem);
		if (dwVal != MENU_RCLICK){
			pTreeCtrl->ClientToScreen(&point);

			CMenu* pMenu = this->GetParentFrame()->GetMenu()->GetSubMenu(dwVal);

			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
		}

	}
	*pResult = 0;
}