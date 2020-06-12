#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>


#pragma warning(disable: 4996)
#define WIDTH_MAP 10
int main()
{
	std::string ShipMap[WIDTH_MAP] = //Игровое поле
	{
	 "0000000000",
	 "0000000000",
	 "0000000000",
	 "0000000000",
	 "0000000000",
	 "0000000000",
	 "0000000000",
	 "0000000000",
	 "0000000000",
	 "0000000000",
	};
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); //Версия библиотеки
	if (WSAStartup(DLLVersion, &wsaData) != 0) //Загрузка библиотеки
	{
		std::cout << "Error" << std::endl;
		exit(1);
	};
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(11111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) { // Проверка успешности соединения
		std::cout << "Client: failed connect to server \n";
		return 1;
	};
	std::cout << "Connected" << std::endl;

	int sizeMap = WIDTH_MAP;//Размер карты 

	send(Connection, (char*)&sizeMap, sizeof(sizeMap), NULL);//отправка данных о размере

	char buff[256]; //Буфер для хранения строк поля 
	for (int i = 0; i < WIDTH_MAP; i++) {

		for(int j=0; j<WIDTH_MAP; j++) //Считывание данных из строки поля в буфер
			buff[j] = ShipMap[i][j];

		send(Connection, buff, sizeof(buff), NULL);//отправка данных о поле
	}
	
	return 0;
}