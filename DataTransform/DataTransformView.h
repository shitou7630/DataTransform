
// DataTransformView.h : CDataTransformView 类的接口
//

#pragma once

#include "resource.h"


class CDataTransformView : public CFormView
{
protected: // 仅从序列化创建
	CDataTransformView();
	DECLARE_DYNCREATE(CDataTransformView)

public:
	enum{ IDD = IDD_DATATRANSFORM_FORM };

// 特性
public:
	CDataTransformDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CDataTransformView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // DataTransformView.cpp 中的调试版本
inline CDataTransformDoc* CDataTransformView::GetDocument() const
   { return reinterpret_cast<CDataTransformDoc*>(m_pDocument); }
#endif

