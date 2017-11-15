#pragma once
#include <tchar.h>
#include <list>
#include <string>
#include<fstream>
#include <io.h>
#include<Windows.h>
using namespace std;
BOOL ShellRun(char* csExe, char* csParam, DWORD nShow);

int FileTraverse(string path, bool recursive, list<string> &fileList);

int FileStream(char* fileName, list<string> listFile);

int ConnectServer(list<char *> ips, int port);

int InjectDll(const char *lpszDll, const DWORD dwProcessID);

int EnumProcessUserName(list<DWORD> &processes);

DWORD FindProcess(LPCTSTR lpszProcess);

BOOL IsRunAsAdmin();

void StrCpy(char* &des, char* src);

void ExportResFile(string strExportPath, UINT Resource, char* type);