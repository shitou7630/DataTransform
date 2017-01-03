// RawDataView.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransform.h"
#include "RawDataView.h"



// CRawDataView

IMPLEMENT_DYNCREATE(CRawDataView, CFormView)

CRawDataView::CRawDataView()
	: CFormView(CRawDataView::IDD)
{
//	m_LeftListctrl = new CColorListCtrl;	
}

CRawDataView::~CRawDataView()
{
	delete m_LeftListctrl;
}

void CRawDataView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRawDataView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRawDataView diagnostics

#ifdef _DEBUG
void CRawDataView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRawDataView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRawDataView message handlers


int CRawDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect rectLeft;
	GetClientRect(&rectLeft);
	m_LeftListctrl.Create(LVS_REPORT | LVS_SHOWSELALWAYS, rectLeft, this, WM_USER+100 );

	m_LeftListctrl.ModifyStyle(0,LVS_REPORT);
//	m_LeftListctrl.ModifyStyle(0,LVS_SHOWSELALWAYS);
	m_LeftListctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	m_LeftListctrl.InsertColumn(0,_T("列0"),LVCFMT_CENTER,30,0);
	m_LeftListctrl.InsertColumn(1,_T("列1"),LVCFMT_CENTER,50,1);
	m_LeftListctrl.InsertColumn(2,_T("列2"),LVCFMT_CENTER,50,2);
	m_LeftListctrl.InsertColumn(3,_T("列3"),LVCFMT_CENTER,50,3);
	m_LeftListctrl.InsertColumn(4,_T("列4"),LVCFMT_CENTER,50,4);
	m_LeftListctrl.InsertColumn(5,_T("列5"),LVCFMT_CENTER,50,5);
	m_LeftListctrl.InsertColumn(6,_T("列6"),LVCFMT_CENTER,50,6);
	m_LeftListctrl.ShowScrollBar(SB_VERT,FALSE);
	m_LeftListctrl.ShowScrollBar(SB_HORZ,FALSE);
	m_LeftListctrl.SetAltRowColors(true,RGB(212,212,212),RGB(185,255,255));
	m_LeftListctrl.ShowWindow(SW_SHOW);
	
	return 0;
}


void CRawDataView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (IsWindowVisible())
	{
		CRect rc;
		GetClientRect(&rc);// 获取当前客户区view大小
		CSize size;
		size.cx = rc.right - rc.left;
		size.cy = rc.bottom - rc.top;
		SetScrollSizes(MM_HIMETRIC, size); // 将CScrollView的大小设置为当前客户区大小
		
		m_LeftListctrl.MoveWindow(0, 0, rc.Width(), rc.Height());
	}
}


void CRawDataView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
//	m_LeftListctrl->InsertItem(1,_T(""));	
}



