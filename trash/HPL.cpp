#include "HPL.h"
using namespace std;

void HPL::runBenchTool(int cpu, int period, int quota)
{
    string mpirun = config.get("mpirun","null").asString();
    string exec = "docker exec " + NAME + " " + mpirun;
    Bench::command(exec);
}


void HPL::init()
{
    Bench::init("hpl");
}

HPL::HPL() : Bench("blackmilk274/hpl", "hpl")
{
}

HPL::~HPL()
{

}