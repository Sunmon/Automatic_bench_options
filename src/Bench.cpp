//Bench.h 구현 클래스
#include "Bench.h"
using namespace std;


/** public **/
//벤치마크 실행하기
void Bench::benchmark()
{
    init();
    runContainer();
    cpEnvToContainer();

    //FIXME: 테스트 후 cpu개수, period 정하기
    //update container & run benchmark
    // for(int cpu = 0; cpu < CORE; cpu++)
    // {
        // for(int period = 100000; period <= 1000000; period += 100000)
        // {

        // for(int cpu = 1; cpu < 2; cpu++)
        // {

            // for(int period = 1000000; period <= 1000000; period += 1000000)
            // {

                int cpu = 1; int period = 100000;
            updateContainer(cpu, period, period/2);
            runBenchTool(cpu, period, period/2);
            saveRslt(cpu, period, period/2);
        // }
    // }

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

//초기화
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


//호스트나 인터넷에 있는 환경설정을 컨테이너 내로 복사
void Bench::cpEnvToContainer()
{
    return;
}

// 컨테이너내에 저장된 결과파일을 호스트 컴퓨터로 복사
void Bench::saveRslt(int cpu, int period, int quota)
{
    return;
}


/** private **/

//config.json 파일 읽어서 config 변수에 저장
void Bench::initJson()
{
    //각종 설정을 모아둔 json파일 읽어오기
    ifstream jsonDir("../env/config.json");
    Json::Reader reader;
    reader.parse(jsonDir, config); // reader can also read strings
}

void Bench::runContainer()
{
    string run = DOCKER + "run " + runOption;
    command(run);
}


// set docker cpu option
void Bench::updateContainer(int cpu, int period, int quota)
{
    manVar[CPUS] = CPUSET[cpu];
    manVar[PER] = to_string(period);
    manVar[QUO] = to_string(quota);

    string update = DOCKER +
        "update --cpuset-cpus=" + manVar[CPUS] + " " +
        "--cpu-period=" + manVar[PER] + " " +
        "--cpu-quota=" + manVar[QUO] + " " + NAME;
    command(update);
}

// stop container
void Bench::stopContainer()
{
    string stop = DOCKER+ "stop " + this->NAME;
    command(stop);
}