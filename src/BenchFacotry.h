//benchmark factory
#pragma once
#include "Bench.h"
#include "HPL.h"
#include "Httpd-Server.h"
#include "Httpd-Client.h"
#include <cstring>

Bench* selectBench(std::string program)
{
    //TODO: 새 프로그램 추가
    if(program == "httpd-server")       return new Httpd_Server;
    else if(program == "httpd-client")  return new Httpd_Client;
    else if(program == "hpl")           return new HPL;

    // 잘못된 프로그램 이름을 넣은 경우
    std::cout << "please check program name\n";
    exit(-1); 
}