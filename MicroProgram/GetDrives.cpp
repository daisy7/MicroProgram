#include"main.h"
//将PULARGE_INTEGER类型的字节(B)数转化为(GB)单位
#define GB(x) (x.HighPart << 2) + (x.LowPart >> 20) / 1024.0
int GetDrives()
{
	return 1;
}