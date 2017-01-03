
/*****************************************************/
//globalFunction.h,ȫ�ֺ���
/****************************************************/

//int ReadTxtFile(const CString filePath, vector< vector<CString> >& m_vectorData)
//��ȡTXT�ļ���vector������filePath���ļ��ľ���·����m_vectorData�Ǵ洢��ȡ������
int ReadTxtFile(const CString filePath, vector< vector<CString> >& m_vectorData)
{
	CString strRowData; //��ȡ��������
	CString strColumnData;//��ȡ��������
	BOOL bRead = TRUE; //���Զ�ȡ�������Ժ�ɾ��

//	LPTSTR m_filePath = filePath.GetBuffer();
	vector<CString> tempDataVector;
	vector<CString> rowDataVector;	
		
	if (bRead)
	{
		//���ļ�������������صı���m_readFile����
		CStdioFile m_readFile(filePath, CFile::typeText | CFile::modeRead);
		//���ж�ȡ�ļ�������ȡ��vector����
		while(m_readFile.ReadString(strRowData)) 
		{
			rowDataVector.push_back(strRowData);

			int m_start = 0;
			int m_offset = 0;
			TCHAR m_charFind = ','; //���Ҷ��ŷָ��������ָ�ֱ�洢��vector����
			int m_charNum = 0;

			tempDataVector.clear(); //���������
			while (m_start <= strRowData.GetLength())
			{				
				m_offset = strRowData.Find(m_charFind,m_start);	//����ƫ����			
				if (-1 != m_offset)
				{
					m_charNum = m_offset - m_start;
					tempDataVector.push_back(strRowData.Mid(m_start, m_charNum));//�洢��vector����
					m_start = m_offset + 1;
				} 
				else
				{
					m_charNum = strRowData.GetLength() - m_start;
					tempDataVector.push_back(strRowData.Mid(m_start, m_charNum));
					break;
				}				
			}
			m_vectorData.push_back(tempDataVector); 
		}
		m_readFile.Close(); //�رմ򿪵��ļ�
	} 	
	return 0;
}

/*****************************************************/
//��д�ַ����ָ�����д������Ż�������C++��д
LPTSTR GetApartString(LPTSTR lpString,DWORD*lOffset,TCHAR chMask)
{
	DWORD l(*lOffset),t(l);
	for(;lpString[t]&&lpString[t]!=chMask;++t);
	if(lpString[t]) lpString[t++] = 0;
	*lOffset = t;
	return(lpString+l);
}

