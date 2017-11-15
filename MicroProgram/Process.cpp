#include"main.h"
#include<tlhelp32.h>
#include <WtsApi32.h>
#pragma comment( lib, "Wtsapi32.lib" )
int EnumProcessUserName(list<DWORD> &processes)
{
	DWORD               dwCount = 0;
	PWTS_PROCESS_INFO   pi = { 0 };
	int                 i = 0;
	DWORD               dwSize = 0;
	char                username[128] = { 0 };
	SID_NAME_USE        nameuse = SidTypeUser;
	printf("Pid\tProcess Name\t\t\tSession\tUser Name\r\n");

	if (WTSEnumerateProcesses(NULL, 0, 1, &pi, &dwCount))
	{
		int j = 0;
		for (i = 0; i < dwCount; i++)
		{
			memset(username, 0, sizeof(char) * 128);
			dwSize = 128;
			if (LookupAccountSid(NULL, pi[i].pUserSid, username, &dwSize, NULL, &dwSize, &nameuse))
			{
				printf("%.4d\t%s\t\t\t\t%.4d\t%s\r\n",
					pi[i].ProcessId,
					pi[i].pProcessName,
					pi[i].SessionId,
					username);
				processes.push_front(pi[i].ProcessId);
			}
			else {
				/*printf("%.4d\t%s\t\t\t\t%.4d\tUnkonw\r\n",
				pi[i].ProcessId,
				pi[i].pProcessName,
				pi[i].SessionId);*/
			}
		}
	}
	else
	{
		return -1;
	}
	WTSFreeMemory(pi);
	return 1;
}
DWORD FindProcess(LPCTSTR lpszProcess)
{
	DWORD processId = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe32);
	do
	{
		if (lstrcmpi(pe32.szExeFile, lpszProcess) == 0)
		{
			processId = pe32.th32ProcessID;
			break;
		}
	} while (Process32Next(hSnapshot, &pe32));
	CloseHandle(hSnapshot);
	return processId;
}