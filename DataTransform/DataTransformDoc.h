
// DataTransformDoc.h : CDataTransformDoc 类的接口
//
#include <vector>
using namespace std;

#pragma once


class CDataTransformDoc : public CDocument
{
protected: // 仅从序列化创建
	CDataTransformDoc();
	DECLARE_DYNCREATE(CDataTransformDoc)

// 特性
public:
	vector< vector<CString> >  m_vectorRawData;//数据输入文件的存储
	vector< vector<CString> >  m_vectorNoTideCorrect;//数据输入文件的存储

// 操作
public:


// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CDataTransformDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen();
	afx_msg void OnEditNotidecorrect();
	afx_msg void OnSaveCassformat();
	afx_msg void OnExtracttide();

public:
	CString m_strTide[1440];//潮位文件保存
	afx_msg void OnSavetidefile();
};
