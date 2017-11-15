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
	//线程休眠，chrono是c++11的时间相关库。
	this_thread::sleep_for(chrono::seconds(3));
	for (int i = 0; i < 10; ++i)
	{
		cout << "hello world" << endl;
		k++;
	}
}

int Thread(int argc, char *argv[])
{
	//创建线程对象
	thread t1(fun);
	//输出线程id和cpu核数
	cout << "ID:" << t1.get_id() << endl;
	cout << "CPU:" << std::thread::hardware_concurrency() << endl;
	//主函数阻塞等待线程结束
	t1.join();
	//主函数和线程函数分离执行，线程变为后台线程
	//t1.detach();

	cout << k << endl;

	return EXIT_SUCCESS;
}