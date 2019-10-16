//benchmark factory
#pragma once
#include "Bench.h"
#include "DockerD.h"
#include "MiniFE.h"
#include "HPCG.h"
#include "Jmeter.h"
#include <cstring>
// #include "HPL.h"
// #include "Httpd-Client.h"
// #include "Nginx-Client.h"
// #include "MiniAlb.h"

Bench* selectBench(std::string program)
{
    //TODO: 새 프로그램 추가
    if(program == "dockerd")       return new DockerD;
    else if(program == "httpd")  return new Jmeter("httpd", "httpd");
    else if(program == "hpl")           return new MPI("blackmilk274/hpl", "hpl");
    else if(program == "hpcg")          return new HPCG;
    else if(program == "minife")        return new MiniFE;
    else if(program == "nginx")  return new Jmeter("nginx", "nginx");
    // else if(program == "miniAlb")       return new MiniAlb;

    // 잘못된 프로그램 이름을 넣은 경우
    std::cout << "please check program name\n";
    exit(-1); 
}