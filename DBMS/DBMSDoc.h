
// DBMSDoc.h : CDBMSDoc ��Ľӿ�
//


#pragma once
#include "DBEntity.h"

class CDBMSDoc : public CDocument
{
protected: // �������л�����
	CDBMSDoc();
	DECLARE_DYNCREATE(CDBMSDoc)

private:
	CDBEntity dbEntity;
	CString strError;
// ����
public:
	CString GetError();
	void SetError(CString error);
	CDBEntity GetDBEntity();
	void SetDBEntity(CDBEntity e);

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CDBMSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
