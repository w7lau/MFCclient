// clientDLL.cpp : 定义 DLL 应用程序的导出函数。

#include "stdafx.h"
#pragma once
#ifndef CLIENTDLL_CPP_
#define CLIENTDLL_CPP_

#include <iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<Windows.h>
#include<string>
#include<thread>
#include<vector>
#include<fstream>
#include <codecvt>
#define CONNECT_NUM_MAX 10
#define SEND_MAX 252
#define STRUCT_MAX 252


#pragma comment(lib,"ws2_32.lib")
using namespace std;
extern string stk;
extern string sendcommd;
extern string ID_name;
extern string who_behaviour;
extern vector<string> list_name;
class Read_server
{
private:
	//static const char* connect_IP = "207.246.127.207";
	enum sendwhat{_sendcommd=0,_ID_name=1,_who_behaviour=2};
	
public:
	
	static string utf8_to_gbk(const string &str)
	{
		wstring_convert<codecvt_utf8<wchar_t>> utf8_cvt; // utf8-》unicode转换器
		wstring_convert<codecvt<wchar_t, char, mbstate_t>> gbk_cvt(new codecvt<wchar_t, char, mbstate_t>("chs")); // unicode-》gbk转换器
		wstring t;
		try
		{
			t = utf8_cvt.from_bytes(str);
		}
		catch(...)
		{
			return "此处发生了未知错误";
		}
		
		return gbk_cvt.to_bytes(t);
	}

	// gbk转utf8
	static string gbk_to_utf8(const string &str)
	{
		wstring_convert<codecvt_utf8<wchar_t>> utf8_cvt; // utf8-》unicode转换器
		wstring_convert<codecvt<wchar_t, char, mbstate_t>> gbk_cvt(new codecvt<wchar_t, char, mbstate_t>("chs")); // unicode-》gbk转换器
		wstring t = gbk_cvt.from_bytes(str);
		return utf8_cvt.to_bytes(t);
	}
	static wstring string2wstring(string str)
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

	struct lData
	{
		char name[SEND_MAX] = { 0 };
		int time = 0;
	};

