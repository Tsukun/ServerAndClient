#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include "time.h"

#pragma warning(disable: 4996)

//������� ��������� ���������� �������� �� ����
int FireX() 
{
	int x = 0;
	x = rand() % 10;
	return x;
}
int FireY()
{
	int  y = 0;
	y = rand() % 10;
	return y;
}
int main() 
{
	srand(time(NULL));
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); //������ ����������
	if (WSAStartup(DLLVersion, &wsaData) != 0) //�������� ����������
	{
		std::cout << "Error" << std::endl;
		exit(1);
	};
	SOCKADDR_IN addr; 
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	addr.sin_port = htons(11111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //�������� ������ �� ���������
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //�������� ������ � �������
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr); //��������� ���������� � ��������

	if (newConnection == 0) { // �������� ���������� ����������
		std::cout << "Error #2";
	}
	else {
		std::cout << "Client connected was succesful" << std::endl;
		while (true) {
			int shoot;	
			recv(newConnection, (char*)&shoot, sizeof(shoot), NULL);
		if (shoot == 1) {
			int x, y;
			x = FireX();
			y = FireY();
			send(newConnection, (char*)&x, sizeof(x), NULL);
			send(newConnection, (char*)&y, sizeof(x), NULL);
			std::cout << x << y;
			shoot = 0;
			}
		}
		
	}

	return 0;

}