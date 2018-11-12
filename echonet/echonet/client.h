#ifndef CLIENT_H
#define CLIENT_H

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
class Client
{
    public:
        Client(std::map<std::string, std::string>);
        virtual ~Client();

        bool start();
        bool CreateSocket();
        bool PrepareAddress();
        bool ConnectSocket();
        bool CommunicationLoop();


    protected:

    private:
        int socketFd;
        std::string buffer;
        struct sockaddr_in serverSocket;
        struct sockaddr_in clientSocket;
        int clientSocketSize;
        std::map<std::string, std::string> paramMap;


};
}
#endif // CLIENT_H
