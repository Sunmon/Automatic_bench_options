#include "HPL.h"
using namespace std;

void HPL::runBenchTool(int cpu, int period, int quota)
{
    string mpirun = " mpirun --allow-run-as-root -np 4 xhpl";
    string exec = "docker exec " + NAME + mpirun;
    Bench::command(exec);
}

//실험환경설정 컨테이너로 복사
void HPL::cpEnvToContainer()
{
    //FIXME: link 고치기. json에서 읽어오기.
    string cp = "docker cp ../env/HPL.dat " + NAME + ":/AddedFiles/hpl-2.3/bin/x86_64";
    Bench::command(cp);
}

//실험결과를 호스트 컴퓨터로 복사
void HPL::saveRslt(int cpu, int period, int quota)
{

    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);
    //FIXME: link 고치기. json에서 읽어오기.
    string result = NAME + ":/AddedFiles/hpl-2.3/bin/x86_64/HPL.out";



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