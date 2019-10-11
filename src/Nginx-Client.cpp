//Nginx client
//server에 명령내려서 컨테이너 조작 & 호스트 자체에서 jmeter 실행
#include "Nginx-Client.h"
using namespace std;

void Nginx_Client::runBenchTool(int cpu, int period, int quota)
{
    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);

    string jmeter = config["jmeter"]["jmeterPath"].asString();
    string jmx = config["jmeter"]["jmxPath"].asString();
    string serv = "-Jserver.IP="+servAddr;
    string user = "-Juser="+config["jmeter"]["users"].asString();
    string rampup = "-Jrampup="+config["jmeter"]["rampup"].asString();
    string threads = "-Jthreads="+config["jmeter"]["threads"].asString();
    string run = jmeter + " -n " + serv + " " + user + " " + rampup + " " + threads + " -t " + jmx + " -l " + outDir + 
                        "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota + ".csv";
    command(run);
}

void Nginx_Client::init()
{
    Bench::init(); 
    this -> servAddr = config["jmeter"]["server.IP"].asString();
    this -> runOption = " -p " + config["jmeter"]["server.port"].asString() + ":80" + runOption;
    this -> DOCKER += "-H " + servAddr + " ";
}

Nginx_Client::Nginx_Client() : Bench("nginx", "nginx"){}

Nginx_Client::~Nginx_Client(){}