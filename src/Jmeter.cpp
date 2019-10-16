//server에 명령내려서 컨테이너 조작 & 호스트 자체에서 jmeter 실행
#include "Jmeter.h"
using namespace std;

void Jmeter::runBenchTool(int cpu, int period, int quota)
{
    string jmeter = config["workdir"].asString();
    string jmx = config["data_host"].asString();
    string serv = " -Jserver.IP="+config["server.IP"].asString();
    string user = " -Juser="+config["users"].asString();
    string rampup = " -Jrampup="+config["rampup"].asString();
    string threads = " -Jthreads="+config["threads"].asString();
    string run = jmeter + " -n " + serv + user + rampup + threads + " -t " + jmx + "\\";
    // string s_cpu = CPUSET[cpu];
    // string s_period = to_string(period/1000);
    // string s_quota = to_string(quota/1000);

    // string jmeter = config["jmeter"]["jmeterPath"].asString();
    // string jmx = config["jmeter"]["jmxPath"].asString();
    // string serv = "-Jserver.IP="+servAddr;
    // string user = "-Juser="+config["jmeter"]["users"].asString();
    // string rampup = "-Jrampup="+config["jmeter"]["rampup"].asString();
    // string threads = "-Jthreads="+config["jmeter"]["threads"].asString();
    // string run = jmeter + " -n " + serv + " " + user + " " + rampup + " " + threads + " -t " + jmx + " -l " + outDir + 
    //                     "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota + ".csv";
    command(run);
}
void Jmeter::saveRslt(int cpu, int period, int quota)
{
    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);

    string result_to =  " -l " + outDir + "/cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota + ".csv";
    command(result_to);




}


void Jmeter::initContainer(){ //do nothing
}


//httpd-client와 동일
void Jmeter::init()
{
    // Bench::init();
    this -> runOption = " -p " + config["server.port"].asString() + ":80" + runOption;
    this -> DOCKER = "docker -H " + config["server.IP"].asString() + " "; //servAddr + " ";


    //기본 output 폴더 만들기
    outDir = "../out/"+NAME;
    makeDir(outDir);

    //json 환경파일 가져오기
    Bench::initJson("jmeter");
  
}

// void Jmeter::init()
// {
    // Bench::init(); 
    // this -> servAddr = config["jmeter"]["server.IP"].asString();
    // this -> runOption = " -p " + config["jmeter"]["server.port"].asString() + ":80" + runOption;
    // this -> DOCKER += "-H " + servAddr + " ";
// }

Jmeter::Jmeter(){}
Jmeter::Jmeter(const std::string &img, const std::string &name) : Bench(img, name){}

Jmeter::~Jmeter(){}