#pragma once

class Client
{
public:
    static Client & getInstance();
    
    void start(const char * serverAddress, const int serverPort);
    void closeSocket();

    ~Client();

private:
    void receiveMsgs();
    void sendMsgs();

    Client() {}
    Client(const Client&)            = delete;
    Client& operator=(const Client&) = delete;

    int clientSocket = -1; // by default
    const int MAX = 500;
};