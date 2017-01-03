// EditNoTideCorrect.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransform.h"
#include "EditNoTideCorrect.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "RawDataView.h"
#include "TransDataView.h"



#ifndef __GLOBALFUNCTION_H__
//#include "globalFunction.h"
#endif


// CEditNoTideCorrect dialog

IMPLEMENT_DYNAMIC(CEditNoTideCorrect, CDialogEx)

CEditNoTideCorrect::CEditNoTideCorrect(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditNoTideCorrect::IDD, pParent)
{

}

CEditNoTideCorrect::~CEditNoTideCorrect()
{
}

void CEditNoTideCorrect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NOTIDE_EASTCOMBO, m_comboEast);
	DDX_Control(pDX, IDC_EDIT_NOTIDE_GPSMODELCOMBO, m_comboGPSmodel);
	DDX_Control(pDX, IDC_EDIT_NOTIDE_HIGHDEPTHCOMBO, m_comboHighDepth);
	DDX_Control(pDX, IDC_EDIT_NOTIDE_INDEXNUMCOMBO, m_comboIndexNum);
	DDX_Control(pDX, IDC_EDIT_NOTIDE_LOWDEPTHCOMBO, m_comboLowDepth);
	DDX_Control(pDX, IDC_EDIT_NOTIDE_NORTHCOMBO, m_comboNorth);
	DDX_Control(pDX, IDC_EDIT_NOTIDE_TIMECOMBO, m_comboTime);
	DDX_Control(pDX, IDC_EDIT_NOTIDE_EARTHHIGHTCOMBO, m_comboEarthHight);
	DDX_Control(pDX, IDC_EDIT_NOTIDE_CORECTNUM, m_editParaValue);
}


BEGIN_MESSAGE_MAP(CEditNoTideCorrect, CDialogEx)
	ON_BN_CLICKED(IDC_EDIT_NOTIDE_PARDLGEXITBOTTON, &CEditNoTideCorrect::OnBnClickedEditPardlgexit)
//	ON_WM_CREATE()
//ON_WM_LBUTTONUP()
ON_BN_CLICKED(IDC_EDIT_DATACORBUTTON, &CEditNoTideCorrect::OnClickedEditDatacorbutton)
END_MESSAGE_MAP()


// CEditNoTideCorrect message handlers


void CEditNoTideCorrect::OnBnClickedEditPardlgexit()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


//int CEditNoTideCorrect::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  Add your specialized creation code here
//	
//
//	return 0;
//}


