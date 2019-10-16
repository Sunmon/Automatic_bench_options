#include "MPI.h"
using namespace std;
//runoption과 DOCKER, 기본 output 폴더 초기화
// void MPI::init()
// {
//     this->runOption = " -dit --rm --name " + NAME + " " + IMG;
//     this->DOCKER = "docker ";

//     //기본 output 폴더 만들기
//     outDir = "../out/"+NAME;
//     makeDir(outDir);

//     //json 환경파일 가져오기
//     initJson();
// }

void MPI::init()
{
    this->runOption = " -dit --rm --name " + NAME + " " + IMG;
    this->DOCKER = "docker ";

    //기본 output 폴더 만들기
    outDir = "../out/"+NAME;
    makeDir(outDir);

    //json 환경파일 가져오기
    Bench::initJson(this->NAME);
}


//config.json파일의 내용을  이용하여 컨테이너 초기화.
void MPI::initContainer()
{
    if(config == "null") return;

    //copy data file into the container
    string data_host = config.get("data_host", "null").asString();
    string data_container = config.get("data_container", "null").asString();
    if(data_host != "null" && data_container != "null")
    {
        string cp = this->DOCKER + " cp " + data_host + " " + NAME + data_container;
        MPI::command(cp);
    }
}


void MPI::runBenchTool(int cpu, int period, int quota)
{
    string mpirun = config.get("mpirun", "null").asString();
    // string mpirun = config["MiniFE"]["mpirun"].asString();
    string exec = "docker exec " + NAME + " " + mpirun;
    Bench::command(exec);

    //결과물 이름이 중구난방이라서 이름 바꾸기
    // string mv = "docker exec " + NAME + " bash -c \"mv *.yaml minife.out\"";
    // Bench::command(mv);
}


// 컨테이너내에 저장된 결과파일을 호스트 컴퓨터로 복사
void MPI::saveRslt(int cpu, int period, int quota)
{
    //파일이름에 쓸 변수
    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);

    //컨테이너에서 호스트로 결과값 복사
    string result_from = this->NAME + config.get("output_container", "null").asString();
    string result_to = outDir + "/cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota;
    string cp =  this->DOCKER +  " cp " + result_from + " " + result_to;

    command(cp);
}


MPI::MPI(){}
MPI::MPI(const std::string &img, const std::string &name):Bench(img, name){}
MPI::~MPI(){}