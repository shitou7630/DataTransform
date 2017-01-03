#pragma once

#include "ColorListCtrl.h"

// CRawDataView form view

class CRawDataView : public CFormView
{
	DECLARE_DYNCREATE(CRawDataView)

protected:
	CRawDataView();           // protected constructor used by dynamic creation
	virtual ~CRawDataView();

public:
	enum { IDD = IDD_RAWDATAVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	CColorListCtrl m_LeftListctrl;

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
};


