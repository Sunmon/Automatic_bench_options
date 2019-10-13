#include "HPL.h"
using namespace std;

void HPL::runBenchTool(int cpu, int period, int quota)
{
    string mpirun = config["HPL"]["mpirun"].asString();
    string exec = "docker exec " + NAME + " " + mpirun;
    Bench::command(exec);
}

//실험환경설정 컨테이너로 복사
void HPL::initContainer()
{
    Bench::initContainer("hpl");
}

// {
//     string hpldat = config["HPL"]["dat"].asString();
//     string hplroot = config["HPL"]["workdir"].asString();
//     string cp = DOCKER + "cp " + hpldat + " " + NAME + hplroot + "/HPL.dat"; 
//     cout << cp << endl;
//     Bench::command(cp);
// }

//실험결과를 호스트 컴퓨터로 복사
void HPL::saveRslt(int cpu, int period, int quota)
{

    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);
    string result = NAME + config["HPL"]["outputPath"].asString();
    string getOutput =  "docker cp " + result + " " + outDir + 
                        "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota;

    command(getOutput);
}

HPL::HPL() : Bench("blackmilk274/hpl", "hpl")
{
}

HPL::~HPL()
{

}