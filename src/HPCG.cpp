#include "HPCG.h"
using namespace std;

//TODO: 한 번 벤치 실행함녀 output이 세개씩나와...

// void HPCG::init()
// {
// //    Bench::init("hpcg");
// }


//TODO: 얘 잘 돌아가는지 TEST 필요
void HPCG::runBenchTool(int cpu, int period, int quota)
{
    // //벤치마크 실행
    // string mpirun = config.get("mpirun","").asString();
    // string exec = "docker exec " + NAME + " " + mpirun;
    // Bench::command(exec);

    MPI::runBenchTool(cpu,period,quota);

    //NOTE: 결과물이 여러개가 나와서, 그중에 가장 최근꺼 하나민 선택하여 이름 바꾸기
    string select = "docker exec " + NAME + " ls -tr | tail -1 ";
    string mv = "| xargs -I {} docker exec " + NAME + "mv {} hpcg.out";
    string setout = select + mv;
    Bench::command(setout);
}


HPCG::HPCG() : MPI("blackmilk274/hpcg", "hpcg")
{
}

HPCG::~HPCG()
{

}