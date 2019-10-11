#include "MiniAlb.h"
using namespace std;

void MiniAlb::init()
{
    Bench::init();
    this->runOption = "-w /project/minife/ref/src --entrypoint=/bin/bash " + runOption;
    

}

void MiniAlb::cpEnvToContainer()
{
    string make = "docker exec " + NAME + " make miniFE.x";
    Bench::command(make);
}


void MiniAlb::runBenchTool(int cpu, int period, int quota)
{
    // string mpirun = config["MiniFE"]["mpirun"].asString();
    string mpirun = config["MiniAlb"]["mpirun"].asString();
    string exec = "docker exec " + NAME + " " + mpirun;
    Bench::command(exec);

    //결과물 이름이 중구난방이라서 이름 바꾸기
    string mv = "docker exec " + NAME + " bash -c \"mv *.yaml output.yaml\"";
    Bench::command(mv);

}

void MiniAlb::saveRslt(int cpu, int period, int quota)
{
    //호스트로 복사하기
    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);
    string result = NAME + config["MiniAlb"]["outputPath"].asString();
    string getOutput =  "docker cp " + result + " " + outDir + 
                        "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota;

    command(getOutput);

    //남아있는 output.yaml 삭제
    string rm = "docker exec " + NAME + " bash -c \"rm output.yaml\"";
    command(rm);

}



MiniAlb::MiniAlb() : Bench("abeltre1/minife-mpi", "miniAlb"){}
MiniAlb::~MiniAlb(){}