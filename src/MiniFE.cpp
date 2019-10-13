#include "MiniFE.h"
using namespace std;

void MiniFE::init(string _json)
{
    Bench::init("minife");
    this->runOption = "-w /minife/ref/src --entrypoint=/bin/bash " + runOption;
}

void MiniFE::runBenchTool(int cpu, int period, int quota)
{
    string mpirun = config.get("mpirun", "null").asString();
    // string mpirun = config["MiniFE"]["mpirun"].asString();
    string exec = "docker exec " + NAME + " " + mpirun;
    Bench::command(exec);

    //결과물 이름이 중구난방이라서 이름 바꾸기
    string mv = "docker exec " + NAME + " bash -c \"mv *.yaml output.yaml\"";
    Bench::command(mv);

}

void MiniFE::saveRslt(int cpu, int period, int quota)
{
    //호스트로 복사하기
    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);
    string result = NAME + config["MiniFE"]["outputPath"].asString();
    string getOutput =  "docker cp " + result + " " + outDir + 
                        "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota;

    command(getOutput);

    //남아있는 output.yaml 삭제
    string rm = "docker exec " + NAME + " bash -c \"rm output.yaml\"";
    command(rm);

}



MiniFE::MiniFE() : Bench("ivotron/minife", "minife"){}
MiniFE::~MiniFE(){}