#include"main.h"
using namespace std;
int InjectDll(const char *lpszDll, const DWORD dwProcessID)
{
	if ((_access(lpszDll, 0)) == -1)
	{
		return 0;
	}
	// 打开目标进程  
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE, FALSE, dwProcessID);
	if (hProcess == NULL)
	{
		return 0;
	}
	// 向目标进程地址空间写入DLL名称  
	DWORD dwSize;
	SIZE_T	dwWritten;
	dwSize = lstrlenA(lpszDll) + 1;
	LPVOID lpBuf = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (NULL == lpBuf)
	{
		CloseHandle(hProcess);
		// 失败处理  
		return 0;
	}
	if (WriteProcessMemory(hProcess, lpBuf, (LPVOID)lpszDll, dwSize, &dwWritten))
	{
		// 要写入字节数与实际写入字节数不相等，仍属失败  
		if (dwWritten != dwSize)
		{
			VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
			CloseHandle(hProcess);
			// 失败处理  
			return 0;
		}
	}
	else
	{
		CloseHandle(hProcess);
		// 失败处理  
		return 0;
	}
	// 使目标进程调用LoadLibrary，加载DLL  
	DWORD dwID;
	LPVOID pFunc = LoadLibraryA;
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0,
		(LPTHREAD_START_ROUTINE)pFunc, lpBuf, 0, &dwID);
	if (hThread == NULL || dwID == NULL)
	{
		return 0;
	}
	// 等待LoadLibrary加载完毕  
	//WaitForSingleObject(hThread, INFINITE);
	// 释放目标进程中申请的空间  
	//VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
	CloseHandle(hThread);
	CloseHandle(hProcess);
	return 1;
}

void UnInjectDll(char *szDllName, DWORD dwPid)
{
	// 使目标进程调用GetModuleHandle，获得DLL在目标进程中的句柄  
	DWORD dwHandle;
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	LPVOID pFunc = GetModuleHandleA;
	char lpBuf[MAXBYTE];
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0,
		(LPTHREAD_START_ROUTINE)pFunc, lpBuf, 0, &dwPid);

	// 等待GetModuleHandle运行完毕  
	WaitForSingleObject(hThread, INFINITE);

	// 获得GetModuleHandle的返回值  
	GetExitCodeThread(hThread, &dwHandle);

	// 释放目标进程中申请的空间  
	int dwSize = strlen(szDllName) + sizeof(char);
	VirtualFreeEx(hProcess, lpBuf, dwSize, MEM_DECOMMIT);
	CloseHandle(hThread);

	// 使目标进程调用FreeLibrary，卸载DLL  
	pFunc = FreeLibrary;
	hThread = CreateRemoteThread(hProcess, NULL, 0,
		(LPTHREAD_START_ROUTINE)pFunc, (LPVOID)dwHandle, 0, &dwPid);

	// 等待FreeLibrary卸载完毕  
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hProcess);
}
//*****************************************************************************************************************************