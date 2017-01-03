
// DataTransformView.cpp : CDataTransformView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DataTransform.h"
#endif

#include "DataTransformDoc.h"
#include "DataTransformView.h"
#include "ColorListCtrl.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDataTransformView

IMPLEMENT_DYNCREATE(CDataTransformView, CFormView)

BEGIN_MESSAGE_MAP(CDataTransformView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CDataTransformView 构造/析构

CDataTransformView::CDataTransformView()
	: CFormView(CDataTransformView::IDD)
{
	// TODO: 在此处添加构造代码

}

CDataTransformView::~CDataTransformView()
{
}

void CDataTransformView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CDataTransformView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CDataTransformView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CDataTransformView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDataTransformView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDataTransformView 诊断

#ifdef _DEBUG
void CDataTransformView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDataTransformView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDataTransformDoc* CDataTransformView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDataTransformDoc)));
	return (CDataTransformDoc*)m_pDocument;
}
#endif //_DEBUG




void CDataTransformView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CFormView::OnPaint() for painting messages
//	Invalidate(TRUE);
}
