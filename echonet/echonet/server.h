#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <chrono>
#include <map>
#include <thread>

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "common.h"

namespace echonet{
class Server
{
    public:
        Server(std::map<std::string, std::string>);
        virtual ~Server();
        bool start();
        bool CreateSocket();
        bool PrepareAddress();
        bool BindSocket();
        bool ListenSocket();
        bool AcceptLoop();
        void connectionHandler(int*, std::string, int); // task handler


    protected:

    private:
        int socketFd;
        int clientSocketFd;
        int *newSocketFd;

        struct sockaddr_in serverSocket;
        struct sockaddr_in clientSocket;
        int clientSocketSize;
        std::map<std::string, std::string> paramMap;
};
}
#endif // SERVER_H
