// TransDataView.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransform.h"
#include "TransDataView.h"



// CTransDataView

IMPLEMENT_DYNCREATE(CTransDataView, CFormView)

CTransDataView::CTransDataView()
	: CFormView(CTransDataView::IDD)
{
	/*m_RightListctrl = new CColorListCtrl;*/
}

CTransDataView::~CTransDataView()
{
	delete m_RightListctrl;
}

void CTransDataView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTransDataView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTransDataView diagnostics

#ifdef _DEBUG
void CTransDataView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTransDataView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTransDataView message handlers


int CTransDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect rectRight;
	GetClientRect(&rectRight);
	m_RightListctrl = new CColorListCtrl;
	m_RightListctrl->Create(LVS_REPORT | LVS_SHOWSELALWAYS, rectRight, this, WM_USER+200 );
	
	m_RightListctrl->ModifyStyle(0,LVS_REPORT);
	//	m_LeftListctrl.ModifyStyle(0,LVS_SHOWSELALWAYS);
	m_RightListctrl->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	m_RightListctrl->InsertColumn(0,_T("列0"),LVCFMT_CENTER,30,0);
	m_RightListctrl->InsertColumn(1,_T("列1"),LVCFMT_CENTER,50,1);
	m_RightListctrl->InsertColumn(2,_T("列2"),LVCFMT_CENTER,50,2);
	m_RightListctrl->InsertColumn(3,_T("列3"),LVCFMT_CENTER,50,3);
	m_RightListctrl->InsertColumn(4,_T("列4"),LVCFMT_CENTER,50,4);
	m_RightListctrl->InsertColumn(5,_T("列5"),LVCFMT_CENTER,50,5);
	m_RightListctrl->InsertColumn(6,_T("列6"),LVCFMT_CENTER,50,6);
//	m_RightListctrl->SetAltRowColors(true,RGB(0,255,255),RGB(153,153,102));

	m_RightListctrl->ShowWindow(SW_SHOW);
	
	return 0;
}


void CTransDataView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (IsWindowVisible())
	{
		CRect rc;
		GetClientRect(&rc);
		CSize size;
		size.cx = rc.right - rc.left;
		size.cy = rc.bottom - rc.top;
		SetScrollSizes(MM_HIMETRIC, size); // 将CScrollView的大小设置为当前客户区大小

		m_RightListctrl->MoveWindow(0, 0, rc.Width(), rc.Height());
	}
}
