#include "server.h"
namespace echonet{
Server::Server(std::map<std::string, std::string> paramMap)
{
    this->paramMap = paramMap;
    start();
}

Server::~Server()
{
    //dtor
}
bool Server::start(){
    bool createSocket = CreateSocket();
    if( !createSocket) return false;
    bool prepareAddress = PrepareAddress();
    if( !prepareAddress) return false;
    bool bindSocket = BindSocket();
    if(! bindSocket) return false;
    bool listenSocket = ListenSocket();
    if( ! listenSocket) return false;
    bool acceptLoop = AcceptLoop();
    if( ! acceptLoop) return false;
    return true;
}

bool Server::CreateSocket(){
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if( socketFd == -1){
        std::cout<<"ERROR: Could not create server socket"<<std::endl;
        return false;
    }
    std::cout<<"Server socket created..."<<std::endl;
    return true;
}

bool Server::PrepareAddress(){
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_addr.s_addr = INADDR_ANY;
    serverSocket.sin_port = htons( atoi(paramMap["p"].c_str()));
    return true;
}

bool Server::BindSocket(){
    int bindValue = bind(socketFd, (struct sockaddr*)&serverSocket, sizeof(serverSocket));
    if( bindValue < 0){
        std::cout<<"ERROR: Binding to server socket failed"<<std::endl;
        return false; // fatal error
    }
    std::cout<<"Binding to server socket success..."<<std::endl;
    return true;
}

bool Server::ListenSocket(){
    listen(socketFd, BACKLOG_QUEUE_SIZE);
    return true;
}

bool Server::AcceptLoop(){
    clientSocketSize = sizeof(struct sockaddr_in);
    std::cout<<"Waiting for incoming connection..."<<std::endl;

    while( (clientSocketFd = accept(socketFd, (struct sockaddr*)&clientSocket, (socklen_t*)&clientSocketSize)) ){

        std::cout<<"Connection accepted from " << inet_ntoa(clientSocket.sin_addr) << ":" <<  ntohs(clientSocket.sin_port)<< std::endl;

        newSocketFd = (int*)malloc( sizeof(*newSocketFd) );
        *newSocketFd = clientSocketFd;

        std::string clientAddr = inet_ntoa(clientSocket.sin_addr);
        int port = ntohs(clientSocket.sin_port);
        std::thread clientThread(&Server::connectionHandler, this, newSocketFd , clientAddr, port);
        std::cout<<"Client handler assigned."<<std::endl;
        clientThread.detach();
    }

    if( clientSocketFd < 0){
        std::cout<<"ERROR: Accepting client connection failed"<<std::endl;
        return false; // fatal error

    }
    return true; // success
}

void Server::connectionHandler(int*clientSocketFd, std::string clientAddr, int port){
    int socket = *clientSocketFd;
    int readSz;
    int writeSz;
    char *bufferSend;
    char *bufferReceive = new char[BUFFER_SIZE];
    std::string signature;

    // receive client message
    while(( readSz = recv( socket, bufferReceive, BUFFER_SIZE, 0)) > 0){

        // echo to client
        writeSz = write(socket, bufferReceive, strlen(bufferReceive));

        std::string serverTime = echonet::getServerTime();
        signature = serverTime +  "@" + clientAddr + ":" + std::to_string(port) + "# ";
        std::cout<< signature << bufferReceive<< std::endl;
        memset(bufferReceive, '\0', BUFFER_SIZE);
    }

    if( readSz == 0){
        std::cout<< signature << "client disconnected." << std::endl;
        fflush(stdout);
    } else if( readSz == -1){
        std::cout<< signature << "ERROR: received failed." << std::endl;
    }

    free(clientSocketFd);
    close(socket);
    return;
}
}//end namespace
