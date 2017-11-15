#include"main.h"
int FileStream(char* fileName, list<string> listFile)
{
	ofstream ofile;
	ofile.open(fileName);
	list<string>::reverse_iterator ir;
	for (ir = listFile.rbegin(); ir != listFile.rend(); ir++) {
		ofile << *ir << endl;
	}
	ofile.close();
	return 1;
}
