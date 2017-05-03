#pragma once
#include <afxcview.h>

class CDBTreeView : public CTreeView {
	DECLARE_DYNCREATE(CDBTreeView);
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
};

