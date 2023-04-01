#include "server.h"
#include <csignal>

void signalHandler(int sig)
{
	Server::getInstance().closeSocket();
	exit(sig);
}

int main()
{
	signal(SIGINT,  signalHandler);

	Server::getInstance().start(56000);

	return 0;
}
