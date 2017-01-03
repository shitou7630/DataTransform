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
	//��ȡ����ͼԭʼ������m_listctrl����������
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0));
	CHeaderCtrl*  pHeaderCtrl = pRawdataview->m_LeftListctrl.GetHeaderCtrl();
	DWORD uiColumNum(0); //����ͼ������
	if(pHeaderCtrl) 
	{ 
		uiColumNum = pHeaderCtrl-> GetItemCount(); 
	} 

	CString m_strAddItem;
	for(DWORD uiColNumTemp = 0; uiColNumTemp != uiColumNum; ++uiColNumTemp)
	{
		m_strAddItem.Format(_T("��%d"),uiColNumTemp);
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
	//��ȡ����ͼ���Ը�����ʾת���������
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //��ȡ����ͼָ��
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
	
	//��ȡ��ʼʱ��
	CTime beginTime = CTime::GetCurrentTime();
	WORD bH = beginTime.GetHour();
	WORD bM = beginTime.GetMinute();
	float bS = (float)beginTime.GetSecond(); 

	//ɾ���Ҳ���ͼ�е�������
	while(pTransdataview->m_RightListctrl->DeleteColumn(0));
	//�½��ض��С���ţ�ʱ�䣬�����򣬱����������ߣ�GPSģʽ����Ƶˮ���Ƶˮ�����������
	const WORD iColumnNum(9);
	pTransdataview->m_RightListctrl->InsertColumn(0,_T("���"),LVCFMT_CENTER,30,0);
	pTransdataview->m_RightListctrl->InsertColumn(1,_T("ʱ��"),LVCFMT_CENTER,60,1);
	pTransdataview->m_RightListctrl->InsertColumn(2,_T("������"),LVCFMT_CENTER,60,2);
	pTransdataview->m_RightListctrl->InsertColumn(3,_T("������"),LVCFMT_CENTER,60,3);
	pTransdataview->m_RightListctrl->InsertColumn(4,_T("������"),LVCFMT_CENTER,60,4);
	pTransdataview->m_RightListctrl->InsertColumn(5,_T("GPSģʽ"),LVCFMT_CENTER,60,5);
	pTransdataview->m_RightListctrl->InsertColumn(6,_T("��Ƶˮ��"),LVCFMT_CENTER,60,6);
	pTransdataview->m_RightListctrl->InsertColumn(7,_T("��Ƶˮ��"),LVCFMT_CENTER,60,7);
	pTransdataview->m_RightListctrl->InsertColumn(8,_T("��������"),LVCFMT_CENTER,60,8);
	////���ض�����ָ���ض���ɫ
	for (WORD tempRowNum = 0; tempRowNum != iColumnNum; tempRowNum++)
	{
		//����ѡ���жϣ��趨��ͬ����ɫ
		switch (tempRowNum)
		{
		case 0:  //����е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(216,216,216),tempRowNum); 
			break;
		case 1:  //ʱ���е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(255,255,168),tempRowNum); 
			break;
		case 2:  //�������е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(209,209,209),tempRowNum);  
			break;
		case 3:  //�������е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(209,209,209),tempRowNum); 
			break;
		case 4:  //�������е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(185,255,255),tempRowNum);
			break;
		case 5: //GPSģʽ�е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(255,255,255),tempRowNum);
			break;
		case 6: //��Ƶˮ���е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(209,209,209),tempRowNum);
			break;
		case 7: //��Ƶˮ���е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(208,185,174),tempRowNum);
			break;
		case 8: //���������е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(180,180,180),tempRowNum);
			break;
		default: //�����е���ɫ
			(pTransdataview->m_RightListctrl)->SetColColor(RGB(188,188,188),tempRowNum);
			break;
		}
	}
	//�½��ض���Ŀ������
	while ((pTransdataview->m_RightListctrl)->DeleteItem(0)); //ɾ�������е�����	
	DWORD tempRowCount = pRawdataview->m_LeftListctrl.GetItemCount(); //����ͳ��
	for (DWORD tempRow = 0; tempRow != tempRowCount; ++tempRow)
	{
		(pTransdataview->m_RightListctrl)->InsertItem(tempRow+1, _T("0"));		
	}
	
//	SelectDataToList(pTransdataview->m_RightListctrl/*, strSelectColum*/);
	vector<CString> strSelectColum;

	//��ȡ����Combox�пؼ��е�ѡ����
	const DWORD COLNUM(9);
	CString uiColumn[COLNUM];			
	m_comboIndexNum.GetWindowText(uiColumn[0]);//���
	m_comboTime.GetWindowText(uiColumn[1]);  //ʱ��
	m_comboEast.GetWindowText(uiColumn[2]); //������
	m_comboNorth.GetWindowText(uiColumn[3]);//������
	m_comboEarthHight.GetWindowText(uiColumn[4]); //������
	m_comboGPSmodel.GetWindowText(uiColumn[5]);  //GPSģʽ	
	m_comboHighDepth.GetWindowText(uiColumn[6]);  //��Ƶˮ��
	m_comboLowDepth.GetWindowText(uiColumn[7]);  //��Ƶˮ��
	m_editParaValue.GetWindowText(uiColumn[8]);  //����

	if ((uiColumn[5].IsEmpty()) || (uiColumn[4].IsEmpty()) || (uiColumn[6].IsEmpty()))
	{
		MessageBox(_T("�������û�Դ�ļ�������˲飡"),_T(""),MB_OK | MB_ICONERROR);				
	}
	else
	{
		//����ѡ�񣬶�����ͼ���и���
		for (WORD temp = 0; temp != COLNUM; temp++)
		{
			SelectDataToList(uiColumn[temp], temp);
		}
		//����������
		const DWORD uiGPSmodelColumn(5);
		const DWORD uiEarthHeightColumn(4);
		int isgood = CorrectEarthHeight(tempRowCount,uiEarthHeightColumn,uiGPSmodelColumn);
		//����ˮ������
		CorrectWaterDepth(tempRowCount,6,7);

		//����CorrectEarthHeight�����Ĳ�ͬ����ֵ���ж��Ƿ�ɹ������Ϊ-1����˵��ִ��ʧ�ܣ����Ϊ0����˵��ִ�гɹ�
		if (isgood == 0)
		{
			//����ʱ��
			CTime endTime = CTime::GetCurrentTime();
			WORD eH = endTime.GetHour();
			WORD eM = endTime.GetMinute();
			float eS = (float)endTime.GetSecond();

			CString leaveTime;
			leaveTime.Format(_T("���鳱�����������,��ʱ%.2f��"),(eH-bH)*3600+(eM-bM)*60+(eS-bS));

			MessageBox(leaveTime,_T(""), MB_ICONWARNING | MB_OK);
		} 
				
	}		
}