/*****************************************************/
//��vector���ݲ��뵽ClistCtrl�ؼ�
int SendDataToListCtrl(CColorListCtrl& m_listctrl, vector<vector<CString> >  m_vectorData)
{
	m_listctrl.DeleteAllItems();//�ӿؼ���ɾ��������
	DWORD iMaxIndex = m_vectorData.size();	//List������Ҫ����������
	DWORD nHeadNum = m_listctrl.GetHeaderCtrl()->GetItemCount(); //��ѯList�����е����� 
	DWORD iRowIndex = m_listctrl.GetItemCount(); //��ѯList�����е�����

	DWORD iColumnIndex = 1;
	//��ѯvector�����У��е����ֵ
	vector<vector<CString> >::iterator iter_vectorData = m_vectorData.begin();		
	DWORD uiColumMaxNum(0); //�洢��������ֵ
	for(iter_vectorData = m_vectorData.begin();iter_vectorData != m_vectorData.end(); ++iter_vectorData)
	{
		if ((*iter_vectorData).size() > uiColumMaxNum)
		{
			uiColumMaxNum = (*iter_vectorData).size();
		}
	}
	//�ж��ļ��Ƿ�Ϊ�գ����費ͬ�Ĵ���ʽ
	if (uiColumMaxNum)
	{
		while(m_listctrl.DeleteColumn(0));//ɾ��������
		CString addColName;  
		for (DWORD tempColumn = 0; tempColumn != uiColumMaxNum; ++tempColumn)
		{
			addColName.Format(_T("��%d"), tempColumn);
			m_listctrl.InsertColumn(tempColumn, addColName, LVCFMT_CENTER, 50, tempColumn);
		}

		//������
		for (DWORD tempRow = 1; tempRow != (m_vectorData.size()+1); ++tempRow)
		{
			m_listctrl.InsertItem(tempRow, _T("0"));
		}
	} 
	else
	{
		MessageBox(NULL,_T("�����ݣ����������壡"),_T("����"),MB_ICONERROR|MB_OK);
		goto QUIT;
	}
	
	//�ж������Ƿ��������������������ڣ�����루�������-4�����У�����ֱ���������
	//�ַ���ASCII���ת�����⣬���д���һ�����Ż�
	/*
	DWORD uiColumNum = m_listctrl.GetHeaderCtrl()->GetItemCount(); //��ȡ����		
	if (uiColumMaxNum > uiColumNum)
	{
		char uiColNameTemp = 'D' ;
		CString addColName;  
		
		for (unsigned int tempColumn = uiColumNum; tempColumn != uiColumMaxNum; ++tempColumn)
		{
			uiColNameTemp++;
			addColName.Format(_T("%c"), uiColNameTemp);
			m_listctrl.InsertColumn(tempColumn, addColName, LVCFMT_CENTER, 50);
		}
	goto QUIT;			
	} 
	*/
	vector<vector<CString> >::size_type iRowNum = 0;	
	for (; iRowNum != m_vectorData.size(); ++iRowNum)
	{
		vector<CString>::size_type iColumNum = 0;
		for (; iColumNum != m_vectorData[iRowNum].size(); ++iColumNum)
		{
			m_listctrl.SetItemText(iRowNum, iColumNum, m_vectorData[iRowNum][iColumNum]);
		}
	}

QUIT: return 0;
}
/*****************************************************/
//���ض��ؼ����ó�ʼ������
//����Doc�ĵ��еĿؼ���ʼ������������
template <class controlClass>
int setControlPara(controlClass lpControl,vector<CString> m_vectorPara)
{

};

/*****************************************************/
//����ѡ����У������ݸ��µ�List��ͼ
int SelectDataToList(CColorListCtrl* m_listctrl, vector<CString> strSelectColum)
{
	//��ȡ����ͼ���Ը�����ʾת���������
//	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//�ĵ��л�ȡ�����ָ��
//	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //��ȡ����ͼָ��
//	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //��ȡ����ͼָ��
	////ɾ���Ҳ���ͼ�е�������
	//while(pTransdataview->m_RightListctrl->DeleteColumn(0));
	////�½��ض��С���ţ�ʱ�䣬�����򣬱����������ߣ�GPSģʽ����Ƶˮ���Ƶˮ�����������
	//const WORD iColumnNum = 9;
	//pTransdataview->m_RightListctrl->InsertColumn(0,_T("���"),LVCFMT_CENTER,30,0);
	//pTransdataview->m_RightListctrl->InsertColumn(1,_T("ʱ��"),LVCFMT_CENTER,60,1);
	//pTransdataview->m_RightListctrl->InsertColumn(2,_T("ʱ��"),LVCFMT_CENTER,60,2);
	//pTransdataview->m_RightListctrl->InsertColumn(3,_T("ʱ��"),LVCFMT_CENTER,60,3);
	//pTransdataview->m_RightListctrl->InsertColumn(4,_T("ʱ��"),LVCFMT_CENTER,60,4);
	//pTransdataview->m_RightListctrl->InsertColumn(5,_T("ʱ��"),LVCFMT_CENTER,60,5);
	//pTransdataview->m_RightListctrl->InsertColumn(6,_T("ʱ��"),LVCFMT_CENTER,60,6);
	//pTransdataview->m_RightListctrl->InsertColumn(7,_T("ʱ��"),LVCFMT_CENTER,60,7);
	//pTransdataview->m_RightListctrl->InsertColumn(8,_T("ʱ��"),LVCFMT_CENTER,60,8);
	//pTransdataview->m_RightListctrl->InsertColumn(9,_T("ʱ��"),LVCFMT_CENTER,60,9);
	


	return 0;
}

/*****************************************************/
/*****************************************************/

/*****************************************************/

/*****************************************************/

/*****************************************************/

/*****************************************************/

/*****************************************************/

/*****************************************************/

/*****************************************************/
/*****************************************************/