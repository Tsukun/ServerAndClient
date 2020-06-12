#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>


#pragma warning(disable: 4996)

int main() 
{
	std::string ShipMap[10];
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
		int sizeMap;
	
		recv(newConnection, (char*)&sizeMap, sizeof(sizeMap), NULL);//��������� ������� ����
		//std::cout << sizeMap << std::endl;
		char buff[256];//����� ��� ����������
		for(int i = 0; i<sizeMap; i++){

			recv(newConnection, buff, sizeof(buff), NULL);//���������� ������ � ����� 

			for (int j = 0; j < sizeMap; j++) //���������� ������ �� ����� � ���� 
				ShipMap[i] += buff[j];
		}
		for (int i = 0; i < sizeMap; i++)//����� ����
			std::cout << ShipMap[i] << std::endl;
	}

	return 0;

}