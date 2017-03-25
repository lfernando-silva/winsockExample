#pragma once

const int getConnectionsLimit();
int getCount();
void handleNewConnections(SOCKET s, SOCKADDR saddr, int addrlen);
void incrementCount();
void sendMessages(SOCKET connection);
void startup();
SOCKET initializeServer(int addrlen, SOCKADDR saddr, int connectionsLimit);
SOCKET getSocket(int position);
SOCKET startConnection(int addrlen, SOCKADDR saddr);
SOCKADDR_IN getAddr(char* host, int port);