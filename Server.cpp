#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include "ConnectionsManager.h"

int main() {
	startup();
	
	SOCKADDR_IN addr = getAddr("127.0.0.1", 1234); //Address that we will bind out listening socket to
	int addrlen = sizeof(addr); //Necessary to accept calls
	SOCKADDR* saddr = (SOCKADDR*)&addr;
	SOCKET s = initializeServer(addrlen, *saddr, 100); //Bind the address to socket
	
	int count = getCount();
	int connectionsLimit = getConnectionsLimit();

	while(count < connectionsLimit) handleNewConnections(s, *saddr, addrlen);
	system("pause");
	return 0;
}