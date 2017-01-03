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
		m_comboTime.AddString(m_strAddItem);		
		m_comboEarthHeight.AddString(m_strAddItem);
		m_comboGpsModel.AddString(m_strAddItem);		
	}
	m_comboInterMethod.AddString(_T("����"));
	m_comboInterMethod.AddString(_T("��������"));

	m_textParaValue.ReplaceSel(_T("2000"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


///////////////////////////////////////////////////////////////
//��λ��ȡ����

void CExtractTide::OnClickedEditExtractitdeEtbutton()
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
	const WORD iColumnNum(4);	
	pTransdataview->m_RightListctrl->InsertColumn(0,_T("ʱ��"),LVCFMT_CENTER,60,0);
	pTransdataview->m_RightListctrl->InsertColumn(1,_T("������"),LVCFMT_CENTER,60,1);
	pTransdataview->m_RightListctrl->InsertColumn(2,_T("GPSģʽ"),LVCFMT_CENTER,60,2);
	pTransdataview->m_RightListctrl->InsertColumn(3,_T("��������"),LVCFMT_CENTER,60,3);
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

	//��ȡ����Combox�пؼ��е�ѡ����
	const DWORD COLNUM(5);
	CString uiColumn[COLNUM];			
	m_comboTime.GetWindowText(uiColumn[0]);  //ʱ��
	m_comboEarthHeight.GetWindowText(uiColumn[1]); //������
	m_comboGpsModel.GetWindowText(uiColumn[2]);  //GPSģʽ	
	m_textParaValue.GetWindowText(uiColumn[3]);  //����
	m_comboInterMethod.GetWindowText(uiColumn[4]); //��ֵ����

	for (WORD temp = 0; temp != COLNUM; temp++)
	{
		SelectDataToList(uiColumn[temp], temp);
	}

	//����������
	const DWORD uiGPSmodelColumn(1);
	const DWORD uiEarthHeightColumn(2);
	int isgood = CorrectEarthHeight(tempRowCount,uiEarthHeightColumn,uiGPSmodelColumn);

	//������λ�ļ�����
	const WORD uiTimeColumn(0);
	ExtractTideToArry(uiTimeColumn , uiEarthHeightColumn);
	
	
	//����ʱ��
	CTime endTime = CTime::GetCurrentTime();
	WORD eH = endTime.GetHour();
	WORD eM = endTime.GetMinute();
	float eS = (float)endTime.GetSecond();

	CString leaveTime;
	leaveTime.Format(_T("��λ�ļ��������,��ʱ%.2f��,�뱣�棡"),(eH-bH)*3600+(eM-bM)*60+(eS-bS));

	MessageBox(leaveTime,_T(""), MB_ICONWARNING | MB_OK);
}


/*********************************************************************/
//�Զ��庯����CString tempColumn����ȡԭʼ�е�ֵ
//WORD uiColumnIndex�л�ȡ���µ�����
int CExtractTide::SelectDataToList(CString tempColumn, WORD uiColumnIndex)
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
		icolumn = 3;		
	}
	

	//��ȡ������ֵ 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //��ȡ����ͼָ��
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
	
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//��ȡ������

	//���ݲ�ͬ����������ֵ���и���
	switch(uiColumnIndex)
	{
	case 0: //ʱ��
	//	break;
	case 1: //������
	//	break;
	case 2: //GPSģʽ
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
	case 3: //��������
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
int CExtractTide::CorrectEarthHeight(DWORD rowCount, DWORD columnEarthHeight, DWORD gpsModel)
{
	//////////////////////////////////////
	//����GPSģʽ����������
	//��ȡ������ֵ 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //��ȡ����ͼָ��
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
	
	DWORD m_rawLineAll = (pRawdataview->m_LeftListctrl).GetItemCount();//��ȡ������
	const DWORD uiGPSmodelColumn(2);
	CString tempGPSmodel;
	const DWORD uiEarthHeightColumn(1);

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

	
	
	return 0;
}


int CExtractTide::ExtractTideToArry(DWORD columnTime,DWORD columnEarthHeight)
{
	//��ȡ������ֵ 
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��	
	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
	CDataTransformDoc *pDoc = (CDataTransformDoc *) pMainFrame->GetActiveDocument(); //��ȡ�ĵ���ָ��
	
//	m_strTempArray = (pDoc->m_strTide);  //���ĵ���������ʱ������

	DWORD m_rawLineAll = (pTransdataview->m_RightListctrl)->GetItemCount();//��ȡ������
	const DWORD uiTimelColumn(0);	
	const DWORD uiEarthHeightColumn(1);
	
	//���������У�ʱ���зֱ𸳸���ͬ��vector����
	vector<double> m_vectorEarthHeight;
	vector<CString> m_vectorTime;
	m_vectorEarthHeight.clear();
	m_vectorTime.clear();

	//�������ߣ�GPSģʽ�ֱ𸳸���������
	for (DWORD tempRow = 0; tempRow < m_rawLineAll; tempRow++)
	{
		CString strTemp1, strTemp2;
		strTemp1 = (pTransdataview->m_RightListctrl)->GetItemText(tempRow,uiEarthHeightColumn);
		m_vectorEarthHeight.push_back(_tstof(strTemp1));
		strTemp2 = (pTransdataview->m_RightListctrl)->GetItemText(tempRow,uiTimelColumn);
		m_vectorTime.push_back(strTemp2);
			
	}
	//����ʱ�䣬��д��ʱ��λ�ļ�����
	vector<DWORD> m_vectorArrayIndex;
	m_vectorArrayIndex.clear();
	DWORD tempUpIndex(0); //�۲⳱λ����
	DWORD tempDownIndex(0); //�۲⳱λ����
	vector<double>::iterator m_itrEH = m_vectorEarthHeight.begin();
	vector<CString>::iterator m_itrT = m_vectorTime.begin();
	int tempTideArray[1440];
	memset(tempTideArray, 0, sizeof(tempTideArray));
	DWORD tempIndex = 0;

	//������������
	for (BOOL btemp = FALSE ; (m_itrT+tempIndex) != m_vectorTime.end(); tempIndex++)
	{
		DWORD nHour = _tstoi((*(m_itrT+tempIndex)).Mid(0,2));
		DWORD nMinute = _tstoi((*(m_itrT+tempIndex)).Mid(3,2));
		DWORD nArrayIndex = nHour *60 + nMinute -1;

		m_vectorArrayIndex.push_back(nArrayIndex);
		
		//�����޳�λ���ݵ���������
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

	//���³�λ����
	vector<DWORD>::iterator m_itrArrayIndex = m_vectorArrayIndex.begin();
	//�����й۲⳱λʱ����ڵĳ�λ�߳�
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
	//����޹۲�ʱ����ڵĳ�λ
	//��ǰ��û�۲����������Ϊ���ֵ
	for (DWORD temp(0); temp <= tempUpIndex; temp++)
	{
		tempTideArray[temp] = tempTideArray[tempUpIndex+1];
	}
	//������û�۲�ʱ��εĳ�λ��������Ϊ���ֵ
	for (DWORD temp= tempDownIndex; temp < 1440; temp++)
	{
		tempTideArray[temp] = tempTideArray[tempDownIndex-1];
	}
	
	//���ݸ��������޸ĳ�λ
	CString strtemp;
	m_textParaValue.GetWindowText(strtemp);
	int i = _tstoi(strtemp)/10;

	for (DWORD temp(0); temp < 1440; temp++)
	{
		tempTideArray[temp] -= i;
	}

	//�������µ��ĵ��е�����
	for (DWORD temp(0); temp < 1440; temp++)
	{
		strtemp.Format(_T("%d"),tempTideArray[temp]);
		pDoc->m_strTide[temp] = strtemp;
	}


	



	return 0;
}



//�����Ĵ���

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
		
		
		

	//ʱ���ַ���תʱ��
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
