#include "client.h"
namespace echonet{
Client::Client(std::map<std::string, std::string> paramMap)
{
    this->paramMap = paramMap;
    start();
}
Client::~Client()
{
    //dtor
}

bool Client::start(){
    bool createSocket = CreateSocket();
    if( !createSocket) return false;
    bool prepareAddress = PrepareAddress();
    if( !prepareAddress) return false;
    bool connectSocket = ConnectSocket();
    if( !connectSocket) return false;
    bool communicationLoop = CommunicationLoop();
    if( !communicationLoop) return false;
    return true;
}
bool Client::CreateSocket(){
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if( socketFd == -1){
        std::cout<<"ERROR: Could not create client socket"<<std::endl;
        return false;
    }
    std::cout<<"Client socket created..."<<std::endl;
    return true;

}

bool Client::PrepareAddress(){
    serverSocket.sin_family = AF_INET;
    //serverSocket.sin_addr.s_addr = INADDR_ANY;
    serverSocket.sin_addr.s_addr = inet_addr( paramMap["h"].c_str());
    serverSocket.sin_port = htons( atoi(paramMap["p"].c_str()));
    return true;
}

bool Client::ConnectSocket(){
    int connectionValue = connect(socketFd, (struct sockaddr*)&serverSocket, sizeof(serverSocket));
    if( connectionValue < 0){
        std::cout<<"ERROR: Connection to server socket failed"<<std::endl;
        return false; // fatal error
    }
    std::cout<<"Connection to server socket success..."<<std::endl;
    return true;
}

bool Client::CommunicationLoop(){
    std::string signature;
    while(true){


        std::cout<<"Type " << BYE_BYE << " to disconnect session :"<< std::endl;
        std::cout<<"Please enter your message:"<<std::endl;
        std::getline(std::cin, buffer, '\n'); // not max size, will need to loop input

        if( buffer == BYE_BYE){
            std::cout<<"Bye bye."<<std::endl;
            close(socketFd);
            return true;
        } else {
            // send data
            int sendSz = send(socketFd, buffer.c_str(),  buffer.length(), 0);
            if( sendSz < 0){
                std::cout<<"ERROR: Sending message to server socket failed"<<std::endl;
                return false; // fatal error
            }

            // receive data
            char readBuffer [BUFFER_SIZE];
            memset(readBuffer, '\0', BUFFER_SIZE);
            int recvSz = recv(socketFd, readBuffer,  BUFFER_SIZE, 0);
            buffer = readBuffer;
            if( recvSz < 0){
                std::cout<<"ERROR: Receiving message from server socket failed"<<std::endl;
                return false; // fatal error
            }

            std::string serverTime = echonet::getServerTime();
            signature = serverTime +  "@" + paramMap["h"] + ":" + std::to_string( serverSocket.sin_port ) + "# ";
            std::cout<<signature << buffer << std::endl;
        }
    }
    close(socketFd);
    return true;
}
}//end namespace
