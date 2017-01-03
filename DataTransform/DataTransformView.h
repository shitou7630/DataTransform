
// DataTransformView.h : CDataTransformView ��Ľӿ�
//

#pragma once

#include "resource.h"


class CDataTransformView : public CFormView
{
protected: // �������л�����
	CDataTransformView();
	DECLARE_DYNCREATE(CDataTransformView)

public:
	enum{ IDD = IDD_DATATRANSFORM_FORM };

// ����
public:
	CDataTransformDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CDataTransformView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // DataTransformView.cpp �еĵ��԰汾
inline CDataTransformDoc* CDataTransformView::GetDocument() const
   { return reinterpret_cast<CDataTransformDoc*>(m_pDocument); }
#endif

