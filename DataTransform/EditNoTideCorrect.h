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
	CComboBox m_comboEast; //������
	CComboBox m_comboGPSmodel; //GPSģʽ
	CComboBox m_comboHighDepth; //��Ƶˮ��
	CComboBox m_comboIndexNum; //���
	CComboBox m_comboLowDepth; //��Ƶˮ��
	CComboBox m_comboNorth; //����������
	CComboBox m_comboTime; //ʱ��
	CComboBox m_comboEarthHight; //������
	CEdit m_editParaValue; //����
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedEditDatacorbutton();

private:
	int SelectDataToList(CString tempColumn, WORD uiColumnIndex); //�Զ��庯��
	int CorrectEarthHeight(DWORD rowCount, DWORD columnEarthHeight, DWORD gpsModel);
	int CorrectWaterDepth(DWORD rowCount, DWORD columnHighDepth, DWORD columnLowDepth);
};
