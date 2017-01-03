
// DataTransformDoc.cpp : CDataTransformDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CDataTransformDoc 构造/析构

CDataTransformDoc::CDataTransformDoc()
{
	// TODO: 在此添加一次性构造代码

}

CDataTransformDoc::~CDataTransformDoc()
{
}

BOOL CDataTransformDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CDataTransformDoc 序列化

void CDataTransformDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CDataTransformDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CDataTransformDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CDataTransformDoc 诊断

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


// CDataTransformDoc 命令


void CDataTransformDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	CString strOpenFileType = _T("Text Files(*.txt)\0*.txt\0Dat Files(*.dat)\0*.dat\0Excel Files(*.xls | *.xlsx)\0*.xls;*.xlsx\0All Files(*.*)\0*.*\0\0");
	CFileDialog fileDlg(TRUE, _T("*.txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strOpenFileType);
	fileDlg.m_ofn.lpstrTitle = _T("读取数据");
	fileDlg.m_ofn.lpstrFilter = _T("Out Files(*.out)\0*.out\0Text Files(*.txt)\0*.txt\0Dat Files(*.dat)\0*.dat\0Excel Files(*.xls | *.xlsx)\0*.xls;*.xlsx\0All Files(*.*)\0*.*\0\0");

	if(IDOK==fileDlg.DoModal())
	{
		CStdioFile file;
		CFileException fileException; 	//文件异常的类型识别，有待以后优化使用	
		if(!file.Open(fileDlg.GetPathName(),CFile::typeText|CFile::modeRead)) 
		{ 
			//利用TRACE()可以隐掉系统所自带的弹出提示对话框
			TRACE(_T("Can't open file %s, error = %u\n"),fileDlg.GetFileName(),fileException.m_cause); 			
		} 
		else
		{
			CString strPathName,strFileName,strFileExtName;
			strPathName.Empty();
			strFileName.Empty();
			strFileExtName.Empty();
			strPathName = fileDlg.GetPathName();//路径名
			strPathName.TrimRight();
			strFileName = fileDlg.GetFileName();//文件名
			strFileName.TrimRight();
			strFileExtName = fileDlg.GetFileExt();//扩展名
			strFileExtName.MakeLower();//转换为小写形式

			//根据文件后缀，选择不同的文件读取函数
			if (_T("txt") == strFileExtName || _T("dat") == strFileExtName || _T("out") == strFileExtName )
			{
				m_vectorRawData.clear();
				file.Close();
				ReadTxtFile(strPathName, m_vectorRawData);	

				CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//获取主框架指针
				CRawDataView* pLeftView = (CRawDataView*)pMainFrame->m_wndSplitter.GetPane(0,0);//获取分割视图的左视图指针
				CTransDataView* pRightView = (CTransDataView*) pMainFrame->m_wndSplitter.GetPane(0,1); //获取分割视图的右视图指针
				while((pRightView->m_RightListctrl)->DeleteItem(0));
				SendDataToListCtrl(pLeftView->m_LeftListctrl, m_vectorRawData);
			} 		
			else if (_T("xls") == strFileExtName)
			{
				AfxMessageBox(_T("测试版不支持XLS文件的读取"));
			}
			else if (_T("xlsx") == strFileExtName)
			{
				AfxMessageBox(_T("测试版不支持XLSX文件的读取"));
			}
			else
			{
				AfxMessageBox(_T("未知格式，系统无法识别！"));
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

		SetWindowText(pBuf);//显示文件内容
	*/	
	}
}



void CDataTransformDoc::OnEditNotidecorrect()
{
	// TODO: Add your command handler code here
	
	////数据索引序号
	//CComboBoxEx* m_comboIndexNum = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_INDEXNUMCOMBO));
	////时间信息
	//CComboBoxEx* m_comboTime = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_TIMECOMBO));
	////东方向坐标
	//CComboBoxEx* m_comboEast = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_EASTCOMBO));
	////北方向坐标
	//CComboBoxEx* m_comboNorth = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_NORTHCOMBO));
	////正常高列
	//CComboBoxEx* m_comboEarthEll = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_EARTHHIGHTCOMBO));
	////GPS模式
	//CComboBoxEx* m_comboGPSModel = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_GPSMODELCOMBO));
	////高频水深
	//CComboBoxEx* m_comboHighDepth = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_HIGHDEPTHCOMBO));
	////低频水深
	//CComboBoxEx* m_comboLowDepth = (CComboBoxEx*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_LOWDEPTHCOMBO));
	////改正常数
	//CEdit* m_comboCorrNum = (CEdit*)(dlgEditNoTideCorrect -> GetDlgItem(IDC_EDIT_NOTIDE_CORECTNUM));
	
	if (!m_vectorRawData.empty())
	{
		CEditNoTideCorrect* dlgEditNoTideCorrect = new CEditNoTideCorrect();
		dlgEditNoTideCorrect->Create(IDD_EDIT_NOTIDECORRECT);

		//vector<CString> vectorTemp = m_vectorRawData[0];
		//vector<CString>::iterator itratorTemp = vectorTemp.begin();
		////获取m_listctrl变量的列数
		//CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
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
		MessageBox(NULL,_T("没数据，无能为力啊！"),_T(""),MB_ICONWARNING|MB_OK);
	}

	

//	delete dlgEditNoTideCorrect;  //是否应该在析构函数中删除new的对话框
	
}

void CDataTransformDoc::OnSaveCassformat()
{
	// TODO: Add your command handler code here
	//获取各类指针
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //获取左视图指针
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
	//获取右侧视图的行，列相关信息
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//获取总行数
	const DWORD tempIndexNum(0)/*点号*/,  tempTime(1)/*时间*/, tempEast(2)/*东方向*/, tempNorth(3)/*北方向*/;
	const DWORD tempEarthHight(4)/*正常高*/,tempHighDepth(6)/*高频水深*/,tempParaValue(8)/*改正常数*/;
	
	if (m_rawLineAll)
	{
		//文件保存对话框
		CFileDialog fileDlg(FALSE);
		fileDlg.m_ofn.lpstrTitle=_T("CASS格式数据存储");
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
			MessageBox(NULL,_T("文件保存成功！"),_T("提示"),MB_OK | MB_ICONWARNING);
		}
		
	} 
	else
	{
		MessageBox(NULL,_T("数据为空，无法转换！"),_T("错误"), MB_OK | MB_ICONERROR);
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
		MessageBox(NULL,_T("没数据，无能为力啊！"),_T(""),MB_ICONWARNING|MB_OK);
	}
	
}


void CDataTransformDoc::OnSavetidefile()
{
	// TODO: Add your command handler code here
	//获取各类指针
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //获取左视图指针
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
		

	if (!m_strTide[0].IsEmpty())
	{
		//文件保存对话框
		CFileDialog fileDlg(FALSE);
		fileDlg.m_ofn.lpstrTitle=_T("潮位文件存储");
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
			MessageBox(NULL,_T("文件保存成功！"),_T("提示"),MB_OK | MB_ICONWARNING);
		}

	} 
	else
	{
		MessageBox(NULL,_T("数据为空，无法存储！"),_T("错误"), MB_OK | MB_ICONERROR);
	}	
}
