#include<string.h>
#include"main.h"
void StrCpy(char* &des, char* src)
{
	int len = strlen(src);
	des = new char[len];
	strcpy_s(des, len + 1, src);
}
