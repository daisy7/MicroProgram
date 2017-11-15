#include <iostream>  
#include <io.h>
#include"main.h"
//_A_ARCH(�浵)��_A_SUBDIR(�ļ���)��_A_HIDDEN(����)��_A_SYSTEM(ϵͳ)��_A_NORMAL(����)��_A_RDONLY(ֻ��)
//������ǰĿ¼�µ��ļ��к��ļ�,Ĭ���ǰ���ĸ˳�����
int FileTraverse(string path, bool recursive, list<string> &fileList)
{
	_finddata_t file_info;
	string current_path = path + "/*.*"; //Ҳ������/*��ƥ������  
	int handle = _findfirst(current_path.c_str(), &file_info);
	//����ֵΪ-1�����ʧ��  
	if (-1 == handle)
	{
		return -1;
	}
	do
	{
		//�ж��Ƿ���Ŀ¼  
		if (file_info.attrib == _A_SUBDIR)
		{
			if (strcmp(file_info.name, ".") == 0 || strcmp(file_info.name, "..") == 0)
				continue;
			//�ݹ������Ŀ¼  
			//��ӡ�Ǻŷ�ӳ����Ȳ��  
			if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0 && recursive)  //.�ǵ�ǰĿ¼��..���ϲ�Ŀ¼�������ų������������
				FileTraverse(path + '/' + file_info.name, recursive, fileList); //��windows�¿�����\\ת��ָ��������Ƽ�
		}
		else
		{
			fileList.push_front(path + '/' + file_info.name);
		}
	} while (!_findnext(handle, &file_info));//����0�������  
//�ر��ļ����
	_findclose(handle);
	return 1;
}
int FileTraversePrint(string path, int layer, bool recursive)
{
	_finddata_t file_info;
	string current_path = path + "/*.*"; //Ҳ������/*��ƥ������  
	int handle = _findfirst(current_path.c_str(), &file_info);
	//����ֵΪ-1�����ʧ��  
	if (-1 == handle)
	{
		cout << "cannot match the path" << endl;
		return -1;
	}
	do
	{
		//�ж��Ƿ���Ŀ¼  
		if (file_info.attrib == _A_SUBDIR)
		{
			if (strcmp(file_info.name, ".") == 0 || strcmp(file_info.name, "..") == 0)
				continue;
			//�ݹ������Ŀ¼  
			//��ӡ�Ǻŷ�ӳ����Ȳ��  
			for (int i = 0; i < layer; i++)
				cout << "--";
			cout << file_info.name << endl;
			int layer_tmp = layer;
			if (strcmp(file_info.name, "..") != 0 && strcmp(file_info.name, ".") != 0 && recursive)  //.�ǵ�ǰĿ¼��..���ϲ�Ŀ¼�������ų������������
				FileTraversePrint(path + '/' + file_info.name, layer_tmp + 1, recursive); //��windows�¿�����\\ת��ָ��������Ƽ�
		}
		else
		{
			//��ӡ�Ǻŷ�ӳ����Ȳ��
			for (int i = 0; i < layer; i++)
				cout << "--";
			cout << file_info.name << endl;
		}
	} while (!_findnext(handle, &file_info));//����0�������  
	_findclose(handle);//�ر��ļ����
	return 1;
}