#pragma once


// CExtractTide dialog

class CExtractTide : public CDialogEx
{
	DECLARE_DYNAMIC(CExtractTide)

public:
	CExtractTide(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExtractTide();

// Dialog Data
	enum { IDD = IDD_EDIT_EXTRACTTIDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboEarthHeight;
	CComboBox m_comboGpsModel;
	CComboBox m_comboInterMethod;
	CEdit m_textParaValue;
	CComboBox m_comboTime;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedEditExtractitdeEtbutton();
	

private:
	int SelectDataToList(CString tempColumn, WORD uiColumnIndex);
	int CorrectEarthHeight(DWORD rowCount, DWORD columnEarthHeight, DWORD gpsModel);
	int ExtractTideToArry(DWORD columnTime,DWORD columnEarthHeight);

};
