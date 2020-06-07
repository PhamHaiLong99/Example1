#include "Socket.h"
#include "AWS_SE.h"
#include <Windows.h>
#include <thread>

//void thread1()
//{
//	while (1)
//	{
//		printf("hello World!\r\n");
//	}
//}
//void thread2()
//{
//	while (1)
//	{
//		printf("Xin Chao \r\n");
//	}
//}
int main()
{
	//Socket test((char*)"192.168.1.19", 2222);
	//test.Send((char*) "send from my app\r\n");
	//char buff[1024];
	//memset(buff, 0, 1024);
	//test.Recv(buff, sizeof(buff));
	//printf("gia tri cua buff la: %s", buff);
	//return 0;
	AWS_S3 imic;
	//char buffer[1024];
	//memset(buffer, 0, 1024);
	//imic.get((char*)"helloWorld.txt", buffer, sizeof(buffer));	
	//printf("%s", buffer);
	//char* data =(char*) "xin chao";
	//imic.put((char*)"test.txt", data, strlen(data));
	//imic.get_file((str)"DocumentC.pdf",(str) "tailieu_PDF.pdf");
	/*imic.putFile((str)"Anhdep.jpg",(str)"Gui_Thay.jpg");*/
	//std::thread vn(thread2);
	//vn.join();
	//std::thread eng(thread1);
	//eng.join();
	Socket server(1234);
	while (1)
	{
		char data[1024];
		memset(data, 0, sizeof(data));
		server.WaitingData(data,sizeof(data));
		printf("%s", data);
		for (int i = 3; i < strlen(data); i++)
		{
			if (data[i] == 'F' && data[i - 1] == 'F' && data[i - 2])
			{
				imic.put((char*)"helloWorld.txt", (char*)"LED_OFF", 7);
			}
			else if (data[i] == 'N' && data[i - 1] == 'O')
			{
				imic.put((char*)"helloWorld.txt", (char*)"LED_ON", 6);
			}
		}
	}
	return 0;
}