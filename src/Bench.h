//벤치마크 인터페이스
//필요한 메소드, 변수들 정의
#pragma once
#include <cstring>
#include <iostream>
#include <stdlib.h>

// using namespace std;

class Bench
{
    public:
    // private:
        const std::string NUM_CPU[4] = {"0", "0-1", "0-2", "0-3"}; //cpu 번호 설정 필요. "0", "0,2", "0,2,4", "0,2,4,6"일수도 있음
        void command(const std::string& cmd);
        void makeDir(const std::string& dir);

        // virtual void createContainer(const std::string& opt); 
        virtual void runContainer();
        // virtual void updateContainer();

        // virtual void runProgram();

    // protected:
        std::string IMG              ;//= "";
        std::string NAME             ;//= "";
        std::string CREATE           ;//= " docker create ";
        std::string RUN              ;//= " docker run ";
        std::string UPDATE           ;//= " docker update ";
        std::string defaultOpt      ;//" -dit --rm --name " + NAME + " " + IMG;

        // virtual void runProgram() = 0;
        virtual void runProgram();

        

    //  public: 
        virtual void benchmark();    //이 함수 실행하면 된다

        void setNUM_CPU(int num);

        Bench(); 
        Bench(const std::string& img, const std::string& name);
        virtual ~Bench();
        // string OUTPUT[2]; 
};