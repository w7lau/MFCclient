// Choujiang.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCclient.h"
#include "Choujiang.h"
#include "afxdialogex.h"


// Choujiang 对话框

IMPLEMENT_DYNAMIC(Choujiang, CDialogEx)

Choujiang::Choujiang(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Choujiang::~Choujiang()
{
}

void Choujiang::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Choujiang, CDialogEx)
	ON_BN_CLICKED(IDOK, &Choujiang::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Choujiang::OnBnClickedButton1)
END_MESSAGE_MAP()


// Choujiang 消息处理程序


void Choujiang::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemTextW(IDC_RICHEDIT21, cjdata.ID);
	GetDlgItemTextW(IDC_RICHEDIT22, cjdata.changci);
	CDialogEx::OnOK();
}


void Choujiang::OnBnClickedButton1()
{
	CDialogEx::OnOK();
	// TODO: 在此添加控件通知处理程序代码
}
