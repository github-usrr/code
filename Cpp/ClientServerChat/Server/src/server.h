#pragma once

#include <mutex>
#include <thread>
#include <map>
#include <arpa/inet.h>

class Server
{
public:
    static Server & getInstance();
    
    void start(const int port);
    void closeSocket();

    ~Server();

private:
    void acceptConnections();
    void handleConnection(const int connection);

    Server() {}
    Server(const Server&)            = delete;
    Server& operator=(const Server&) = delete;

    int serverSocket = -1; // by default
    const int MAX = 500;
    sockaddr_in clientAddr;
    std::mutex m;
    std::map<int, std::thread> connectionHandlers;
};