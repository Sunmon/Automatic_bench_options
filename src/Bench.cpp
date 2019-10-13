//Bench.h 구현 클래스
#include "Bench.h"
using namespace std;


/** public **/
//벤치마크 실행하기
void Bench::benchmark()
{
    init();
    runContainer();
    initContainer();

    // update container & run benchmark
    for(int cpu = 0; cpu < CORE; cpu++)
    {
        for(int period = 100000; period <= 1000000; period += 100000)
        {

            // int cpu = 1, period = 1000000;
            updateContainer(cpu, period, period/2);
            runBenchTool(cpu, period, period/2);
            saveRslt(cpu, period, period/2);

        }
    }

    stopContainer();
}    




//최대 코어 수 설정
void Bench::setCore(int num)
{
    this->CORE = num;
};


Bench::Bench(){
}

Bench::Bench(const string& img, const string& name)
{
    this->IMG = img;
    this->NAME =  name;
}

Bench::~Bench(){
}

//terminal에 명령어 전달
void Bench::command(const std::string& cmd)
{
    const char* cmdptr = cmd.c_str();
    system(cmdptr); 
}

//dir에 디렉토리 만들기
void Bench::makeDir(const std::string& dir)
{
    string mkdir = "mkdir " + dir;
    command(mkdir);
}




/** protected **/

//runoption과 DOCKER, 기본 output 폴더 초기화
void Bench::init()
{
    this->runOption = " -dit --rm --name " + NAME + " " + IMG;
    this->DOCKER = "docker ";

    //기본 output 폴더 만들기
    outDir = "../out/"+NAME+"/";
    makeDir(outDir);

    //json 환경파일 가져오기
    initJson();
}

void Bench::initContainer()
{
    return;
}


//config.json파일의 '_json'를 이용하여 컨테이너 초기화.
void Bench::initContainer(std::string _json)
{
    //해당 컨테이너 설정만 읽어오기
    config = config.get(_json, "");

    //copy data file into the container
    string data_host = config.get("data_host", "null").asString();
    string data_container = config.get("data_container", "null").asString();
    if(data_host != "null" && data_container != "null")
    {
        string cp = this->DOCKER + " cp " + data_host + " " + NAME + data_container;
        Bench::command(cp);

    }
}

// 컨테이너내에 저장된 결과파일을 호스트 컴퓨터로 복사
void Bench::saveRslt(int cpu, int period, int quota)
{
    return;
}

//FIXME: 삭제
// void Bench::initContainer(string data, string dest_dir)
// {
//    string _data =  config[NAME][data].asString();
//    string _dir = config[NAME][dest_dir].asString();
//    string cp = DOCKER + "cp " + _data + " " + NAME + dest_dir;
//    Bench:: command(cp);
// }


/** private **/

//config.json 파일 읽어서 config 변수에 저장
void Bench::initJson()
{
    //각종 설정을 모아둔 json파일 읽어오기
    ifstream jsonDir("../env/config.json");
    Json::Reader reader;
    reader.parse(jsonDir, config); // reader can also read strings


}

//runoption 더해서 실행
void Bench::runContainer()
{
    string run = this->DOCKER + " run " + this->runOption;
    command(run);
}


// set docker cpu option
void Bench::updateContainer(int cpu, int period, int quota)
{
    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period);
    string s_quota = to_string(quota);

    string update = DOCKER +
        " update --cpuset-cpus=" + s_cpu +
        " --cpu-period=" + s_period +
        " --cpu-quota=" + s_quota + " " + NAME;
    command(update);
}

// stop container
void Bench::stopContainer()
{
    string stop = DOCKER + " stop " + this->NAME;
    command(stop);
}