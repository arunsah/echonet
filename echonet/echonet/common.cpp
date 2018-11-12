#include "common.h"

namespace echonet{
std::string getServerTime(){
    // clean time code
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())%1000;
    auto time = std::chrono::system_clock::to_time_t(now);

    //auto time = std::time(nullptr);
    auto localtime = *std::localtime( &time);
    std::ostringstream oss;
    // NOTE: GCC 5.0>

    //oss<< std::put_time( &localtime, "%d-%m-%Y %H-%M-%S");
    oss<< std::put_time( &localtime, "%Y.%m.%d %H.%M.%S");
    oss<<'.'<< std::setfill('0')<<std::setw(3)<< ms.count();
    std::string serverTime = oss.str();
    return serverTime;
}
}//end namespace
