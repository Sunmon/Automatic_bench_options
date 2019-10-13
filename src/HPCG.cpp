#include "HPCG.h"
using namespace std;

//TODO: 한 번 벤치 실행함녀 output이 세개씩나와...

void HPCG::init(std::string _json)
{
   Bench::init("hpcg");
}

void HPCG::runBenchTool(int cpu, int period, int quota)
{
    string mpirun = config.get("mpirun","").asString();
    string exec = "docker exec " + NAME + " " + mpirun;
    Bench::command(exec);
}


//실험결과를 호스트 컴퓨터로 복사
void HPCG::saveRslt(int cpu, int period, int quota)
{

    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);
    // docker exec NAME ls -tr | tail -1 | xargs -I {} docker cp NAME:/AddedFiles/hpcg-3.1/bin/{}"
    string select = "docker exec " + NAME + " ls -tr | tail -1 | xargs -I {} ";
    string result_from = NAME + config.get("output_container","").asString();
    string result_to = outDir + "/cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota;
    string getOutput =  select + "docker cp " + result_from + " " + result_to;

    command(getOutput);
}



HPCG::HPCG() : Bench("blackmilk274/hpcg", "hpcg")
{
}

HPCG::~HPCG()
{

}