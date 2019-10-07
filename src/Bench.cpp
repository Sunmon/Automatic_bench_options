//Bench.h 구현 클래스
#include "Bench.h"
using namespace std;


//terminal에 명령어 전달
void Bench::command(const std::string& cmd)
{
    const char* cmdptr = cmd.c_str();
    system(cmdptr); 
}

//dir에 디렉토리 만들기
void Bench::makeDir(const std::string& dir)
{
    string mkdir = "mkdir " + dir;
    // command(mkdir);
}



// void Bench::createContainer(const std::string& opt)
// {
//     CREATE = opt + CREATE; 
//     command(CREATE);
// }

void Bench::runContainer()
{
    command(RUN);
}

// void Bench::updateContainer()
// {
//     command(UPDATE);
// }
void Bench::runProgram(){}


//이 함수 실행하면 된다
void Bench::benchmark()
{
    runContainer();

}    

void setNUM_CPU(int num){};


Bench::Bench()
{
    // defaultOpt = " -dit --rm --name " + NAME + " " + IMG;
}

Bench::Bench(const string& img, const string& name)
{
    this->IMG = img;
    this->NAME =  name;
    this->defaultOpt = " -dit --rm --name " + NAME + " " + IMG;
}
Bench::~Bench(){}