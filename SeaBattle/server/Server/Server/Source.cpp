#include <SFML/Network.hpp>
#include <iostream>
#include "windows.h"
using namespace sf;
int main()
{
	IpAddress ip = "172.0.0.1";
	TcpSocket socket;
	TcpListener listener;
	std::size_t received;
	listener.listen(2000);
	listener.accept(socket);
	int x = 5;
	int y = 2;
	socket.send((char*)&x, sizeof(x));
	socket.send((char*)&y, sizeof(y));
	socket.receive((char*)&x, sizeof(x), received);
	std::cout << x;
}