/*********************************************************************/
//�Զ��庯����CString tempColumn����ȡԭʼ�е�ֵ
//WORD uiColumnIndex�л�ȡ���µ�����
int CEditNoTideCorrect::SelectDataToList(CString tempColumn, WORD uiColumnIndex)
{
	//��ȡԭʼ�е�����
	CString strTempColumn;
	DWORD icolumn(0);
	int i= tempColumn.Find(_T('��'));
	if ((0 == tempColumn.Find(_T('��'))) || tempColumn.IsEmpty())
	{
		strTempColumn = tempColumn.Right(tempColumn.GetLength()-1);
		icolumn = _tstol(strTempColumn);
	} 
	else
	{
		icolumn = 8;		
	}
	

	//��ȡ������ֵ 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //��ȡ����ͼָ��
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
	
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//��ȡ������

	//���ݲ�ͬ����������ֵ���и���
	switch(uiColumnIndex)
	{
	case 0: //���
		for (int temp = 0; temp != m_rawLineAll; temp++) //��ѡ���и��Ƶ��Ҳ���ͼ
		{
			strTempColumn.Format(_T("%d"),temp);
			(pTransdataview->m_RightListctrl)->SetItemText(temp, uiColumnIndex, strTempColumn);
		}
		break;
	case 1: //ʱ��
	//	break;
	case 2: //������
	//	break;
	case 3: //������
	//	break;
	case 4: //������
	//	break;
	case 5: //GPSģʽ
	//	break;
	case 6: //��Ƶˮ��
	//	break;
	case 7: //��Ƶˮ��
		if (!tempColumn.IsEmpty())
		{
			for (int temp = 0; temp != m_rawLineAll; temp++) //��ѡ���и��Ƶ��Ҳ���ͼ
			{
				(pTransdataview->m_RightListctrl)->SetItemText(temp, uiColumnIndex, (pRawdataview->m_LeftListctrl).GetItemText(temp,icolumn));
			}
		} 
		else
		{
			for (int temp = 0; temp != m_rawLineAll; temp++) //��ѡ���и��Ƶ��Ҳ���ͼ
			{
				(pTransdataview->m_RightListctrl)->SetItemText(temp, uiColumnIndex, _T(" "));
			}
		}
		break;
	case 8: //��������
		for (int temp = 0; temp != m_rawLineAll; temp++) //��ѡ���и��Ƶ��Ҳ���ͼ
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

//�Զ��庯��������GPSģʽ�޸�������
int CEditNoTideCorrect::CorrectEarthHeight(DWORD rowCount, DWORD columnEarthHeight, DWORD gpsModel)
{
	//////////////////////////////////////
	//����GPSģʽ����������
	//��ȡ������ֵ 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //��ȡ����ͼָ��
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
	
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//��ȡ������
	const DWORD uiGPSmodelColumn(5);
	CString tempGPSmodel;
	const DWORD uiEarthHeightColumn(4);

	//���������У�GPSģʽ�зֱ𸳸���ͬ��vector<float>����������������Ȼ��ֵ����CListCtrl����
	const DWORD uiAllLineCount(m_rawLineAll);
	vector<double> m_vectorEarthHeight;
	vector<WORD> m_vectorGPSModel;
	m_vectorEarthHeight.clear();
	m_vectorGPSModel.clear();
	
	//�������ߣ�GPSģʽ�ֱ𸳸���������
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

	////�����ж�GPS model�Ƿ��������������޽⣬�˳�
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
		MessageBox(_T("Դ�����޹̶��⣬����Դ�ļ���������ã�"), _T(""), MB_OK | MB_ICONERROR);
		return -1;
	}

	//////////////////////////////////////
	//����ɨ�裬�ֲ�ͬ������������߽�������
	//1.���зǹ̶���ʱ������̶������Ƹ���
	//2.β�зǹ̶���ʱ������̶������Ƹ���
	//3.���м�ʱ�����Բ�ֵ
	/////////////////////////////////////
	for (DWORD m_length = 0 ; m_length < m_rawLineAll; )
	{
		if (*(m_itrGM+m_length) == 4)
		{
			m_length++; //�̶���ʱ��ת�������ж�
			continue;
		} 
		else
		{
			DWORD downNum = m_length ;
			//Ѱ������Ϊ�̶����ֵ
			while (((++downNum)<m_rawLineAll) && (*(m_itrGM+downNum) != 4));
				
			//�ж�δβ���Ƿ�̶��⣬���費ͬ�Ĵ���ʽ
			if (downNum < m_rawLineAll)
			{
				//�ж��Ƿ�Ϊ���У������벻ͬ�Ĵ���ʽ
				//������ʱ��ǰ���ֵ
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
					//����Ϊ�ǹ̶���ʱ��������Ĺ̶�����ֲ������
					//[m_length, dwonNum-1]�����ڵ�ֵ�޸ĳ�����̶�ֵ
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



	//�ַ�����ıȽϣ�������,����ֵ�Ƚϣ�����Ч�ʸ���
	if(FALSE){
	//����ɨ������У��ж���GPS model�Ƿ�Ϊ�̶���
	for (DWORD iline = 0; iline <= (m_rawLineAll-1); /*iline++*/) 
	{
		tempGPSmodel = (pTransdataview->m_RightListctrl)->GetItemText(iline, uiGPSmodelColumn);
		DWORD fgpsmodel = _tstoi(tempGPSmodel);
		//�����ж������Ƿ�̶��⣬������ǹ̶��⣬�����������Ĺ̶��⸳ֵ����
		if ((4 != fgpsmodel ) && (iline == 0)) 
		{
			//���������̶���ʱ��������
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
			//��������
			iline++;
		} 
		//������ʱ������ɨ�衣�������ĳ�е�GPS model�Ƿǹ̶��⣬���������Բ�ֵ���������߽����ڲ塣
		else 
		{
			//�����ж�GPS model�Ƿ�Ϊ�ǹ̶��⣬���Ϊ�ǹ̶��⣬���ҵ���������Ĺ̶����У�����ֵ��Ϊ���ޣ����и߳��ڲ�
			tempGPSmodel = (pTransdataview->m_RightListctrl)->GetItemText(iline, uiGPSmodelColumn);
			if (4 != _tstoi(tempGPSmodel))
			{
				DWORD downtemp2 = iline;
				//Ѱ����һ���̶���������������ж����Ƿ������һ��
				while(downtemp2 != (m_rawLineAll))
				{
					downtemp2++;
					tempGPSmodel = (pTransdataview->m_RightListctrl)->GetItemText(downtemp2, uiGPSmodelColumn);
					if (4 == _tstoi(tempGPSmodel))
					{
						break;
					}
				}
				//�жϷǹ̶���������Ƿ�����У����᲻ͬ�Ĵ���ʽ
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
				iline++; //���GPS�ǹ̶��⣬�����¼�������
			}
			
		}
	}
	}
	return 0;
}

//////////////////////////////////////////////////////
//ˮ����������������ȥ���������ҶԵ�Ƶˮ���������
//
int CEditNoTideCorrect::CorrectWaterDepth(DWORD rowCount, DWORD columnHighDepth, DWORD columnLowDepth)
{
	///////////////////////////////////////
	
	//��ʼ�׶Σ������ĳ�ʼ������������Ķ��� 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //��ȡ����ͼָ��
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
		
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//��ȡ������
	const DWORD uiHighDepthColumn(6);
	CString tempHighDepth;
	CString tempLowDepth;
	const DWORD uiLowDepthColumn(7);
	vector<double> m_vectorHighDepth;
	vector<double> m_vectorLowDepth;

	for (DWORD tempRow(0); tempRow < m_rawLineAll; tempRow++)
	{
		//��ȡ��Ƶ����Ƶ��ˮ���У������и�ֵ��vector����
		tempHighDepth = (pTransdataview->m_RightListctrl)->GetItemText(tempRow, uiHighDepthColumn);
		tempLowDepth = (pTransdataview->m_RightListctrl)->GetItemText(tempRow, uiLowDepthColumn);

		//��CString���͵������ַ���תΪdouble����ֵ
		m_vectorHighDepth.push_back(_tstof(tempHighDepth)); 
		m_vectorLowDepth.push_back(_tstof(tempLowDepth));
	}

	//��ȡ�ߣ���Ƶˮ��ĵ�����
	vector<double>::iterator m_itrHighDepth = m_vectorHighDepth.begin();
	vector<double>::iterator m_itrLowDepth = m_vectorLowDepth.begin();

		/////////////////////////////////////////////////////////
		//���ݲ�����ˮ��ֵ�������ĳ�ˮ������жϴ����ˮ�����������
	///////////////////////////////////////////////////////////
		//������Ƶˮ����

	//���ڲ���ȫ�жϣ������һ��ˮ��Ϊ0���������ش�����
	for (DWORD tempRow(1); tempRow < m_rawLineAll-1; tempRow++)
	{
		if (abs(*(m_itrHighDepth+tempRow)) < 1)
		{
			*(m_itrHighDepth+tempRow) = *(m_itrHighDepth+tempRow-1);
		}
	}
	
	

	////////////////////////////////////////////////
	//������Ƶˮ��
	for (DWORD tempRow(0); tempRow < m_rawLineAll-1; tempRow++)
	{
		if(abs(*(m_itrLowDepth+tempRow)-*(m_itrHighDepth+tempRow)) > 1)
		{
			*(m_itrLowDepth+tempRow) = *(m_itrHighDepth+tempRow) - 0.2;
		}
	}
	
	//���޸Ľ�����µ��Ҳ��б�
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