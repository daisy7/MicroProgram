#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <thread>
#include <iostream>
#include"main.h"
using namespace std;
int k = 0;

void fun(void)
{
	//�߳����ߣ�chrono��c++11��ʱ����ؿ⡣
	this_thread::sleep_for(chrono::seconds(3));
	for (int i = 0; i < 10; ++i)
	{
		cout << "hello world" << endl;
		k++;
	}
}

int Thread(int argc, char *argv[])
{
	//�����̶߳���
	thread t1(fun);
	//����߳�id��cpu����
	cout << "ID:" << t1.get_id() << endl;
	cout << "CPU:" << std::thread::hardware_concurrency() << endl;
	//�����������ȴ��߳̽���
	t1.join();
	//���������̺߳�������ִ�У��̱߳�Ϊ��̨�߳�
	//t1.detach();

	cout << k << endl;

	return EXIT_SUCCESS;
}