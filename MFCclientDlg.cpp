
// MFCclientDlg.cpp: 实现文件
//


#include "stdafx.h"
#include"clientDLL.cpp"
#include "MFCclient.h"
#include "MFCclientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCclientDlg 对话框

string stk = "";
string sendcommd = "";
string ID_name = "";
string who_behaviour = "";
vector<string> list_name;
wstring string2wstring(string str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}


CMFCclientDlg::CMFCclientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CMFCclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, cbox1);
	DDX_Control(pDX, IDC_RICHEDIT22, richedit2);
}

BEGIN_MESSAGE_MAP(CMFCclientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCclientDlg::OnBnClickedButton1)

	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCclientDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCclientDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_RICHEDIT21, &CMFCclientDlg::OnEnChangeRichedit21)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCclientDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCclientDlg 消息处理程序

BOOL CMFCclientDlg::OnInitDialog()
{
	Read_server rs;
	rs.T_x();
	LPCTSTR k = _T("");
	wstring temp = string2wstring(stk);
	k = temp.c_str();
	SetDlgItemTextW(IDC_RICHEDIT21, k);
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCclientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//IDC_STATIC.caption = "bbb";
	//SetDlgItemText(IDC_STATIC, _T("哈哈哈哈"));
	sendcommd = "list";
	Read_server rs;
	rs.T_x();
	LPCTSTR k = _T("");
	wstring temp = string2wstring(stk);
	k = temp.c_str();
	SetDlgItemTextW(IDC_RICHEDIT21, k);
	cbox1.ResetContent();
	for (auto it = list_name.begin(); it != list_name.end(); it++)
	{
		temp = string2wstring(*it);
		k = temp.c_str();
		cbox1.AddString(k);
	}
	SetDlgItemTextW(IDC_BUTTON1, _T("刷新"));
	SetDlgItemTextW(IDC_BUTTON2, _T("查看"));
}
void CMFCclientDlg::OnEnChangeRichedit21() 
{
}
void CMFCclientDlg::OnBnClickedButton2()
{
	int cul = cbox1.GetCurSel();
	CString temp1;
	cbox1.GetLBText(cul, temp1);
	ID_name = (CStringA)temp1;
	sendcommd = "read";
	//sendcommd.assign(ws.begin(), ws.end());
	Read_server rs;
	rs.T_x();
	LPCTSTR k = _T("");
	wstring temp = string2wstring(stk);
	k = temp.c_str();
	SetDlgItemTextW(IDC_RICHEDIT21, k);
	SetDlgItemTextW(IDC_BUTTON1, _T("总列表"));
	SetDlgItemTextW(IDC_BUTTON2, _T("刷新"));
}
void CMFCclientDlg::OnCbnSelchangeCombo1()
{
	int cul = cbox1.GetCurSel();
	CString temp1;
	ID_name = (CStringA)temp1;
	cbox1.GetLBText(cul, temp1);
	SetDlgItemTextW(IDC_RICHEDIT22, CString(temp1));
}

void CMFCclientDlg::OnBnClickedButton4()
{
	CString temp;
	GetDlgItemTextW(IDC_RICHEDIT23,temp);
	who_behaviour = (CStringA)temp;
	sendcommd = "write";
	GetDlgItemTextW(IDC_RICHEDIT22, temp);
	ID_name= (CStringA)temp;
	Read_server rs;
	rs.T_x();
	//AfxMessageBox(_T("记录成功！了吧？"),_T("我好烦，我不想弄"));
	::MessageBox(NULL, _T("记录成功！了吧？"), _T("不想弄"), MB_SYSTEMMODAL|MB_OK);
	// TODO: 在此添加控件通知处理程序代码
}