BOOL CEditNoTideCorrect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//获取左视图原始数据中m_listctrl变量的列数
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0));
	CHeaderCtrl*  pHeaderCtrl = pRawdataview->m_LeftListctrl.GetHeaderCtrl();
	DWORD uiColumNum(0); //左视图的列数
	if(pHeaderCtrl) 
	{ 
		uiColumNum = pHeaderCtrl-> GetItemCount(); 
	} 

	CString m_strAddItem;
	for(DWORD uiColNumTemp = 0; uiColNumTemp != uiColumNum; ++uiColNumTemp)
	{
		m_strAddItem.Format(_T("列%d"),uiColNumTemp);
		m_comboIndexNum.AddString(m_strAddItem);
		m_comboTime.AddString(m_strAddItem);
		m_comboEast.AddString(m_strAddItem);
		m_comboNorth.AddString(m_strAddItem);
		m_comboEarthHight.AddString(m_strAddItem);
		m_comboGPSmodel.AddString(m_strAddItem);
		m_comboHighDepth.AddString(m_strAddItem);
		m_comboLowDepth.AddString(m_strAddItem);
	}
	m_editParaValue.ReplaceSel(_T("2000"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


//void CEditNoTideCorrect::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	AfxMessageBox(_T("test"));
//
//	CDialogEx::OnLButtonUp(nFlags, point);
//}


void CEditNoTideCorrect::OnClickedEditDatacorbutton()
{
	// TODO: Add your control notification handler code here
	//获取右视图，以更新显示转换后的数据
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //获取左视图指针
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
	
	//获取开始时间
	CTime beginTime = CTime::GetCurrentTime();
	WORD bH = beginTime.GetHour();
	WORD bM = beginTime.GetMinute();
	float bS = (float)beginTime.GetSecond(); 

	//删除右侧视图中的所有列
	while(pTransdataview->m_RightListctrl->DeleteColumn(0));
	//新建特定列“点号，时间，东方向，北方向，正常高，GPS模式，高频水深，低频水深，改正常数”
	const WORD iColumnNum(9);
	pTransdataview->m_RightListctrl->InsertColumn(0,_T("点号"),LVCFMT_CENTER,30,0);
	pTransdataview->m_RightListctrl->InsertColumn(1,_T("时间"),LVCFMT_CENTER,60,1);
	pTransdataview->m_RightListctrl->InsertColumn(2,_T("东方向"),LVCFMT_CENTER,60,2);
	pTransdataview->m_RightListctrl->InsertColumn(3,_T("北方向"),LVCFMT_CENTER,60,3);
	pTransdataview->m_RightListctrl->InsertColumn(4,_T("正常高"),LVCFMT_CENTER,60,4);
	pTransdataview->m_RightListctrl->InsertColumn(5,_T("GPS模式"),LVCFMT_CENTER,60,5);
	pTransdataview->m_RightListctrl->InsertColumn(6,_T("高频水深"),LVCFMT_CENTER,60,6);
	pTransdataview->m_RightListctrl->InsertColumn(7,_T("低频水深"),LVCFMT_CENTER,60,7);
	pTransdataview->m_RightListctrl->InsertColumn(8,_T("改正常数"),LVCFMT_CENTER,60,8);
	////给特定的列指定特定颜色
	for (WORD tempRowNum = 0; tempRowNum != iColumnNum; tempRowNum++)
	{
		//利用选择判断，设定不同的颜色
		switch (tempRowNum)
		{
		case 0:  //点号列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(216,216,216),tempRowNum); 
			break;
		case 1:  //时间列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(255,255,168),tempRowNum); 
			break;
		case 2:  //东方向列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(209,209,209),tempRowNum);  
			break;
		case 3:  //北方向列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(209,209,209),tempRowNum); 
			break;
		case 4:  //正常高列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(185,255,255),tempRowNum);
			break;
		case 5: //GPS模式列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(255,255,255),tempRowNum);
			break;
		case 6: //高频水深列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(209,209,209),tempRowNum);
			break;
		case 7: //低频水深列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(208,185,174),tempRowNum);
			break;
		case 8: //改正常数列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(180,180,180),tempRowNum);
			break;
		default: //其他列的颜色
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(188,188,188),tempRowNum);
			break;
		}
	}
	//新建特定数目的行数
	while ((pTransdataview->m_RightListctrl)->DeleteItem(0)); //删除所有行的数据	
	DWORD tempRowCount = pRawdataview->m_LeftListctrl.GetItemCount(); //行数统计
	for (DWORD tempRow = 0; tempRow != tempRowCount; ++tempRow)
	{
		(pTransdataview->m_RightListctrl)->InsertItem(tempRow+1, _T("0"));		
	}
	
//	SelectDataToList(pTransdataview->m_RightListctrl/*, strSelectColum*/);
	vector<CString> strSelectColum;

	//获取各个Combox中控件中的选择项
	const DWORD COLNUM(9);
	CString uiColumn[COLNUM];			
	m_comboIndexNum.GetWindowText(uiColumn[0]);//序号
	m_comboTime.GetWindowText(uiColumn[1]);  //时间
	m_comboEast.GetWindowText(uiColumn[2]); //东坐标
	m_comboNorth.GetWindowText(uiColumn[3]);//北坐标
	m_comboEarthHight.GetWindowText(uiColumn[4]); //正常高
	m_comboGPSmodel.GetWindowText(uiColumn[5]);  //GPS模式	
	m_comboHighDepth.GetWindowText(uiColumn[6]);  //高频水深
	m_comboLowDepth.GetWindowText(uiColumn[7]);  //低频水深
	m_editParaValue.GetWindowText(uiColumn[8]);  //常数

	if ((uiColumn[5].IsEmpty()) || (uiColumn[4].IsEmpty()) || (uiColumn[6].IsEmpty()))
	{
		MessageBox(_T("参数配置或源文件有误，请核查！"),_T(""),MB_OK | MB_ICONERROR);				
	}
	else
	{
		//根据选择，对右视图进行更新
		for (WORD temp = 0; temp != COLNUM; temp++)
		{
			SelectDataToList(uiColumn[temp], temp);
		}
		//修正正常高
		const DWORD uiGPSmodelColumn(5);
		const DWORD uiEarthHeightColumn(4);
		int isgood = CorrectEarthHeight(tempRowCount,uiEarthHeightColumn,uiGPSmodelColumn);
		//修正水深噪声
		CorrectWaterDepth(tempRowCount,6,7);

		//根据CorrectEarthHeight函数的不同返回值，判断是否成功，如果为-1，则说明执行失败，如果为0，则说明执行成功
		if (isgood == 0)
		{
			//结束时间
			CTime endTime = CTime::GetCurrentTime();
			WORD eH = endTime.GetHour();
			WORD eM = endTime.GetMinute();
			float eS = (float)endTime.GetSecond();

			CString leaveTime;
			leaveTime.Format(_T("无验潮数据修正完毕,用时%.2f秒"),(eH-bH)*3600+(eM-bM)*60+(eS-bS));

			MessageBox(leaveTime,_T(""), MB_ICONWARNING | MB_OK);
		} 
				
	}		
}

/*********************************************************************/
//自定义函数，CString tempColumn中提取原始列的值
//WORD uiColumnIndex中获取更新的索引
int CEditNoTideCorrect::SelectDataToList(CString tempColumn, WORD uiColumnIndex)
{
	//获取原始列的索引
	CString strTempColumn;
	DWORD icolumn(0);
	int i= tempColumn.Find(_T('列'));
	if ((0 == tempColumn.Find(_T('列'))) || tempColumn.IsEmpty())
	{
		strTempColumn = tempColumn.Right(tempColumn.GetLength()-1);
		icolumn = _tstol(strTempColumn);
	} 
	else
	{
		icolumn = 8;		
	}
	

	//获取各类数值 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //获取左视图指针
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
	
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//获取总行数

	//根据不同的条件，将值进行更新
	switch(uiColumnIndex)
	{
	case 0: //序号
		for (int temp = 0; temp != m_rawLineAll; temp++) //将选择列复制到右侧视图
		{
			strTempColumn.Format(_T("%d"),temp);
			(pTransdataview->m_RightListctrl)->SetItemText(temp, uiColumnIndex, strTempColumn);
		}
		break;
	case 1: //时间
	//	break;
	case 2: //东坐标
	//	break;
	case 3: //北坐标
	//	break;
	case 4: //正常高
	//	break;
	case 5: //GPS模式
	//	break;
	case 6: //高频水深
	//	break;
	case 7: //低频水深
		if (!tempColumn.IsEmpty())
		{
			for (int temp = 0; temp != m_rawLineAll; temp++) //将选择列复制到右侧视图
			{
				(pTransdataview->m_RightListctrl)->SetItemText(temp, uiColumnIndex, (pRawdataview->m_LeftListctrl).GetItemText(temp,icolumn));
			}
		} 
		else
		{
			for (int temp = 0; temp != m_rawLineAll; temp++) //将选择列复制到右侧视图
			{
				(pTransdataview->m_RightListctrl)->SetItemText(temp, uiColumnIndex, _T(" "));
			}
		}
		break;
	case 8: //改正常数
		for (int temp = 0; temp != m_rawLineAll; temp++) //将选择列复制到右侧视图
		{
			double icolumn = _tstof(tempColumn); 			
			strTempColumn.Format(_T("%.3f"),icolumn/1000);  //
			(pTransdataview->m_RightListctrl)->SetItemText(temp, uiColumnIndex, strTempColumn);
		}
		break;
	default:
		break;
	}

	
	return 0;
}

//自定义函数，根据GPS模式修改正常高
int CEditNoTideCorrect::CorrectEarthHeight(DWORD rowCount, DWORD columnEarthHeight, DWORD gpsModel)
{
	//////////////////////////////////////
	//基于GPS模式修正正常高
	//获取各类数值 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //获取左视图指针
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
	
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//获取总行数
	const DWORD uiGPSmodelColumn(5);
	CString tempGPSmodel;
	const DWORD uiEarthHeightColumn(4);

	//将正常高列，GPS模式列分别赋给不同的vector<float>变量，进行修正，然后将值赋给CListCtrl变量
	const DWORD uiAllLineCount(m_rawLineAll);
	vector<double> m_vectorEarthHeight;
	vector<WORD> m_vectorGPSModel;
	m_vectorEarthHeight.clear();
	m_vectorGPSModel.clear();
	
	//将正常高，GPS模式分别赋给两个数组
	for (DWORD tempRow = 0; tempRow < m_rawLineAll; tempRow++)
	{
		CString strTemp1, strTemp2;
		strTemp1 = (pTransdataview->m_RightListctrl)->GetItemText(tempRow,uiEarthHeightColumn);
		strTemp2 = (pTransdataview->m_RightListctrl)->GetItemText(tempRow,uiGPSmodelColumn);
		m_vectorEarthHeight.push_back(_tstof(strTemp1));
		m_vectorGPSModel.push_back(_tstoi(strTemp2));
	}
	
	vector<double>::iterator m_itrEH = m_vectorEarthHeight.begin();
	vector<WORD>::iterator m_itrGM = m_vectorGPSModel.begin();

	////首先判断GPS model是否正常，否则则无解，退出
	DWORD tempRow(0);
	for (; tempRow < m_rawLineAll; tempRow++)
	{
		if (*(m_itrGM+tempRow) == 4)
		{
			break;
		} 
	}
	if (tempRow == m_rawLineAll)
	{
		MessageBox(_T("源数据无固定解，请检查源文件或参数配置！"), _T(""), MB_OK | MB_ICONERROR);
		return -1;
	}

	//////////////////////////////////////
	//逐行扫描，分不同的情况对正常高进行修正
	//1.首行非固定解时，最近固定解上移复制
	//2.尾行非固定解时，最近固定解下移复制
	//3.在中间时，线性插值
	/////////////////////////////////////
	for (DWORD m_length = 0 ; m_length < m_rawLineAll; )
	{
		if (*(m_itrGM+m_length) == 4)
		{
			m_length++; //固定解时，转入下行判断
			continue;
		} 
		else
		{
			DWORD downNum = m_length ;
			//寻找下面为固定解的值
			while (((++downNum)<m_rawLineAll) && (*(m_itrGM+downNum) != 4));
				
			//判断未尾行是否固定解，给予不同的处理方式
			if (downNum < m_rawLineAll)
			{
				//判断是否为首行，并给与不同的处理方式
				//非首行时，前后插值
				if ((m_length-1) != -1) 
				{
					int i = m_length - 1;
					double dIncreasement = (*(m_itrEH+downNum)-*(m_itrEH+m_length-1))/(downNum-m_length+1);
					for (DWORD temp = m_length; temp < downNum; temp++)
					{
						DWORD i(0);
						*(m_itrEH + temp) = *(m_itrEH+temp-1)+(++i)*dIncreasement;
					}
				} 
				else
				{
					//首行为非固定解时，将最近的固定解移植给首行
					//[m_length, dwonNum-1]区间内的值修改成最近固定值
					for (DWORD temp = m_length; temp < downNum; temp++)
					{
						*(m_itrEH + temp) = *(m_itrEH +downNum);
					}
				}
			} 
			else
			{
				for (DWORD temp = m_length; temp < downNum; temp++)
				{
					DWORD i(0);
					*(m_itrEH + temp) = *(m_itrEH+m_length-1);
				}
			}
			
			
			m_length = downNum;
		}
	}
	
	CString strTransTemp;
	for (DWORD temp = 0; temp < m_rawLineAll; temp++)
	{
		strTransTemp.Format(_T("%.2f"),*(m_itrEH+temp));
		(pTransdataview->m_RightListctrl)->SetItemText(temp, uiEarthHeightColumn, strTransTemp);
		/*if (*(m_itrGM+temp)!=4)
		{
		(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), temp, uiEarthHeightColumn);
		(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), temp, uiGPSmodelColumn);
		}*/
	}



	//字符串类的比较，禁用了,用数值比较，可能效率更高
	if(FALSE){
	//逐行扫描各个行，判断其GPS model是否为固定解
	for (DWORD iline = 0; iline <= (m_rawLineAll-1); /*iline++*/) 
	{
		tempGPSmodel = (pTransdataview->m_RightListctrl)->GetItemText(iline, uiGPSmodelColumn);
		DWORD fgpsmodel = _tstoi(tempGPSmodel);
		//首先判断首行是否固定解，如果不是固定解，则把下面最近的固定解赋值给它
		if ((4 != fgpsmodel ) && (iline == 0)) 
		{
			//向下搜索固定解时的正常高
			DWORD downtemp = iline;			
			while (++downtemp)
			{
				tempGPSmodel = (pTransdataview->m_RightListctrl)->GetItemText(downtemp, uiGPSmodelColumn);
				if (4 == _tstoi(tempGPSmodel))
				{
					break;
				}
			//	downtemp++;
			}
			(pTransdataview->m_RightListctrl)->SetItemText(iline,uiEarthHeightColumn,
				(pTransdataview->m_RightListctrl)->GetItemText(downtemp,uiEarthHeightColumn));
			(pTransdataview->m_RightListctrl)->SetItemText(iline,uiGPSmodelColumn,_T("4"));
			(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), iline, uiEarthHeightColumn);
			(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), iline, uiGPSmodelColumn);
			//行数自增
			iline++;
		} 
		//非首先时，逐行扫描。如果发现某行的GPS model是非固定解，则利用线性插值，将正常高进行内插。
		else 
		{
			//逐行判断GPS model是否为非固定解，如果为非固定解，则找到下面最近的固定解行，将其值做为下限，进行高程内插
			tempGPSmodel = (pTransdataview->m_RightListctrl)->GetItemText(iline, uiGPSmodelColumn);
			if (4 != _tstoi(tempGPSmodel))
			{
				DWORD downtemp2 = iline;
				//寻找下一个固定解的行索引，并判断它是否是最后一行
				while(downtemp2 != (m_rawLineAll))
				{
					downtemp2++;
					tempGPSmodel = (pTransdataview->m_RightListctrl)->GetItemText(downtemp2, uiGPSmodelColumn);
					if (4 == _tstoi(tempGPSmodel))
					{
						break;
					}
				}
				//判断非固定解的下限是否最后列，给柔不同的处理方式
				if (downtemp2 <= (m_rawLineAll-1))
				{
					CString tempUpRow = (pTransdataview->m_RightListctrl)->GetItemText(iline-1, uiEarthHeightColumn);
					CString tempDownRow = (pTransdataview->m_RightListctrl)->GetItemText(downtemp2, uiEarthHeightColumn);
					double fStep = (_tstof(tempDownRow)-_tstof(tempUpRow))/(downtemp2-iline+1);
					for (DWORD temp = 1; (iline+temp-1) != downtemp2; temp++)
					{
						CString strTemp;
						strTemp.Format(_T("%.3g"),_tstof(tempUpRow)+temp*fStep);
						(pTransdataview->m_RightListctrl)->SetItemText(iline+temp-1,uiEarthHeightColumn,strTemp);
						(pTransdataview->m_RightListctrl)->SetItemText(iline+temp-1,uiGPSmodelColumn,_T("4"));
						(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), iline+temp-1, uiEarthHeightColumn);
						(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), iline+temp-1, uiGPSmodelColumn);
					}
					
					iline = downtemp2;
				} 
				else
				{
					(pTransdataview->m_RightListctrl)->SetItemText(iline,uiEarthHeightColumn,
						(pTransdataview->m_RightListctrl)->GetItemText(iline-1,uiEarthHeightColumn));
					(pTransdataview->m_RightListctrl)->SetItemText(iline,uiGPSmodelColumn,_T("4"));
					(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), iline, uiEarthHeightColumn);
					(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), iline, uiGPSmodelColumn);	
				//	iline = downtemp2 +1;
				}
							
			}
			else
			{
				iline++; //如果GPS是固定解，则往下继续搜索
			}
			
		}
	}
	}
	return 0;
}

