//Bench.h 구현 클래스
#include "Bench.h"
using namespace std;


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

void Bench::init()
{

    this->defaultOpt = " -dit --rm --name " + NAME + " " + IMG;
    this->DOCKER = "docker ";


    //기본 output 폴더 만들기
    outDir = "../out/"+NAME+"/";
    makeDir(outDir);

    // this->IMG = img;
    // this->NAME =  name;
    // this->defaultOpt = " -dit --rm --name " + NAME + " " + IMG;
}


// void Bench::createContainer(const std::string& opt)
// {
//     CREATE = opt + CREATE; 
//     command(CREATE);
// }

void Bench::runContainer()
{
    string run = DOCKER + "run " + defaultOpt;
    command(run);
}


// set docker cpu option
void Bench::updateContainer(int cpu, int period, int quota)
{
    manVar[CPUS] = CPUSET[cpu];
    manVar[PER] = to_string(period);
    manVar[QUO] = to_string(quota);
    // string s_cpu = CPUSET[cpu];
    // string s_period = to_string(period);
    // string s_quota = to_string(quota);
    string update = DOCKER +
        "update --cpuset-cpus=" + manVar[CPUS] + " " +
        "--cpu-period=" + manVar[PER] + " " +
        "--cpu-quota=" + manVar[QUO] + " " + NAME;
    command(update);
}


void Bench::cpEnvToContainer()
{
    return;
}


//이 함수 실행하면 된다
void Bench::benchmark()
{
    // createContainer();
    init();
    runContainer();
    cpEnvToContainer();

    //update container & run benchmark
    for(int cpu = 0; cpu < CORE; cpu++)
    {
        for(int period = 100000; period <= 1000000; period += 100000)
        {

        // for(int cpu = 1; cpu < 2; cpu++)
        // {

            // for(int period = 1000000; period <= 1000000; period += 1000000)
            // {

            updateContainer(cpu, period, period/2);
            runBenchTool(cpu, period, period/2);
            // cout << ">>>\tfinish  cpu: " << cpu << " period: " << period <<"\t<<<\n";
        }
    }

    stopContainer();
}    

// stop container
void Bench::stopContainer()
{
    string stop = DOCKER+ "stop " + this->NAME;
    command(stop);
}


void Bench::setCore(int num)
{
    this->CORE = num;
};


Bench::Bench()
{
    // defaultOpt = " -dit --rm --name " + NAME + " " + IMG;
}

Bench::Bench(const string& img, const string& name)
{
    this->IMG = img;
    this->NAME =  name;
    

    // init();

}
Bench::~Bench(){}