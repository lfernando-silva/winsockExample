#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <iostream>

static int count = 0;
const int connectionsLimit;
SOCKET Connections[];

int ClientHandlerThread(int index) {
	char buffer[256];
	while (true) {
		recv(getSocket(index), buffer, sizeof(buffer), NULL);
		for (int i = 0; i < count; i++) 
			i != index ? send(getSocket(i), buffer, sizeof(buffer), NULL) : NULL;
	}
}

const int getConnectionsLimit() {
	return connectionsLimit;
}

int getCount() {
	return count;
}

void handleNewConnections(SOCKET s, SOCKADDR saddr, int addrlen) {
	SOCKET newConnection = accept(s, &saddr, &addrlen); //Socket to hold and accept client's connetion
	if (newConnection == 0) {
		std::cout << "Failed to accept client's connection" << std::endl;
	}
	else {
		std::cout << "Client's connected" << std::endl;
		char message[256] = "Welcome! Message of the day.";//Buffer
		Connections[count] = newConnection;
		count++;
		send(newConnection, message, sizeof(message), NULL);
	}
}

void incrementCount() {
	count+=1;
}

void sendMessages(SOCKET connection) {
	char message[256];
	recv(connection, message, sizeof(message), NULL);
	std::cout << "Message received from server:" << message << std::endl;
}

void startup() {
	try {
		//winsock startup
		WSAData wsaData;
		WORD DllVersion = MAKEWORD(2, 1);

		//Check if WSAStartup throws error
		if (WSAStartup(DllVersion, &wsaData) != 0) {
			throw 0;
		}
	}
	catch (int e) {
		std::cout << "WinSock startup failed" << std::endl;
		exit(1);
	}
}

SOCKET initializeServer(int addrlen, SOCKADDR saddr, int connectionsLimit) {
	Connections[connectionsLimit];
	SOCKET s = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	bind(s, &saddr, addrlen); //Bind the address to socket
	listen(s, SOMAXCONN); //Places s in a state listening for incoming connections
	return s;
}

SOCKET getSocket(int position) {
	return Connections[position];
}

SOCKET startConnection(int addrlen, SOCKADDR saddr) {
	SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
	try {
		if (connect(connection, &saddr, addrlen) != 0) {
			throw 0;
		}
		std::cout << "Connected" << std::endl;
		return connection;
	}
	catch (int e) {
		std::cout << "Failed to connect" << std::endl;
		system("pause");
		exit(1);
	}
}

SOCKADDR_IN getAddr(char* host, int port) {
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr(host); //Host
	addr.sin_port = htons(port); //Port
	addr.sin_family = AF_INET; //IPV4
	return addr;
}