//////////////////////////////////////////////////////
//水深修正函数，用来去除噪声，且对低频水深进行修正
//
int CEditNoTideCorrect::CorrectWaterDepth(DWORD rowCount, DWORD columnHighDepth, DWORD columnLowDepth)
{
	///////////////////////////////////////
	
	//初始阶段，变量的初始化，各类变量的定义 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //获取左视图指针
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
		
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//获取总行数
	const DWORD uiHighDepthColumn(6);
	CString tempHighDepth;
	CString tempLowDepth;
	const DWORD uiLowDepthColumn(7);
	vector<double> m_vectorHighDepth;
	vector<double> m_vectorLowDepth;

	for (DWORD tempRow(0); tempRow < m_rawLineAll; tempRow++)
	{
		//获取高频，低频的水深列，并进行赋值给vector变量
		tempHighDepth = (pTransdataview->m_RightListctrl)->GetItemText(tempRow, uiHighDepthColumn);
		tempLowDepth = (pTransdataview->m_RightListctrl)->GetItemText(tempRow, uiLowDepthColumn);

		//将CString类型的数字字符串转为double型数值
		m_vectorHighDepth.push_back(_tstof(tempHighDepth)); 
		m_vectorLowDepth.push_back(_tstof(tempLowDepth));
	}

	//获取高，低频水深的迭代器
	vector<double>::iterator m_itrHighDepth = m_vectorHighDepth.begin();
	vector<double>::iterator m_itrLowDepth = m_vectorLowDepth.begin();

		/////////////////////////////////////////////////////////
		//根据测量的水深值，及船的吃水情况，判断错误的水深，并进行修正
	///////////////////////////////////////////////////////////
		//修正高频水深列

	//存在不完全判断，如果第一个水深为0，则会出现重大问题
	for (DWORD tempRow(1); tempRow < m_rawLineAll-1; tempRow++)
	{
		if (abs(*(m_itrHighDepth+tempRow)) < 1)
		{
			*(m_itrHighDepth+tempRow) = *(m_itrHighDepth+tempRow-1);
		}
	}
	
	

	////////////////////////////////////////////////
	//修正低频水深
	for (DWORD tempRow(0); tempRow < m_rawLineAll-1; tempRow++)
	{
		if(abs(*(m_itrLowDepth+tempRow)-*(m_itrHighDepth+tempRow)) > 1)
		{
			*(m_itrLowDepth+tempRow) = *(m_itrHighDepth+tempRow) - 0.2;
		}
	}
	
	//将修改结果更新到右侧列表
	CString strTransTempH, strTransTempL;
	for (DWORD temp = 0; temp < m_rawLineAll; temp++)
	{
		strTransTempH.Format(_T("%.2f"),*(m_itrHighDepth+temp));
		strTransTempL.Format(_T("%.2f"),*(m_itrLowDepth+temp));
		(pTransdataview->m_RightListctrl)->SetItemText(temp, uiHighDepthColumn, strTransTempH);
		(pTransdataview->m_RightListctrl)->SetItemText(temp, uiLowDepthColumn, strTransTempL);
		/*if (*(m_itrGM+temp)!=4)
		{
		(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), temp, uiEarthHeightColumn);
		(pTransdataview->m_RightListctrl)->SetCellColor(RGB(255,98,98), temp, uiGPSmodelColumn);
		}*/
	}
		
	return 0;
}