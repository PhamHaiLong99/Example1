#define _CRT_SECURE_NO_WARNINGS
#include "AWS_SE.h"
AWS_S3::AWS_S3():Socket((char*)"52.219.128.83", 80)
{

}
void AWS_S3::get(char* nameFile, char* buff, int buffLen)
{
	char data_send[1024];
	sprintf(data_send, "GET /%s HTTP/1.1\r\nHost: imic-backet-s3.s3-ap-southeast-1.amazonaws.com\r\n\r\n", nameFile);
	printf("data send:%s", data_send);
	Send(data_send);
	char header[1024];
	int cnt = 0;
	memset(header, 0, sizeof(header));
	while (1)
	{
		Recv(header + cnt, 1);//truyen vao cai dia chi.
		if (cnt > 3)
		{
			if (header[cnt]=='\n' && header[cnt-1]=='\r'&& header[cnt-2]=='\n'&& header[cnt-3]=='\r')
			{
				break;
			}
		}
		cnt++;
	}
	printf("Header:\r\n%s", header);
	Recv(buff, buffLen);
	//printf("\r\n");
}
void AWS_S3::put(char* nameFile, char* data, int dataLen)
{
	char data_send[1024];
	char data_temp[1024];
	memset(data_temp, 0, 1024);
	memset(data_send, 0, 1024);
	sprintf(data_send, "PUT /%s HTTP/1.1\r\nContent-Length: %d\r\nHost: imic-backet-s3.s3-ap-southeast-1.amazonaws.com\r\n\r\n%s", nameFile, dataLen,data);
	printf("data_send: %s\r\n", data_send);
	Send(data_send);
	Recv(data_temp, sizeof(data_temp));
	printf("%s", data_temp);
}
void AWS_S3::get_file(char* nameSrc, char* nameDst)
{
	char data_temp[1024];
	char data_send[1024];
	memset(data_temp, 0, 1024);
	memset(data_send, 0, 1024);
	sprintf(data_send, "GET /%s HTTP/1.1\r\nHost: imic-backet-s3.s3-ap-southeast-1.amazonaws.com\r\n\r\n", nameSrc);
	//printf("data_send: %s\r\n", data_send);
	int cnt = 0;
	Send(data_send);
	Recv(data_temp, 1024);
	printf("\r\n%s", data_temp);
	char content = conten_Length(data_temp);
	FILE* fp = fopen(nameDst, "a+b");
	char temp = 0;
	for (int i = 0; i < content; i++)
	{
		Recv(&temp, 1);
		putc(temp,fp);
	}
	fclose(fp);
}
void AWS_S3::putFile(str nameFile,str nameAWS)
{
	FILE* file = fopen(nameFile, "a+b");
	int sizeFile = 0;
	while (1)
	{
		if (fgetc(file) == EOF) break;
		sizeFile++;
	}
	fclose(file);
	printf("size of file %d\r\n", sizeFile);
	char data_temp[1024];
	char data_send[1024];
	memset(data_send, 0, 1024);
	memset(data_temp, 0, 1024);
	sprintf(data_send, "PUT /%s HTTP/1.1\r\nContent-Length: %d\r\nHost: imic-backet-s3.s3-ap-southeast-1.amazonaws.com\r\n\r\n", nameAWS, sizeFile);
	printf("%s", data_send);
	Send(data_send);
	file = fopen(nameFile, "a+b");
	char temp = 0;
	for (int i = 0; i < sizeFile; i++)
	{
		temp = fgetc(file);
		SendOneByte(temp);
	}
	Recv(data_temp,sizeof(data_temp));
	printf("\r\n%s", data_temp);
}
void AWS_S3::getFile(str nameFile, str nameAWS)
{

}