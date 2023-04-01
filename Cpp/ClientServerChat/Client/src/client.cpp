#include "client.h"

#include <thread>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

Client & Client::getInstance()
{
    static Client client;
    return client;
}

void Client::start(const char * serverAddress, const int serverPort)
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	if (clientSocket < 0)
	{
		cout << "Creation of client socket failed" << endl;
		return;
	}

	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(serverAddress);
	serverAddr.sin_port = htons(serverPort);

	if ( connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0 )
	{
		cout << "Connection Error..." << endl;
		return;
	}

	cout << "\t\tConnection Established..." << endl;

	// receive
	std::thread t(&Client::receiveMsgs, this);
	t.detach();

	// send
	sendMsgs();
}

void Client::closeSocket()
{
    if (clientSocket != -1)
        close(clientSocket);
}

Client::~Client()
{
    closeSocket();
}

void Client::receiveMsgs()
{
	while (true)
	{
		char receiveMessage[MAX+sizeof(int)];
		int rMsgSize = recv(clientSocket, receiveMessage, MAX+sizeof(int), 0);

		if (rMsgSize < 0)
		{
			cout << "Packet receive failed." << endl;
			return;
		}
		else if (rMsgSize == 0)
		{
			cout << "Server is off." << endl;
			return;
		}

		int id;
		memcpy(&id, receiveMessage, sizeof(int));

		char pureMsg[MAX];
		memcpy(pureMsg, receiveMessage + sizeof(int), MAX);

		cout << "\nClient id=" << id << ": " << pureMsg << "\n\n";
	}
}

void Client::sendMsgs()
{
	while (true)
	{
		string s;
		char input[MAX];

		getline(cin, s);
		int n = s.size();

		for (int i = 0; i < n; i++)
		{
			input[i] = s[i];
		}
		input[n] = '\0';

		send(clientSocket, input, strlen(input) + 1, 0);
	}
}