#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

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


namespace echonet{

const int BUFFER_SIZE = 1024;
const int DEFAULT_PORT = 30001;
const int DEFAULT_MSG_COUNT = 1;
const int BACKLOG_QUEUE_SIZE = 10;

const std::string DEFAULT_HOST = "127.0.0.1";
const std::string MODE_CLIENT = "client";
const std::string MODE_SERVER = "server";
const std::string DEFAULT_MODE = MODE_CLIENT;
const std::string DEFAULT_MSG = "hello world!";
const std::string BYE_BYE = "`"; // "!exit";
const std::string APP_NAME = "echonet";

std::string getServerTime();
}
#endif // COMMON_H_INCLUDED
