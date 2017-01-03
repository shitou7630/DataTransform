
// DataTransformView.cpp : CDataTransformView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CDataTransformView ����/����

CDataTransformView::CDataTransformView()
	: CFormView(CDataTransformView::IDD)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

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


// CDataTransformView ���

#ifdef _DEBUG
void CDataTransformView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDataTransformView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDataTransformDoc* CDataTransformView::GetDocument() const // �ǵ��԰汾��������
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
