#include "server.h"

#include <iostream>
#include <cstring>
#include <unistd.h>

using namespace std;

Server & Server::getInstance()
{
    static Server server;
    return server;
}

Server::~Server()
{
    closeSocket();
}

void Server::start(const int port)
{
    // Creating server socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// creating a socket and assigning it to the socket handler
	if (serverSocket < 0)
	{
		// socket methode return -1 if the creation was not successful
		cout << "Socket creation has failed.";
		return;
	}

	struct sockaddr_in serverAddr;

	// specifying address and type for the server to operate under
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int bindStatus = bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (bindStatus < 0)
	{
		cout << "Socket binding has failed" << endl;
		return;
	}

	// listen to the client while others are waiting in queue of size 5
	int listenStatus = listen(serverSocket, 5);
	if (listenStatus < 0)
	{ // when queue is full listen fails
		cout << "Listen has failed" << endl;
		return;
	}

	cout << "\t\t...Waiting for connections... \n\n";

	acceptConnections();
}

void Server::closeSocket()
{
    if (serverSocket != -1)
        close(serverSocket);
}

void Server::acceptConnections()
{
    socklen_t len = sizeof(clientAddr);

	while (true)
	{
		int connection;
		if ((connection = accept(serverSocket, (struct sockaddr*)&clientAddr, &len)) < 0)
		{
			m.lock(); cout << "\nServer didn't accept the request." << endl; m.unlock();
			return;
		}
		else
		{
			m.lock(); cout << "\nServer accepted the request. \n"; m.unlock();
		}

		m.lock();
		connectionHandlers[ connection ] = std::thread(&Server::handleConnection, this, connection);
		connectionHandlers[ connection ].detach();
		m.unlock();
	}
}

void Server::handleConnection(const int connection)
{
	while (true)
	{
		int rMsgSize;
		char buff[MAX];

		if ((rMsgSize = recv(connection, buff, MAX, 0)) > 0)
		{
			m.lock();
			cout << "\nReceived from Client id=" << connection << ": " << buff << endl;
			m.unlock();

            // add client id to beginning of byte array
			char idBuff[ MAX + sizeof(int) ];
			memcpy(idBuff, &connection, sizeof(int));
			memcpy(idBuff+sizeof(int), buff, MAX);

			m.lock();
			for ( auto it = connectionHandlers.begin(); it != connectionHandlers.end(); )
			{
				// don't send message to sender client
				if (it->first == connection)
					++it;

				// send message to other clients
				else
				{	// check if connection is available
					int error = 0;
					socklen_t len = sizeof (error);
					int retval = getsockopt(it->first, SOL_SOCKET, SO_ERROR, &error, &len);

					if ( retval || error )  // connection lost, remove it from list
					{
						it->second.~thread();
						it = connectionHandlers.erase(it);
					}
					else  // connection is up
					{
						send(it->first, idBuff, MAX+sizeof(int), 0);
						++it;
					}
				}
			}
			m.unlock();
		}
	}
}