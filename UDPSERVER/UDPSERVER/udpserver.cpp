#include <winsock2.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib,"WS2_32.lib")


int main()
{
	WSADATA data;
	WORD W = MAKEWORD(2,0);

	char sztext[] = "welcome,friends,you successfully connect to the server by UDP..\r\n";
	::WSAStartup(W,&data);
	SOCKET s,s2;
	//Create a UDP socket using SOCK_DGRAM
	s = ::socket(AF_INET,SOCK_DGRAM,0);
	s2 = ::socket(AF_INET, SOCK_DGRAM, 0);	
	//Give the ip and port of server
	sockaddr_in server_addr, client_addr;
	int num = sizeof(client_addr);
	char buff[255] = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(80);//80
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;//ANY IP

	//Bind the ip and port of server
	::bind(s,(sockaddr*)&server_addr,sizeof(server_addr));
	printf("Now,UDP server start already...\r\n");

	//endless; circulation
	while (true)
	{ 
		//receive msg from client(udp protocol)
		if (::recvfrom(s,buff,255,0,(sockaddr*)&client_addr,&num) != 0)
		{
			printf("UDP IP:%s--already connect\r\n",inet_ntoa(client_addr.sin_addr));

			printf("%s\r\n",buff);

			//send datas to client to let client know get the responce
			if (::sendto(s2, sztext, sizeof(sztext), 0, (sockaddr*)&client_addr, num)==0)
			{
				printf("failed to send msg to udp client... ...\n");
			}
			//break;
			::Sleep(1000);
		}
	}
	::closesocket(s);
	::WSACleanup();

	if (getchar())
	{
		return 0;
	}
	else
	{
		::Sleep(100);
	}
}