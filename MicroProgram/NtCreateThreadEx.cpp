#include"main.h"
using namespace std;
int InjectDll(const char *lpszDll, const DWORD dwProcessID)
{
	if ((_access(lpszDll, 0)) == -1)
	{
		return 0;
	}
	// ��Ŀ�����  
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE, FALSE, dwProcessID);
	if (hProcess == NULL)
	{
		return 0;
	}
	// ��Ŀ����̵�ַ�ռ�д��DLL����  
	DWORD dwSize;
	SIZE_T	dwWritten;
	dwSize = lstrlenA(lpszDll) + 1;
	LPVOID lpBuf = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (NULL == lpBuf)
	{
		CloseHandle(hProcess);
		// ʧ�ܴ���  
		return 0;
	}
	if (WriteProcessMemory(hProcess, lpBuf, (LPVOID)lpszDll, dwSize, &dwWritten))
	{
		// Ҫд���ֽ�����ʵ��д���ֽ�������ȣ�����ʧ��  
		if (dwWritten != dwSize)
		{
			VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
			CloseHandle(hProcess);
			// ʧ�ܴ���  
			return 0;
		}
	}
	else
	{
		CloseHandle(hProcess);
		// ʧ�ܴ���  
		return 0;
	}
	// ʹĿ����̵���LoadLibrary������DLL  
	DWORD dwID;
	LPVOID pFunc = LoadLibraryA;
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0,
		(LPTHREAD_START_ROUTINE)pFunc, lpBuf, 0, &dwID);
	if (hThread == NULL || dwID == NULL)
	{
		return 0;
	}
	// �ȴ�LoadLibrary�������  
	//WaitForSingleObject(hThread, INFINITE);
	// �ͷ�Ŀ�����������Ŀռ�  
	//VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
	CloseHandle(hThread);
	CloseHandle(hProcess);
	return 1;
}

void UnInjectDll(char *szDllName, DWORD dwPid)
{
	// ʹĿ����̵���GetModuleHandle�����DLL��Ŀ������еľ��  
	DWORD dwHandle;
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	LPVOID pFunc = GetModuleHandleA;
	char lpBuf[MAXBYTE];
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0,
		(LPTHREAD_START_ROUTINE)pFunc, lpBuf, 0, &dwPid);

	// �ȴ�GetModuleHandle�������  
	WaitForSingleObject(hThread, INFINITE);

	// ���GetModuleHandle�ķ���ֵ  
	GetExitCodeThread(hThread, &dwHandle);

	// �ͷ�Ŀ�����������Ŀռ�  
	int dwSize = strlen(szDllName) + sizeof(char);
	VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
	CloseHandle(hThread);

	// ʹĿ����̵���FreeLibrary��ж��DLL  
	pFunc = FreeLibrary;
	hThread = CreateRemoteThread(hProcess, NULL, 0,
		(LPTHREAD_START_ROUTINE)pFunc, (LPVOID)dwHandle, 0, &dwPid);

	// �ȴ�FreeLibraryж�����  
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hProcess);
}
//*****************************************************************************************************************************