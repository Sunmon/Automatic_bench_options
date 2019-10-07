#include "HPL.h"
using namespace std;

void HPL::runBenchTool(int cpu, int period, int quota)
{
    exec();
    cpRslt(cpu, period, quota);
}

void HPL::exec()
{
    string mpirun = " mpirun --allow-run-as-root -np 4 xhpl";
    string exec = "docker exec " + NAME + mpirun;
    Bench::command(exec);
}

void HPL::init()
{
    Bench::init();
}

//실험환경설정 컨테이너로 복사
void HPL::cpEnvToContainer()
{
    string cp = "docker cp ../data/HPL.dat " + NAME + ":/AddedFiles/hpl-2.3/bin/x86_64";
    Bench::command(cp);
}

//실험결과를 호스트 컴퓨터로 복사
void HPL::cpRslt(int cpu, int period, int quota)
{
    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);
    string result = NAME + ":/AddedFiles/hpl-2.3/bin/x86_64/HPL.out";

    string getOutput =  "docker cp " + result + " " + outDir + 
                        "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota;

    command(getOutput);

}

HPL::HPL() : Bench("blackmilk274/hpl", "hpl")
{
    // init();
    // Bench::RUN = "docker run" + Bench::defaultOpt;


    // Bench::IMG = "blackmilk274/hpl";
    // Bench::NAME = "hpl";
    // Bench::CREATE = "docker create "; 
    // Bench::UPDATE = "";
    // Bench::IMG = string("asdf");
    // const string& IMG = "blackmilk274/hpl";
    // const string& NAME = "hpl";
}

HPL::~HPL()
{

}