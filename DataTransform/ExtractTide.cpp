// ExtractTide.cpp : implementation file
//

#include "stdafx.h"
#include "DataTransform.h"
#include "ExtractTide.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "RawDataView.h"
#include "TransDataView.h"
#include "EditNoTideCorrect.h"
#include "DataTransformDoc.h"

// CExtractTide dialog

IMPLEMENT_DYNAMIC(CExtractTide, CDialogEx)

CExtractTide::CExtractTide(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExtractTide::IDD, pParent)
{

}

CExtractTide::~CExtractTide()
{
}

void CExtractTide::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EXTRACTITDE_EARTHHIGHTLIST, m_comboEarthHeight);
	DDX_Control(pDX, IDC_EDIT_EXTRACTITDE_GPSMODELLIST, m_comboGpsModel);
	DDX_Control(pDX, IDC_EDIT_EXTRACTITDE_INTERPMETHODLIST, m_comboInterMethod);
	DDX_Control(pDX, IDC_EDIT_EXTRACTITDE_PARAVALUETEXT, m_textParaValue);
	DDX_Control(pDX, IDC_EDIT_EXTRACTITDE_TIMELIST, m_comboTime);
}


BEGIN_MESSAGE_MAP(CExtractTide, CDialogEx)
	ON_BN_CLICKED(IDC_EDIT_EXTRACTITDE_ETBUTTON, &CExtractTide::OnClickedEditExtractitdeEtbutton)
END_MESSAGE_MAP()


// CExtractTide message handlers


