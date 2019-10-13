#include "MiniFE.h"
using namespace std;

void MiniFE::init(string _json)
{
    Bench::init("minife");
    this->runOption = "-w /minife/ref/src --entrypoint=/bin/bash " + runOption;
}

void MiniFE::initContainer(){   //do nothing
}

void MiniFE::runBenchTool(int cpu, int period, int quota)
{
    string mpirun = config.get("mpirun", "null").asString();
    // string mpirun = config["MiniFE"]["mpirun"].asString();
    string exec = "docker exec " + NAME + " " + mpirun;
    Bench::command(exec);

    //결과물 이름이 중구난방이라서 이름 바꾸기
    string mv = "docker exec " + NAME + " bash -c \"mv *.yaml minife.out\"";
    Bench::command(mv);
}

// void MiniFE::saveRslt(int cpu, int period, int quota)
// {
//     Bench::saveRslt(cpu,period,quota);

//     //남아있는 output.yaml 삭제
//     // string rm = "docker exec " + NAME + " rm minife.out";
//     string rm = "docker exec " + NAME + " bash -c \"rm output.yaml\"";
//     command(rm);

// }



MiniFE::MiniFE() : Bench("ivotron/minife", "minife"){}
MiniFE::~MiniFE(){}