
// DataTransformDoc.cpp : CDataTransformDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DataTransform.h"
#endif

#include "DataTransformDoc.h"
#include "ColorListCtrl.h"
#include "globalFunction.h"
#include "RawDataView.h"
#include "TransDataView.h"
#include "MainFrm.h"
#include "EditNoTideCorrect.h"
#include "ExtractTide.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDataTransformDoc

IMPLEMENT_DYNCREATE(CDataTransformDoc, CDocument)

BEGIN_MESSAGE_MAP(CDataTransformDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CDataTransformDoc::OnFileOpen)
	ON_COMMAND(IDM_EDIT_NOTIDECORRECT, &CDataTransformDoc::OnEditNotidecorrect)
	ON_COMMAND(IDM_SAVE_CASSFORMAT, &CDataTransformDoc::OnSaveCassformat)
	ON_COMMAND(IDM_EXTRACTTIDE, &CDataTransformDoc::OnExtracttide)
	ON_COMMAND(IDM_SAVETIDEFILE, &CDataTransformDoc::OnSavetidefile)
END_MESSAGE_MAP()


// CDataTransformDoc ����/����

CDataTransformDoc::CDataTransformDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CDataTransformDoc::~CDataTransformDoc()
{
}

BOOL CDataTransformDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDataTransformDoc ���л�

void CDataTransformDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CDataTransformDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CDataTransformDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CDataTransformDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDataTransformDoc ���

#ifdef _DEBUG
void CDataTransformDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDataTransformDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDataTransformDoc ����


void CDataTransformDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	CString strOpenFileType = _T("Text Files(*.txt)\0*.txt\0Dat Files(*.dat)\0*.dat\0Excel Files(*.xls | *.xlsx)\0*.xls;*.xlsx\0All Files(*.*)\0*.*\0\0");
	CFileDialog fileDlg(TRUE, _T("*.txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strOpenFileType);
	fileDlg.m_ofn.lpstrTitle = _T("��ȡ����");
	fileDlg.m_ofn.lpstrFilter = _T("Out Files(*.out)\0*.out\0Text Files(*.txt)\0*.txt\0Dat Files(*.dat)\0*.dat\0Excel Files(*.xls | *.xlsx)\0*.xls;*.xlsx\0All Files(*.*)\0*.*\0\0");

	if(IDOK==fileDlg.DoModal())
	{
		CStdioFile file;
		CFileException fileException; 	//�ļ��쳣������ʶ���д��Ժ��Ż�ʹ��	
		if(!file.Open(fileDlg.GetPathName(),CFile::typeText|CFile::modeRead)) 
		{ 
			//����TRACE()��������ϵͳ���Դ��ĵ�����ʾ�Ի���
			TRACE(_T("Can't open file %s, error = %u\n"),fileDlg.GetFileName(),fileException.m_cause); 			
		} 
		else
		{
			CString strPathName,strFileName,strFileExtName;
			strPathName.Empty();
			strFileName.Empty();
			strFileExtName.Empty();
			strPathName = fileDlg.GetPathName();//·����
			strPathName.TrimRight();
			strFileName = fileDlg.GetFileName();//�ļ���
			strFileName.TrimRight();
			strFileExtName = fileDlg.GetFileExt();//��չ��
			strFileExtName.MakeLower();//ת��ΪСд��ʽ

			//�����ļ���׺��ѡ��ͬ���ļ���ȡ����
			if (_T("txt") == strFileExtName || _T("dat") == strFileExtName || _T("out") == strFileExtName )
			{
				m_vectorRawData.clear();
				file.Close();
				ReadTxtFile(strPathName, m_vectorRawData);	

				CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//��ȡ�����ָ��
				CRawDataView* pLeftView = (CRawDataView*)pMainFrame->m_wndSplitter.GetPane(0,0);//��ȡ�ָ���ͼ������ͼָ��
				CTransDataView* pRightView = (CTransDataView*) pMainFrame->m_wndSplitter.GetPane(0,1); //��ȡ�ָ���ͼ������ͼָ��
				while((pRightView->m_RightListctrl)->DeleteItem(0));
				SendDataToListCtrl(pLeftView->m_LeftListctrl, m_vectorRawData);
			} 		
			else if (_T("xls") == strFileExtName)
			{
				AfxMessageBox(_T("���԰治֧��XLS�ļ��Ķ�ȡ"));
			}
			else if (_T("xlsx") == strFileExtName)
			{
				AfxMessageBox(_T("���԰治֧��XLSX�ļ��Ķ�ȡ"));
			}
			else
			{
				AfxMessageBox(_T("δ֪��ʽ��ϵͳ�޷�ʶ��"));
			}
		}
				
		
	//	file.Close();

		/*
		LPTSTR pBuf;
		DWORD dwFileLen;

		dwFileLen=file.GetLength();
		pBuf=new char[dwFileLen+1];
		pBuf[dwFileLen]=0;
		file.Read(pBuf,dwFileLen);
		file.Close();
		((CMainFrame *)AfxGetApp()->GetMainWnd())->m_lpTransData=pBuf;
		//		((CMainFrame *)AfxGetApp()->GetMainWnd())->m_lFileRowNum=FileRowCount(pBuf);

		SetWindowText(pBuf);//��ʾ�ļ�����
	*/	
	}
}



void CDataTransformDoc::OnEditNotidecorrect()
{
	// TODO: Add your command handler code here
	
	////�����������
	//CComboBoxEx* m_comboIndexNum = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_INDEXNUMCOMBO));
	////ʱ����Ϣ
	//CComboBoxEx* m_comboTime = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_TIMECOMBO));
	////����������
	//CComboBoxEx* m_comboEast = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_EASTCOMBO));
	////����������
	//CComboBoxEx* m_comboNorth = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_NORTHCOMBO));
	////��������
	//CComboBoxEx* m_comboEarthEll = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_EARTHHIGHTCOMBO));
	////GPSģʽ
	//CComboBoxEx* m_comboGPSModel = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_GPSMODELCOMBO));
	////��Ƶˮ��
	//CComboBoxEx* m_comboHighDepth = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_HIGHDEPTHCOMBO));
	////��Ƶˮ��
	//CComboBoxEx* m_comboLowDepth = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_LOWDEPTHCOMBO));
	////��������
	//CEdit* m_comboCorrNum = (CEdit*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_CORECTNUM));
	
	if (!m_vectorRawData.empty())
	{
		CEditNoTideCorrect* dlgEditNoTideCorrect = new CEditNoTideCorrect();
		dlgEditNoTideCorrect->Create(IDD_EDIT_NOTIDECORRECT);

		//vector<CString> vectorTemp = m_vectorRawData[0];
		//vector<CString>::iterator itratorTemp = vectorTemp.begin();
		////��ȡm_listctrl����������
		//CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
		//CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0));
		//CHeaderCtrl*  pHeaderCtrl = pRawdataview->m_LeftListctrl.GetHeaderCtrl();
		//DWORD uiColumNum(0);
		//if(pHeaderCtrl) 
		//{ 
		//	uiColumNum = pHeaderCtrl-> GetItemCount(); 
		//} 
		//char charTemp(65);
		//CString strTemp ;
		//
		//for (unsigned int itemp(0); itemp<uiColumNum; itemp++)
		//{
		//	charTemp++;
		//	strTemp.Format(_T("%c"),charTemp);
		////	m_comboIndexNum->AddString(strTemp);
		//}

		dlgEditNoTideCorrect->ShowWindow(SW_SHOWNORMAL);
		

	} 
	else
	{
		MessageBox(NULL,_T("û���ݣ�����Ϊ������"),_T(""),MB_ICONWARNING|MB_OK);
	}

	

//	delete dlgEditNoTideCorrect;  //�Ƿ�Ӧ��������������ɾ��new�ĶԻ���
	
}

void CDataTransformDoc::OnSaveCassformat()
{
	// TODO: Add your command handler code here
	//��ȡ����ָ��
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //��ȡ����ͼָ��
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
	//��ȡ�Ҳ���ͼ���У��������Ϣ
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//��ȡ������
	const DWORD tempIndexNum(0)/*���*/,  tempTime(1)/*ʱ��*/, tempEast(2)/*������*/, tempNorth(3)/*������*/;
	const DWORD tempEarthHight(4)/*������*/,tempHighDepth(6)/*��Ƶˮ��*/,tempParaValue(8)/*��������*/;
	
	if (m_rawLineAll)
	{
		//�ļ�����Ի���
		CFileDialog fileDlg(FALSE);
		fileDlg.m_ofn.lpstrTitle=_T("CASS��ʽ���ݴ洢");
		fileDlg.m_ofn.lpstrFilter=_T("CASS Format(*.dat)\0*.dat\0\0");
	//	fileDlg.m_ofn.lpstrFilter=_T("CASS Format\0\0");
		fileDlg.m_ofn.lpstrDefExt=_T("DAT");
		if(IDOK==fileDlg.DoModal())
		{
			CStdioFile file(fileDlg.GetPathName(),/*CFile::typeText |*/ CFile::modeCreate | CFile::modeWrite);
			CString strEveryLine;
			for (DWORD tempRow(0); tempRow < m_rawLineAll; tempRow++)
			{
				CString strTemp;
				strTemp.Format(_T("%.2f"),_tstof((pTransdataview->m_RightListctrl)->GetItemText(tempRow, tempEarthHight))
					+_tstof((pTransdataview->m_RightListctrl)->GetItemText(tempRow, tempHighDepth))
					-_tstof((pTransdataview->m_RightListctrl)->GetItemText(tempRow, tempParaValue)));
				CString strTempIN = (pTransdataview->m_RightListctrl)->GetItemText(tempRow, tempIndexNum);
				CString strTempT = (pTransdataview->m_RightListctrl)->GetItemText(tempRow, tempTime);
				CString strTempE = (pTransdataview->m_RightListctrl)->GetItemText(tempRow, tempEast);
				CString strTempN = (pTransdataview->m_RightListctrl)->GetItemText(tempRow, tempNorth);
				
				strEveryLine = strTempIN+_T(",") + strTempT +_T(",") + strTempE +_T(",") + strTempN +_T(",") + strTemp +_T('\n');
				file.WriteString(strEveryLine);
			}
			//	file.Write(m_lpTransResult,strlen(m_lpTransResult));
			file.Close();
			MessageBox(NULL,_T("�ļ�����ɹ���"),_T("��ʾ"),MB_OK | MB_ICONWARNING);
		}
		
	} 
	else
	{
		MessageBox(NULL,_T("����Ϊ�գ��޷�ת����"),_T("����"), MB_OK | MB_ICONERROR);
	}		
}


void CDataTransformDoc::OnExtracttide()
{
	// TODO: Add your command handler code here
	if (!m_vectorRawData.empty())
	{
		CExtractTide* dlgExtractTide = new CExtractTide();
		dlgExtractTide->Create(IDD_EDIT_EXTRACTTIDE);


		dlgExtractTide->ShowWindow(SW_SHOWNORMAL);
	} 
	else
	{
		MessageBox(NULL,_T("û���ݣ�����Ϊ������"),_T(""),MB_ICONWARNING|MB_OK);
	}
	
}


void CDataTransformDoc::OnSavetidefile()
{
	// TODO: Add your command handler code here
	//��ȡ����ָ��
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //��ȡ����ͼָ��
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
		

	if (!m_strTide[0].IsEmpty())
	{
		//�ļ�����Ի���
		CFileDialog fileDlg(FALSE);
		fileDlg.m_ofn.lpstrTitle=_T("��λ�ļ��洢");
		fileDlg.m_ofn.lpstrFilter=_T("TID Format(*.tid)\0*.tid\0\0");
		//	fileDlg.m_ofn.lpstrFilter=_T("CASS Format\0\0");
		fileDlg.m_ofn.lpstrDefExt=_T("TID");
		if(IDOK==fileDlg.DoModal())
		{
			CStdioFile file(fileDlg.GetPathName(),/*CFile::typeText |*/ CFile::modeCreate | CFile::modeWrite);
			CString strEveryLine;
			const DWORD iLineTotalNum(1440);
			for (DWORD tempRow(0); tempRow < iLineTotalNum; tempRow++)
			{
				strEveryLine = m_strTide[tempRow]+_T(" ") +_T('\n');
				file.WriteString(strEveryLine);
			}
			//	file.Write(m_lpTransResult,strlen(m_lpTransResult));
			file.Close();
			MessageBox(NULL,_T("�ļ�����ɹ���"),_T("��ʾ"),MB_OK | MB_ICONWARNING);
		}

	} 
	else
	{
		MessageBox(NULL,_T("����Ϊ�գ��޷��洢��"),_T("����"), MB_OK | MB_ICONERROR);
	}	
}
