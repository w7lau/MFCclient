#pragma once


// Choujiang 对话框

class Choujiang : public CDialogEx
{
	DECLARE_DYNAMIC(Choujiang)

public:
	Choujiang(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Choujiang();
	struct CJData
	{
		CString ID;
		CString changci;
	};
	CJData cjdata;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
