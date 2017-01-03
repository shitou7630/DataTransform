#pragma once

#include "ColorListCtrl.h"

// CTransDataView form view

class CTransDataView : public CFormView
{
	DECLARE_DYNCREATE(CTransDataView)

protected:
	CTransDataView();           // protected constructor used by dynamic creation
	virtual ~CTransDataView();

public:
	enum { IDD = IDD_TRANSDATAVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	CColorListCtrl* m_RightListctrl;

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