	struct sData
	{
		char name[SEND_MAX] = { 0 };
		int num = 0;
	};
	static void Writemsg(sData sendd, SOCKET sock_c, string zl = "请输入指令：",int sendwhat=_sendcommd)
	{
		string ta;
		cout << zl;
		cin >> ta;
		//cout << gbk_to_utf8(ta) << endl;
		if (sendwhat == _sendcommd)
		{
			strcpy_s(sendd.name, gbk_to_utf8(sendcommd).c_str());
			if(sendcommd=="")
			{
				return;
			}
		}
		else if (sendwhat == _ID_name)
		{
			strcpy_s(sendd.name, gbk_to_utf8(ID_name).c_str());
		}
		else if (sendwhat == _who_behaviour)
		{
			strcpy_s(sendd.name, gbk_to_utf8(who_behaviour).c_str());
		}
		//cout << "发送：" << ta << endl;
		send(sock_c, (char*)&sendd, sizeof(sendd), 0);
	}
	static void T_x()
	{

		WORD ver = MAKEWORD(2, 2);
		WSADATA dat;
		WSAStartup(ver, &dat);

		SOCKET sock_c = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


		SOCKADDR_IN addrSrv;
		//addrSrv.sin_addr.S_un.S_addr = inet_addr(connect_IP);
		//inet_pton(AF_INET, "207.246.127.207", (void*)&addrSrv.sin_addr.S_un.S_addr);
		InetPton(AF_INET, _T("207.246.127.207"), (void*)&addrSrv.sin_addr.S_un.S_addr);
		addrSrv.sin_family = AF_INET;
		addrSrv.sin_port = htons(6000);

		//绑定
		if (0 != connect(sock_c, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))
		{
			std::cout << "连接失败……" << std::endl;
			//cout << "可能卡了，重新开一下，可能被墙了，可能服务器没话费了" << endl;
			stk = "可能卡了，重新开一下，可能被墙了，可能服务器没话费了";
			return;
		}
		else
		{
			std::cout << "连接成功……" << std::endl;
			if (sendcommd == "")
			{
				sData sendd = { "_connect_",9 };
				send(sock_c, (char*)&sendd, sizeof(sendd), 0);
			}
			else
			{
				sData sendd = { " ",3 };
				Writemsg(sendd, sock_c);
			}


		}
		int i = 0;
		int kk = 1;
		while (kk>0)
		{
			sData recd{};
			//cout << "i0:" << i << endl;
			i = recv(sock_c, (char*)&recd, sizeof(recd), 0);
			while (i > 0)
			{
				//cout <<"i1:"<< i<<endl;
				//cout << "ID：" << utf8_to_gbk(recd.name) << endl;
				//cout << "ID：" << utf8_to_gbk(recd.name) << "  死亡次数：" << recd.num << endl;
				sData sendd = { " ",3 };
				string strrecname = utf8_to_gbk(recd.name);
				if (strrecname == "连接服务器成功………………")
				{
					//cout << "当前可以使用指令：list、read、write" << endl;
					//cout << utf8_to_gbk(recd.name) << endl;
					stk = utf8_to_gbk(recd.name);
					stk += "\n";
					stk += "剩下的罚款抽奖池会在5.0之前弄好，为了让我们有钱花！\n至于自动更新和美化……会弄的会弄的（有生之年）";
					//wstring temp = string2wstring(utf8_to_gbk(recd.name));
					//k = temp.c_str();
					//return;
					Writemsg(sendd, sock_c);
					i = 0;
					return;
				}
				else if (strrecname == "List_begining")
				{
					//char recv_buf[1024] = "";
					Sleep(1000);
					stk = "";
					list_name.clear();
					i = recv(sock_c, (char*)&recd, sizeof(recd), 0);
					//cout << "text：" << utf8_to_gbk(recd.name) << "  number：" << recd.num << endl;
					//i = recv(sock_c, recv_buf, sizeof(recv_buf), 0);
					while (i > 0)
					{
						//ofstream ofs("log.txt");
						string tempname1 = utf8_to_gbk(recd.name);
						//ofs << tempname1 << endl;
						if (tempname1 == "List_ending"|| tempname1 == "此处发生了未知错误")
						{
							//cout << "ID：" << utf8_to_gbk(recd.name) << "  死亡次数：" << recd.num << endl;
							i = 0;
							return;
							Writemsg(sendd, sock_c);
							//cout << "here" << endl;
							break;
						}
						else
						{
							list_name.push_back(tempname1);
							//ofs << "ID：" << tempname1 << "  犯罪次数：" << recd.num << endl;
							stk += "ID：";
							stk += tempname1;
							stk += "  犯罪次数：";
							string strn=to_string(recd.num);
							stk += strn;
							stk += "\n";
							i = recv(sock_c, (char*)&recd, sizeof(recd), 0);
						}
					}


				}
				else if (strrecname == "Name_begining")
				{
					Writemsg(sendd, sock_c, "请输入要查看的ID：", 1);
					Sleep(1000);
					i = recv(sock_c, (char*)&recd, sizeof(recd), 0);
					stk = "";
					while (i > 0)
					{
						if (utf8_to_gbk(recd.name) == "Name_ending")
						{
							i = 0;
							kk = 0;
							return;
							Writemsg(sendd, sock_c);
							//cout << "here111" << endl;
							break;
						}
						else
						{
							//char t1=''
							string sss = utf8_to_gbk(recd.name);
							for (int i = 0; i < sss.length(); i++)
							{
								if (sss[i] == '_')
								{
									sss[i] = ' ';
								}
							}
							//cout << "时间：" << sss;
							stk += "时间：";
							stk += sss;
							i = recv(sock_c, (char*)&recd, sizeof(recd), 0);
							//cout << "\t罪行：" << utf8_to_gbk(recd.name) << endl;
							stk += "\t罪行：";
							stk += utf8_to_gbk(recd.name);
							stk += "\n";
							i = recv(sock_c, (char*)&recd, sizeof(recd), 0);
						}
					}

				}
				else if (strrecname == "Write_begining")
				{
					//cout << "text：" << utf8_to_gbk(recd.name) << "  number：" << recd.num << endl;
					Writemsg(sendd, sock_c, "请输入要记录的ID：",1);
					Sleep(1000);
					recv(sock_c, (char*)&recd, sizeof(recd), 0);
					while (utf8_to_gbk(recd.name) != "Write_midding")
					{
						recv(sock_c, (char*)&recd, sizeof(recd), 0);
					}
					//cout << "text：" << utf8_to_gbk(recd.name) << "  number：" << recd.num << endl;
					Writemsg(sendd, sock_c, "请输入要记录的罪行：",2);
					cout << "记录成功" << endl;
					return;
					//i = recv(sock_c, (char*)&recd, sizeof(recd), 0);
				}
				else
				{
					//cout << "name：" << utf8_to_gbk(recd.name) << "  num：" << recd.num << endl;
					stk = strrecname;
					if (sendcommd == "")
					{
						kk = 0;
					}
					Writemsg(sendd, sock_c);
					i = 0;
				}

				//cout << "接收到消息：" << recd.name << endl;

				//cout << "i2:" << i << endl;
			}
		}
		WSACleanup();
		closesocket(sock_c);
	}
	void testa(LPCTSTR &aa)
	{
		//aa=_T("暗示法暗示法暗示的");

	}
	Read_server()
	{

		//char recvBuf[100];
		//recv(sock_c, recvBuf, sizeof(recvBuf), 0);
		//cout << "接收到消息："<<recvBuf << endl;

		//char sendBuf[100];
		//strcpy_s(sendBuf, "aaaaaa");
		//cout << "发送：" << sendBuf << endl;
		//send(sock_c, sendBuf, strlen(sendBuf) + 1, 0);

		//cout << "自动化的功能算法问题好麻烦，先当一个云公用记事本用着吧，其他的以后再说吧……" << endl;
		//cout << "还有好多细节暂时懒得弄了，例如如果发一半发现卡着不动了，可能卡住了，没写重连，重启吧，重连以后再说……" << endl;
		//thread *T = new thread(T_x);
		//T->join();
		//T->detach();
		//T_x();
		//recv(sock_c, (char*)&recd, sizeof(recd), 0);
		//cout << "接收到消息：" << utf8_to_gbk(recd.name) << endl;


		//WSACleanup();
	}




};

#endif // !1


