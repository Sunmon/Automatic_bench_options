//벤치마크 인터페이스
//필요한 메소드, 변수들 정의
#pragma once
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include "json/json.h"
#include <fstream>

// #include "memory.h"
// #include "parsor.h"


#define CPUS 0
#define PER 1
#define QUO 2
// using namespace std;

class Bench
{
    private:
        int CORE = 4;

        virtual void runContainer();
        virtual void updateContainer(int cpu, int period, int quota);
        virtual void stopContainer();
        void initJson();

    protected:
        std::string IMG;
        std::string NAME;
        std::string DOCKER;             // "docker -H PORT" or "docker"
        std::string runOption;          // " -dit --rm --name " + NAME + " " + IMG;
        std::string manVar[3];          // manVar[0] = cpuset, manVar[1] = period, manVar[2] = bandwidth.
        std::string outDir;             // output이 저장되는 dir
        const std::string CPUSET[4] = {"0", "0-1", "0-2", "0-3"}; //cpu 번호 설정 필요. "0", "0,2", "0,2,4", "0,2,4,6"일수도 있음

        virtual void init();
        virtual void runBenchTool(int cpu, int period, int quota) = 0;
        virtual void cpEnvToContainer();
        virtual void saveRslt(int cpu, int period, int quota);
        
        void command(const std::string& cmd);
        void makeDir(const std::string& dir);



     public:
        virtual void benchmark();    //이 함수 실행하면 된다
        void setCore(int num);
        Json::Value config;

        Bench(); 
        Bench(const std::string& img, const std::string& name);
        virtual ~Bench();
        
        
};