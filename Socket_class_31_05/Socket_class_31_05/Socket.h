#pragma once
#include <stdio.h>
#include "Ws2tcpip.h"
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define maxi 30
typedef char* str;
class Socket
{
public:
	//Ham tao
	Socket(int port);
	Socket(char* SeverIp, int port);
	int Send(char* data);
	int Recv(char* buff, int size);
	int conten_Length(char* nameFile);
	int status(str strSrc, str strFind, char a[], char key);
	int stringfind(str strSrc, str strFind);
	int SendOneByte(char data);
	void WaitingData(char* dataRecv,int sizeData);
private:
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	
};

//class HTTP
//{
//
//};
