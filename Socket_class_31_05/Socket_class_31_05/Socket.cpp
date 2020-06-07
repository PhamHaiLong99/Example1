#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Socket.h"

Socket::Socket(int port)
{
	printf("Initializing Winsock... \r\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf(" Failed.Error Code : % d \r\n", WSAGetLastError());
	}
	else
	{
		printf(" Initialized.\r\n");

		//Create a socket
		if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		{
			printf("Could not create socket : %d\r\n", WSAGetLastError());
		}
		printf(" Socket created.\r\n");

		server.sin_addr.s_addr = htonl(INADDR_ANY);//dia chi IP
		server.sin_family = AF_INET;
		server.sin_port = htons(port);//Port
		bind(s, (struct sockaddr*) & server, sizeof(struct sockaddr));// dang listen o port bao nhieu
	}
}
void Socket::WaitingData(char* dataRecv,int sizeData)
{
	listen(s, 10);// 10 la so thiet bi sever cho phep ket noi.
	struct sockaddr_in client;
	int lenSockAddr = sizeof(struct sockaddr);
	SOCKET sock = accept(s, (struct sockaddr*) & client, &lenSockAddr);
	//char dataRecv[1024];
	recv(sock, dataRecv, sizeData, 0);
	//printf("data: %s\r\n", dataRecv);
	char* dataSend = (char*)"200 OK";
	send(sock, dataSend, strlen(dataSend), 0);
	closesocket(sock);
}
Socket::Socket(char* SeverIp, int port)
{
	printf("Initialising Winsock...\r\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf(" Failed.Error Code : %d\r\n", WSAGetLastError());
	}
	else
	{
		printf(" Initialized.\r\n");

		//Create a socket
		if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		{
			printf("Could not create socket : %d\r\n", WSAGetLastError());
		}

		printf(" Socket created.\r\n");

		server.sin_addr.s_addr = inet_addr(SeverIp);//lay dia chi IP.

		server.sin_family = AF_INET;
		server.sin_port = htons(port);

		//Connect to remote server
		if (connect(s, (struct sockaddr*) & server, sizeof(server)) < 0)
		{
			printf("connect error\r\n");
		}
		printf("Connected\r\n");
	}

}
int Socket::Send(char* data)
{
	int size = 0;
	while (data[size++] != 0);
	return send(s, data, size-1, 0);
}
int Socket::SendOneByte(char data)
{
	return send(s, &data, 1, 0);
}
int Socket::Recv(char* buff, int size)
{
	return recv(s, buff, size, 0);
}
int Socket::conten_Length(char* nameFile)
{
	char* nameFind = (str)"Content-Length:";
	char arr[maxi];
	memset(arr, 0, maxi);
	status(nameFile, nameFind, arr, '\r');
	return atoi(arr);
}
int Socket::status(str strSrc, str strFind, char a[], char key)
{
	int i = 0;
	int j = 0;
	memset(a, 0, maxi);
	for (i = stringfind(strSrc, strFind); i < strlen(strFind) + stringfind(strSrc, strFind); i++)
	{
		a[j++] = strSrc[i];
	}
	return 0;
	if (strSrc[i] == key) return -1;
}
int Socket::stringfind(str strSrc, str strFind)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < strlen(strSrc) - strlen(strFind); i++)
	{
		for (j = 0; j < strlen(strFind); j++)
		{
			if (strSrc[i + j] != strFind[j]) break;
		}
		if (j == strlen(strFind)) break;
	}
	if (i == strlen(strSrc) - strlen(strFind)) return -1;
	return i + strlen(strFind);
}