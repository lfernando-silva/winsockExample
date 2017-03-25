#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include "ConnectionsManager.h"

int main() {
	startup();

	SOCKADDR_IN addr = getAddr("127.0.0.1", 1234); //Address to be binded to our socket client
	int addrlen = sizeof(addr); //Necessary to accept calls

	SOCKADDR* saddr = (SOCKADDR*)&addr;
	SOCKET connection = startConnection(addrlen, *saddr);
	sendMessages(connection);

	system("pause");
	return 0;
}