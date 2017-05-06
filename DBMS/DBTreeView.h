#pragma once
#include <afxcview.h>

class CDBTreeView : public CTreeView {
	DECLARE_DYNCREATE(CDBTreeView);
private:
	CTreeCtrl* pTreeCtrl;
protected :
	CDBTreeView();
	virtual ~CDBTreeView();
public :
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