BOOL CExtractTide::OnInitDialog()
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
		m_comboTime.AddString(m_strAddItem);		
		m_comboEarthHeight.AddString(m_strAddItem);
		m_comboGpsModel.AddString(m_strAddItem);		
	}
	m_comboInterMethod.AddString(_T("线性"));
	m_comboInterMethod.AddString(_T("样条曲线"));

	m_textParaValue.ReplaceSel(_T("2000"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


///////////////////////////////////////////////////////////////
//潮位提取功能

void CExtractTide::OnClickedEditExtractitdeEtbutton()
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
	const WORD iColumnNum(4);	
	pTransdataview->m_RightListctrl->InsertColumn(0,_T("时间"),LVCFMT_CENTER,60,0);
	pTransdataview->m_RightListctrl->InsertColumn(1,_T("正常高"),LVCFMT_CENTER,60,1);
	pTransdataview->m_RightListctrl->InsertColumn(2,_T("GPS模式"),LVCFMT_CENTER,60,2);
	pTransdataview->m_RightListctrl->InsertColumn(3,_T("改正常数"),LVCFMT_CENTER,60,3);
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

	//获取各个Combox中控件中的选择项
	const DWORD COLNUM(5);
	CString uiColumn[COLNUM];			
	m_comboTime.GetWindowText(uiColumn[0]);  //时间
	m_comboEarthHeight.GetWindowText(uiColumn[1]); //正常高
	m_comboGpsModel.GetWindowText(uiColumn[2]);  //GPS模式	
	m_textParaValue.GetWindowText(uiColumn[3]);  //常数
	m_comboInterMethod.GetWindowText(uiColumn[4]); //插值方法

	for (WORD temp = 0; temp != COLNUM; temp++)
	{
		SelectDataToList(uiColumn[temp], temp);
	}

	//修正正常高
	const DWORD uiGPSmodelColumn(1);
	const DWORD uiEarthHeightColumn(2);
	int isgood = CorrectEarthHeight(tempRowCount,uiEarthHeightColumn,uiGPSmodelColumn);

	//制作潮位文件数组
	const WORD uiTimeColumn(0);
	ExtractTideToArry(uiTimeColumn , uiEarthHeightColumn);
	
	
	//结束时间
	CTime endTime = CTime::GetCurrentTime();
	WORD eH = endTime.GetHour();
	WORD eM = endTime.GetMinute();
	float eS = (float)endTime.GetSecond();

	CString leaveTime;
	leaveTime.Format(_T("潮位文件制作完毕,用时%.2f秒,请保存！"),(eH-bH)*3600+(eM-bM)*60+(eS-bS));

	MessageBox(leaveTime,_T(""), MB_ICONWARNING | MB_OK);
}


/*********************************************************************/
//自定义函数，CString tempColumn中提取原始列的值
//WORD uiColumnIndex中获取更新的索引
int CExtractTide::SelectDataToList(CString tempColumn, WORD uiColumnIndex)
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
		icolumn = 3;		
	}
	

	//获取各类数值 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //获取左视图指针
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
	
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//获取总行数

	//根据不同的条件，将值进行更新
	switch(uiColumnIndex)
	{
	case 0: //时间
	//	break;
	case 1: //正常高
	//	break;
	case 2: //GPS模式
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
	case 3: //改正常数
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
int CExtractTide::CorrectEarthHeight(DWORD rowCount, DWORD columnEarthHeight, DWORD gpsModel)
{
	//////////////////////////////////////
	//基于GPS模式修正正常高
	//获取各类数值 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //获取左视图指针
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
	
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//获取总行数
	const DWORD uiGPSmodelColumn(2);
	CString tempGPSmodel;
	const DWORD uiEarthHeightColumn(1);

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

	
	
	return 0;
}


int CExtractTide::ExtractTideToArry(DWORD columnTime,DWORD columnEarthHeight)
{
	//获取各类数值 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针	
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
	CDataTransformDoc *pDoc = (CDataTransformDoc *) pMainFrame->GetActiveDocument(); //获取文档的指针
	
//	m_strTempArray = (pDoc->m_strTide);  //将文档变量与临时变量绑定

	DWORD m_rawLineAll = (pTransdataview->m_RightListctrl)->GetItemCount();//获取总行数
	const DWORD uiTimelColumn(0);	
	const DWORD uiEarthHeightColumn(1);
	
	//将正常高列，时间列分别赋给不同的vector变量
	vector<double> m_vectorEarthHeight;
	vector<CString> m_vectorTime;
	m_vectorEarthHeight.clear();
	m_vectorTime.clear();

	//将正常高，GPS模式分别赋给两个数组
	for (DWORD tempRow = 0; tempRow < m_rawLineAll; tempRow++)
	{
		CString strTemp1, strTemp2;
		strTemp1 = (pTransdataview->m_RightListctrl)->GetItemText(tempRow,uiEarthHeightColumn);
		m_vectorEarthHeight.push_back(_tstof(strTemp1));
		strTemp2 = (pTransdataview->m_RightListctrl)->GetItemText(tempRow,uiTimelColumn);
		m_vectorTime.push_back(strTemp2);
			
	}
	//根据时间，编写临时潮位文件数组
	vector<DWORD> m_vectorArrayIndex;
	m_vectorArrayIndex.clear();
	DWORD tempUpIndex(0); //观测潮位上限
	DWORD tempDownIndex(0); //观测潮位下限
	vector<double>::iterator m_itrEH = m_vectorEarthHeight.begin();
	vector<CString>::iterator m_itrT = m_vectorTime.begin();
	int tempTideArray[1440];
	memset(tempTideArray, 0, sizeof(tempTideArray));
	DWORD tempIndex = 0;

	//更新索引容器
	for (BOOL btemp = FALSE ; (m_itrT+tempIndex) != m_vectorTime.end(); tempIndex++)
	{
		DWORD nHour = _tstoi((*(m_itrT+tempIndex)).Mid(0,2));
		DWORD nMinute = _tstoi((*(m_itrT+tempIndex)).Mid(3,2));
		DWORD nArrayIndex = nHour *60 + nMinute -1;

		m_vectorArrayIndex.push_back(nArrayIndex);
		
		//设置无潮位数据的上下区间
		if (btemp)
		{
			tempDownIndex = nArrayIndex +1;
		} 
		else
		{
			tempUpIndex = nArrayIndex -1;
			
			btemp = TRUE;
		}
	}

	//更新潮位数组
	vector<DWORD>::iterator m_itrArrayIndex = m_vectorArrayIndex.begin();
	//计算有观测潮位时间段内的潮位高程
	for (DWORD tp(0); (m_itrArrayIndex + tp) != m_vectorArrayIndex.end(); )
	{
		DWORD tempStart = *(m_itrArrayIndex + tp);
		DWORD temptp = tp;
		while((m_itrArrayIndex+(++tp)) != m_vectorArrayIndex.end() &&
			(*(m_itrArrayIndex+tp)) == tempStart);
		
		double sum(0);
		for (DWORD temp1 = temptp;temp1 < tp; temp1++)
		{
			sum += *(m_itrEH+temp1);
		}
		tempTideArray[tempStart] = (int)(sum*100/(tp-temptp));
	}
	//填充无观测时间段内的潮位
	//将前面没观测的数据设置为最近值
	for (DWORD temp(0); temp <= tempUpIndex; temp++)
	{
		tempTideArray[temp] = tempTideArray[tempUpIndex+1];
	}
	//将后面没观测时间段的潮位数据设置为最近值
	for (DWORD temp= tempDownIndex; temp < 1440; temp++)
	{
		tempTideArray[temp] = tempTideArray[tempDownIndex-1];
	}
	
	//根据改正常数修改潮位
	CString strtemp;
	m_textParaValue.GetWindowText(strtemp);
	int i = _tstoi(strtemp)/10;

	for (DWORD temp(0); temp < 1440; temp++)
	{
		tempTideArray[temp] -= i;
	}

	//最后将其更新到文档中的数据
	for (DWORD temp(0); temp < 1440; temp++)
	{
		strtemp.Format(_T("%d"),tempTideArray[temp]);
		pDoc->m_strTide[temp] = strtemp;
	}


	



	return 0;
}



//废弃的代码

/*	DWORD nSearchTemp = tempIndex+1;
		while(((m_itrT+tempIndex) < m_vectorTime.end()) && 
		(_tstoi((*(m_itrT+nSearchTemp)).Mid(3,2)) == nMinute) && 
		(_tstoi((*(m_itrT+nSearchTemp)).Mid(0,2)) == nHour))
		{
		tempIndex = nSearchTemp;
		nSearchTemp++;
		}

		double sum(0);
		for (DWORD temp = tempIndex; temp < nSearchTemp; temp++)
		{
		sum += *(m_itrEH + temp);
		}

		tempTideArray[nArrayIndex] = (int)(sum*100/(nSearchTemp-tempIndex));*/
		
		
		

	//时间字符串转时间
		/*COleDateTime oleDateTime;
		oleDateTime.ParseDateTime(strTemp2);
		CTime tempTime(oleDateTime.GetYear(), oleDateTime.GetMonth(), oleDateTime.GetDay(), 
		oleDateTime.GetHour(), oleDateTime.GetMinute(), oleDateTime.GetSecond());*/
		
		/*COleVariant vtime(strTemp2);
		vtime.ChangeType(VT_DATE);
		COleDateTime oletime=vtime;
		SYSTEMTIME   systime; 
		VariantTimeToSystemTime(oletime,  &systime); 
		CTime   ctmtemp(systime);*/

		/*COleDateTime dt;
		SYSTEMTIME st;
		dt.ParseDateTime(strTemp2);
		dt.GetAsSystemTime(st);
		st.wYear = 2000;
		CTime tempTime(st);*/
		/*int nHour(0),nMinute(0);
		int fSecond(0);	
		strTemp2.OemToCharA();*/
		/*char* strCharTemp = NULL;
		memset(strCharTemp, 0, sizeof(strCharTemp));*/
		
	//	sprintf_s((LPSTR)(LPCSTR)strTemp2.GetBuffer(), _T("%d:%d:%f"), &nHour, &nMinute, &fSecond);
	//	sscanf_s(strTemp2, "%d:%d:%f", &nHour, &nMinute, &fSecond);
	//	CTime tempTime(nHour, nMinute, fSecond);
	//	m_vectorTime.push_back(strTemp2);
