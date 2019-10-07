//벤치마크 인터페이스
//필요한 메소드, 변수들 정의
#pragma once
#include <cstring>
#include <iostream>
#include <stdlib.h>
#define CPUS 0
#define PER 1
#define QUO 2
// using namespace std;

class Bench
{
    //TODO: public/ private/ protectec 구분하기
    public:
    // private:
        int CORE = 4;
        const std::string CPUSET[4] = {"0", "0-1", "0-2", "0-3"}; //cpu 번호 설정 필요. "0", "0,2", "0,2,4", "0,2,4,6"일수도 있음
        virtual void init();
        void command(const std::string& cmd);
        void makeDir(const std::string& dir);

        // virtual void createContainer(const std::string& opt); 
        virtual void runContainer();
        virtual void updateContainer(int cpu, int period, int quota);

        // virtual void runProgram();

    // protected:
        std::string IMG              ;//= "";
        std::string NAME             ;//= "";
        // std::string CREATE           ;//= " docker create ";
        // std::string RUN              ;//= " docker run ";
        std::string DOCKER;             //"docker -H PORT" or "docker"
        // std::string UPDATE           ;//= " docker update ";
        std::string defaultOpt      ;//" -dit --rm --name " + NAME + " " + IMG;
        std::string manVar[3]   ; //update와 결과 저장에 쓰는 조작변인.
        std::string outDir;
        // const int CPU = 0, PER = 1, QUO = 2;

        // virtual void runProgram() = 0;
        virtual void runBenchTool(int cpu, int period, int quota) = 0;
        virtual void stopContainer();
        virtual void cpEnvToContainer();

        

    //  public: 
        virtual void benchmark();    //이 함수 실행하면 된다

        void setCore(int num);

        Bench(); 
        Bench(const std::string& img, const std::string& name);
        virtual ~Bench();
        // string OUTPUT[2]; 
};