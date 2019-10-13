//benchmark factory
#pragma once
#include "Bench.h"
#include "HPL.h"
#include "Httpd-Server.h"
#include "Httpd-Client.h"
#include "MiniFE.h"
#include "Nginx-Client.h"
#include "HPCG.h"
#include <cstring>
// #include "MiniAlb.h"

Bench* selectBench(std::string program)
{
    //TODO: 새 프로그램 추가
    if(program == "httpd-server")       return new Httpd_Server;
    else if(program == "httpd-client")  return new Httpd_Client;
    else if(program == "hpl")           return new HPL;
    else if(program == "hpcg")          return new HPCG;
    else if(program == "minife")        return new MiniFE;
    else if(program == "nginx-client")  return new Nginx_Client;
    // else if(program == "miniAlb")       return new MiniAlb;

    // 잘못된 프로그램 이름을 넣은 경우
    std::cout << "please check program name\n";
    exit(-1); 
}