
// DBMSDoc.h : CDBMSDoc ��Ľӿ�
//


#pragma once
#include "DBEntity.h"
#include "TableEntity.h"

class CDBMSDoc : public CDocument
{
protected: // �������л�����
	CDBMSDoc();
	DECLARE_DYNCREATE(CDBMSDoc)

private:
	CDBEntity dbEntity;
	CTableEntity *selectedTB;
	CString strError;
	DBARR arrDB;
	TABLEARR arrTB;
// ����
public:
	CString GetError();
	void SetError(CString error);
	CDBEntity GetDBEntity();
	void SetDBEntity(CDBEntity e);
	CDBEntity * GetDBAt(int index);
	int GetDBNum();
	CTableEntity *GetTBAt(int index);
	int GetTableNum();
	void SetSelectedTB(CTableEntity *e);
	CTableEntity *GetSelectedTB();

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
	CDBEntity * CreateDatabase();
	void LoadDatabase();
	void LoadTables();
	void LoadFields();
	void RenameTable(CString newName);
	CFieldEntity * AddField(CFieldEntity & field);
	CTableEntity * CreateTable(CString strName);
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif 
	// SHARED_HANDLERS
};
