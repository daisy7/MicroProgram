#include <iostream>  
#include <io.h>
#include"main.h"
//_A_ARCH(存档)，_A_SUBDIR(文件夹)，_A_HIDDEN(隐藏)，_A_SYSTEM(系统)，_A_NORMAL(正常)，_A_RDONLY(只读)
//遍历当前目录下的文件夹和文件,默认是按字母顺序遍历
int FileTraverse(string path, bool recursive, list<string> &fileList)
{
	_finddata_t file_info;
	string current_path = path + "/*.*"; //也可以用/*来匹配所有  
	int handle = _findfirst(current_path.c_str(), &file_info);
	//返回值为-1则查找失败  
	if (-1 == handle)
	{
		return -1;
	}
	do
	{
		//判断是否子目录  
		if (file_info.attrib == _A_SUBDIR)
		{
			if (strcmp(file_info.name, ".") == 0 || strcmp(file_info.name, "..") == 0)
				continue;
			//递归遍历子目录  
			//打印记号反映出深度层次  
			if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0 && recursive)  //.是当前目录，..是上层目录，必须排除掉这两种情况
				FileTraverse(path + '/' + file_info.name, recursive, fileList); //再windows下可以用\\转义分隔符，不推荐
		}
		else
		{
			fileList.push_front(path + '/' + file_info.name);
		}
	} while (!_findnext(handle, &file_info));//返回0则遍历完  
//关闭文件句柄
	_findclose(handle);
	return 1;
}
int FileTraversePrint(string path, int layer, bool recursive)
{
	_finddata_t file_info;
	string current_path = path + "/*.*"; //也可以用/*来匹配所有  
	int handle = _findfirst(current_path.c_str(), &file_info);
	//返回值为-1则查找失败  
	if (-1 == handle)
	{
		cout << "cannot match the path" << endl;
		return -1;
	}
	do
	{
		//判断是否子目录  
		if (file_info.attrib == _A_SUBDIR)
		{
			if (strcmp(file_info.name, ".") == 0 || strcmp(file_info.name, "..") == 0)
				continue;
			//递归遍历子目录  
			//打印记号反映出深度层次  
			for (int i = 0; i < layer; i++)
				cout << "--";
			cout << file_info.name << endl;
			int layer_tmp = layer;
			if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0 && recursive)  //.是当前目录，..是上层目录，必须排除掉这两种情况
				FileTraversePrint(path + '/' + file_info.name, layer_tmp + 1, recursive); //再windows下可以用\\转义分隔符，不推荐
		}
		else
		{
			//打印记号反映出深度层次
			for (int i = 0; i < layer; i++)
				cout << "--";
			cout << file_info.name << endl;
		}
	} while (!_findnext(handle, &file_info));//返回0则遍历完  
	_findclose(handle);//关闭文件句柄
	return 1;
}