
// DataTransformDoc.h : CDataTransformDoc ��Ľӿ�
//
#include <vector>
using namespace std;

#pragma once


class CDataTransformDoc : public CDocument
{
protected: // �������л�����
	CDataTransformDoc();
	DECLARE_DYNCREATE(CDataTransformDoc)

// ����
public:
	vector< vector<CString> >  m_vectorRawData;//���������ļ��Ĵ洢
	vector< vector<CString> >  m_vectorNoTideCorrect;//���������ļ��Ĵ洢

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
	virtual ~CDataTransformDoc();
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
public:
	afx_msg void OnFileOpen();
	afx_msg void OnEditNotidecorrect();
	afx_msg void OnSaveCassformat();
	afx_msg void OnExtracttide();

public:
	CString m_strTide[1440];//��λ�ļ�����
	afx_msg void OnSavetidefile();
};
