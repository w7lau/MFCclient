
// MFCclientDlg.h: 头文件
//

#pragma once


// CMFCclientDlg 对话框
class CMFCclientDlg : public CDialogEx
{
// 构造
public:
	CMFCclientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnEnChangeRichedit22();
	afx_msg void OnStnClickedStatic3();
	afx_msg void OnEnChangeRichedit23();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeRichedit21();
	CComboBox cbox1;
	CRichEditCtrl richedit2;
	afx_msg void OnBnClickedButton4();
};
