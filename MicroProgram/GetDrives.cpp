#include"main.h"
//��PULARGE_INTEGER���͵��ֽ�(B)��ת��Ϊ(GB)��λ
#define GB(x) (x.HighPart << 2) + (x.LowPart >> 20) / 1024.0
int GetDrives()
{
	return 1;
}