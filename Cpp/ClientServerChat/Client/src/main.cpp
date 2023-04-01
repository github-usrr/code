#include "client.h"
#include <csignal>
#include <cstdlib>

void signalHandler(int sig)
{
	Client::getInstance().closeSocket();
	exit(sig);
}

int main()
{
	signal(SIGINT,  signalHandler);

	Client::getInstance().start("127.0.0.1", 56000);

	return 0;
}
