#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Socket.h"
typedef char* str;
class AWS_S3: private Socket
{
public:
	AWS_S3();
	void get(char* nameFile, char* buff, int buffLen);
	void put(char* nameFile, char* data, int dataLen);
	void get_file(char* nameSrc, char* nameDst);
	void put_file(char* nameSrc);
	void putFile(str nameFile, str nameAWS);
	void getFile(str nameFile, str nameAWS);
};


