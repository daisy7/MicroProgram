#include"resource.h"
#include"main.h"
void ExportResFile(string strExportPath,UINT Resource,char* type)
{
	HRSRC hrSrcSys = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL1), _T(type));
	HGLOBAL hGlobalSys = LoadResource(NULL, hrSrcSys);
	LPVOID lpGlobalSys = LockResource(hGlobalSys);

	//char * buffer;
	//long size;
	//ifstream in("f:/XXYY.zip", ios::in | ios::binary | ios::ate);
	//size = in.tellg();
	//in.seekg(0, ios::beg);
	//buffer = new char[size];
	//in.read(buffer, size);
	//in.close();

	ofstream out(strExportPath, ios::out | ios::binary | ios::ate);
	out.write((char*)lpGlobalSys, (UINT)SizeofResource(NULL, hrSrcSys));
	out.close();

	UnlockResource(hGlobalSys);
	FreeResource(hGlobalSys);
}