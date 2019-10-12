#include "HPCG.h"
using namespace std;

//TODO: outputpath 고치기.
//TODO: 한 번 벤치 실행함녀 output이 세개씩나와...

void HPCG::runBenchTool(int cpu, int period, int quota)
{
    string mpirun = config["HPCG"]["mpirun"].asString();
    string exec = "docker exec " + NAME + " " + mpirun;
    Bench::command(exec);
}

//실험환경설정 컨테이너로 복사
void HPCG::cpEnvToContainer()
{
    string dat = config["HPCG"]["dat"].asString();
    string dir = config["HPCG"]["workdir"].asString();
    string cp = DOCKER + "cp " + dat + " " + NAME + dir; 
    Bench::command(cp);
}


//실험결과를 호스트 컴퓨터로 복사
void HPCG::saveRslt(int cpu, int period, int quota)
{

    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);
    // string result = NAME + config["HPCG"]["outputPath"].asString();
    string result = NAME + config["HPCG"]["outputPath"].asString();
    string select = "docker exec " + NAME + " ls -tr | tail -1 | xargs -I {} ";
    string getOutput =  select + "docker cp " + result + " " + outDir + 
                        "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota;

    command(getOutput);
}

HPCG::HPCG() : Bench("blackmilk274/hpcg", "hpcg")
{
}

HPCG::~HPCG()
{

}