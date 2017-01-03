#pragma once

#include "ColorListCtrl.h"
// CEditNoTideCorrect dialog

class CEditNoTideCorrect : public CDialogEx
{
	DECLARE_DYNAMIC(CEditNoTideCorrect)

public:
	CEditNoTideCorrect(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditNoTideCorrect();

// Dialog Data
	enum { IDD = IDD_EDIT_NOTIDECORRECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEditPardlgexit();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CComboBox m_comboEast; //东坐标
	CComboBox m_comboGPSmodel; //GPS模式
	CComboBox m_comboHighDepth; //高频水深
	CComboBox m_comboIndexNum; //序号
	CComboBox m_comboLowDepth; //低频水深
	CComboBox m_comboNorth; //北方向坐标
	CComboBox m_comboTime; //时间
	CComboBox m_comboEarthHight; //正常高
	CEdit m_editParaValue; //常数
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedEditDatacorbutton();

private:
	int SelectDataToList(CString tempColumn, WORD uiColumnIndex); //自定义函数
	int CorrectEarthHeight(DWORD rowCount, DWORD columnEarthHeight, DWORD gpsModel);
	int CorrectWaterDepth(DWORD rowCount, DWORD columnHighDepth, DWORD columnLowDepth);
};
