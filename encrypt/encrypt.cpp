// encrypt.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "encrypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;


void generateRandXorList()
{
	BYTE buf[256];

	::srand(::time(0));

	for (int i=0; i<256; i++)
		buf[i] = i;

	for (int i=0; i<256; i++)
	{
		int idx = rand() & 0xff;
		BYTE tmp = buf[idx];
		buf[idx] = buf[i];
		buf[i] = tmp;
	}

	char str[256];

	// 编码缓冲
	for (int i=0; i<256; i++)
	{
		if ((i & 15) == 0)
			cout << endl;

		sprintf(str, "0x%02X,", buf[i]);
		cout << str;
	}
	
	cout << endl << endl << endl << endl;

	// 解码缓冲
	for (int i=0; i<256; i++)
	{
		for (int j=0; j<256; j++)
		{
			if (buf[j] == i)
			{
				if ((i & 15) == 0)
					cout << endl;
				sprintf(str, "0x%02X,", j);
				cout << str;
			}
		}
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		DWORD dwPacketKey = 0x6A45F24D;
		DWORD m_dwPacketKey = ((dwPacketKey>>16)|((dwPacketKey&0xFFFF)<<16)^dwPacketKey);
		generateRandXorList();
	}

	system(_T("pause"));

	return nRetCode;
}
