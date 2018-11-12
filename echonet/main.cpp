#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "echonet/common.h"
#include "echonet/server.h"
#include "echonet/client.h"

using namespace std;

//https://github.com/arunsah/echonet.git
//It is C++ project to implement echo server/client using socket and multi-threading.
//It was tested on gcc 7.3.0 and -std=c++14.
//Goal is to improve this version with reactor pattern.

/*

Welcome to echonet
-------------------START_OF_USAGE-------------------
Usage: echonet [<params>=<values>]
<params> :
         /? | -help | -HELP | "anything not starting with -" will display this help.
         -p=port_value (eg. 20001)
         -h=hostname (eg. localhost | 127.0.0.1)
         -m=operating_mode (eg. server | client)

Default port    : 30001
Default host    : 127.0.0.1
Default mode    : client

Examples:
echonet -p=30001 -h=127.0.0.1 -m=server
echonet -p=30001 -h=127.0.0.1 -m=client
-------------------END_OF_USAGE-------------------
*/
void printUsage(){
    cout<<"Welcome to " << echonet::APP_NAME <<endl;
    cout<<"-------------------START_OF_USAGE-------------------"<<endl;
    cout<<"Usage: "<< echonet::APP_NAME <<" [<params>=<values>]"<<endl;
    cout<<"<params> : "<<endl;
    cout<<"\t /? | -help | -HELP | \"anything not starting with -\" will display this help."<<endl;
    cout<<"\t -p=port_value (eg. 20001)"<<endl;
    cout<<"\t -h=hostname (eg. localhost | 127.0.0.1)"<<endl;
    cout<<"\t -m=operating_mode (eg. server | client)"<<endl;
    //cout<<"\t -msg=default_message will send first (eg. \"hello world\")"<<endl;
    //cout<<"\t -count=number of times the mgs will be sent (eg. 1)"<<endl;
    cout<<endl;

    cout<<"Default port \t: "<< echonet::DEFAULT_PORT<<endl;
    cout<<"Default host \t: "<< echonet::DEFAULT_HOST<<endl;
    cout<<"Default mode \t: "<< echonet::DEFAULT_MODE<<endl;
    //cout<<"Default msg \t: "<< echonet::DEFAULT_MSG<<endl;
    //cout<<"Default count \t: "<< echonet::DEFAULT_MSG_COUNT<<endl;
    cout<<endl;

    cout<<"Examples:"<<endl;
    cout<<""<< echonet::APP_NAME <<" -p=30001 -h=127.0.0.1 -m=server"<<endl;
    cout<<""<< echonet::APP_NAME <<" -p=30001 -h=127.0.0.1 -m=client"<<endl;
    //cout<<""<< echonet::APP_NAME <<" -p=30001 -h=127.0.0.1 -m=client -msg=\"hello from client\" -count=10 "<<endl;

    cout<<"-------------------END_OF_USAGE-------------------"<<endl;

}

map<string, string> parseInputParameters(int argc, char ** argv){
    map<string, string> paramMap;

    paramMap.insert(pair<string, string>("app", argv[0]));

    for(int i=1; i < argc; ++i){
        string word = argv[i]; // pattern like: -p=30001;

        // capturing help
        if( word == "/?" || word == "-help" || word == "-HELP" || word[0] != '-' ){
            paramMap.clear();// erase all elements
            return paramMap;
        }

        int indexOfEq = 0;
        for(int j=0; j <word.length(); ++j) {
            if(word[j] == '=')break;
            ++indexOfEq;
        }
        string key = word.substr(1, indexOfEq-1);
        string value = word.substr(indexOfEq+1, word.length()-1);
        paramMap.insert(pair<string, string>(key, value));
    }

    if( paramMap.find("app") == paramMap.end() ) paramMap["app"] = echonet::APP_NAME;
    if( paramMap.find("p") == paramMap.end() ) paramMap["p"] = echonet::DEFAULT_PORT;
    if( paramMap.find("h") == paramMap.end() ) paramMap["h"] = echonet::DEFAULT_HOST;
    if( paramMap.find("m") == paramMap.end() ) paramMap["m"] = echonet::DEFAULT_MODE;
    if( paramMap.find("msg") == paramMap.end() ) paramMap["msg"] = echonet::DEFAULT_MSG;
    if( paramMap.find("count") == paramMap.end() ) paramMap["count"] = std::to_string( echonet::DEFAULT_MSG_COUNT );


    //    for(auto i : paramMap){
    //        cout<< i.first << "  \t " << i.second << endl;
    //    }

    return paramMap;

}

int main(int argc, char ** argv)
{
    auto paramMap = parseInputParameters(argc, argv);
    if( paramMap.size() < 1){
        printUsage();
        return 0;
    }

    if( paramMap["m"] == echonet::MODE_SERVER){
        echonet::Server s(paramMap);
    } else if( paramMap["m"] == echonet::MODE_CLIENT){
        echonet::Client c(paramMap);
    } else {
        cout<< "ERROR: Unknown operating mode :" << paramMap["m"] << ", use : " << echonet::MODE_SERVER << endl;
    }
    return 0;
}//end main
