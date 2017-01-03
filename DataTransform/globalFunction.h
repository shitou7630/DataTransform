
/*****************************************************/
//globalFunction.h,全局函数
/****************************************************/

//int ReadTxtFile(const CString filePath, vector< vector<CString> >& m_vectorData)
//读取TXT文件到vector容器，filePath是文件的绝对路径，m_vectorData是存储读取的容器
int ReadTxtFile(const CString filePath, vector< vector<CString> >& m_vectorData)
{
	CString strRowData; //读取的行数据
	CString strColumnData;//读取的列数据
	BOOL bRead = TRUE; //调试读取函数，以后删除

//	LPTSTR m_filePath = filePath.GetBuffer();
	vector<CString> tempDataVector;
	vector<CString> rowDataVector;	
		
	if (bRead)
	{
		//打开文件，并将其与相关的变量m_readFile关联
		CStdioFile m_readFile(filePath, CFile::typeText | CFile::modeRead);
		//逐行读取文件，并存取到vector容器
		while(m_readFile.ReadString(strRowData)) 
		{
			rowDataVector.push_back(strRowData);

			int m_start = 0;
			int m_offset = 0;
			TCHAR m_charFind = ','; //查找逗号分割符，将其分割分别存储到vector容器
			int m_charNum = 0;

			tempDataVector.clear(); //将容器清空
			while (m_start <= strRowData.GetLength())
			{				
				m_offset = strRowData.Find(m_charFind,m_start);	//搜索偏移量			
				if (-1 != m_offset)
				{
					m_charNum = m_offset - m_start;
					tempDataVector.push_back(strRowData.Mid(m_start, m_charNum));//存储到vector容器
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
		m_readFile.Close(); //关闭打开的文件
	} 	
	return 0;
}

/*****************************************************/
//自写字符串分割函数，有待测试优化，利用C++编写
LPTSTR GetApartString(LPTSTR lpString,DWORD*lOffset,TCHAR chMask)
{
	DWORD l(*lOffset),t(l);
	for(;lpString[t]&&lpString[t]!=chMask;++t);
	if(lpString[t]) lpString[t++] = 0;
	*lOffset = t;
	return(lpString+l);
}

/*****************************************************/
//将vector数据插入到ClistCtrl控件
int SendDataToListCtrl(CColorListCtrl& m_listctrl, vector<vector<CString> >  m_vectorData)
{
	m_listctrl.DeleteAllItems();//从控件中删除所有项
	DWORD iMaxIndex = m_vectorData.size();	//List中所需要的行数计算
	DWORD nHeadNum = m_listctrl.GetHeaderCtrl()->GetItemCount(); //查询List中现有的列数 
	DWORD iRowIndex = m_listctrl.GetItemCount(); //查询List中现有的行数

	DWORD iColumnIndex = 1;
	//查询vector容器中，列的最大值
	vector<vector<CString> >::iterator iter_vectorData = m_vectorData.begin();		
	DWORD uiColumMaxNum(0); //存储最大的列数值
	for(iter_vectorData = m_vectorData.begin();iter_vectorData != m_vectorData.end(); ++iter_vectorData)
	{
		if ((*iter_vectorData).size() > uiColumMaxNum)
		{
			uiColumMaxNum = (*iter_vectorData).size();
		}
	}
	//判断文件是否为空，给予不同的处理方式
	if (uiColumMaxNum)
	{
		while(m_listctrl.DeleteColumn(0));//删除所有列
		CString addColName;  
		for (DWORD tempColumn = 0; tempColumn != uiColumMaxNum; ++tempColumn)
		{
			addColName.Format(_T("列%d"), tempColumn);
			m_listctrl.InsertColumn(tempColumn, addColName, LVCFMT_CENTER, 50, tempColumn);
		}

		//插入行
		for (DWORD tempRow = 1; tempRow != (m_vectorData.size()+1); ++tempRow)
		{
			m_listctrl.InsertItem(tempRow, _T("0"));
		}
	} 
	else
	{
		MessageBox(NULL,_T("空数据，处理无意义！"),_T("警告"),MB_ICONERROR|MB_OK);
		goto QUIT;
	}
	
	//判断列数是否大于现有列数，如果大于，则插入（最大列数-4）个列，否则，直接填充数据
	//字符与ASCII码的转换问题，还有待进一步的优化
	/*
	DWORD uiColumNum = m_listctrl.GetHeaderCtrl()->GetItemCount(); //获取列数		
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
//给特定控件设置初始化变量
//用于Doc文档中的控件初始化及参数设置
template <class controlClass>
int setControlPara(controlClass lpControl,vector<CString> m_vectorPara)
{

};

/*****************************************************/
//基于选择的列，将数据更新到List视图
int SelectDataToList(CColorListCtrl* m_listctrl, vector<CString> strSelectColum)
{
	//获取右视图，以更新显示转换后的数据
//	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();//文档中获取主框架指针
//	CRawDataView* pRawdataview = (CRawDataView*)(pMainFrame->m_wndSplitter.GetPane(0,0)); //获取左视图指针
//	CTransDataView* pTransdataview = (CTransDataView*)(pMainFrame->m_wndSplitter.GetPane(0,1)); //获取右视图指针
	////删除右侧视图中的所有列
	//while(pTransdataview->m_RightListctrl->DeleteColumn(0));
	////新建特定列“点号，时间，东方向，北方向，正常高，GPS模式，高频水深，低频水深，改正常数”
	//const WORD iColumnNum = 9;
	//pTransdataview->m_RightListctrl->InsertColumn(0,_T("点号"),LVCFMT_CENTER,30,0);
	//pTransdataview->m_RightListctrl->InsertColumn(1,_T("时间"),LVCFMT_CENTER,60,1);
	//pTransdataview->m_RightListctrl->InsertColumn(2,_T("时间"),LVCFMT_CENTER,60,2);
	//pTransdataview->m_RightListctrl->InsertColumn(3,_T("时间"),LVCFMT_CENTER,60,3);
	//pTransdataview->m_RightListctrl->InsertColumn(4,_T("时间"),LVCFMT_CENTER,60,4);
	//pTransdataview->m_RightListctrl->InsertColumn(5,_T("时间"),LVCFMT_CENTER,60,5);
	//pTransdataview->m_RightListctrl->InsertColumn(6,_T("时间"),LVCFMT_CENTER,60,6);
	//pTransdataview->m_RightListctrl->InsertColumn(7,_T("时间"),LVCFMT_CENTER,60,7);
	//pTransdataview->m_RightListctrl->InsertColumn(8,_T("时间"),LVCFMT_CENTER,60,8);
	//pTransdataview->m_RightListctrl->InsertColumn(9,_T("时间"),LVCFMT_CENTER,60,9);
	


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