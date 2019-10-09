//Httpd client
//server에 명령내려서 컨테이너 조작 & 호스트 자체에서 jmeter 실행
#include "Httpd-Client.h"
using namespace std;

void Httpd_Client::runBenchTool(int cpu, int period, int quota)
{
    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);

    //TODO: link에서 읽어오기
    string jmeter = config["jmeter"]["jmeterPath"].asString();
    string jmx = config["jmeter"]["jmxPath"].asString();
    // string jmeter = "~/Desktop/apache-jmeter-5.1.1/bin/jmeter";
    // string jmeter = "~/Desktop/apache-jmeter-5.1.1/bin/jmeter"; jmeterpath
    string serv = "-Jserver.IP="+servAddr;
    string user = "-Juser="+config["jmeter"]["users"].asString();
    string rampup = "-Jrampup="+config["jmeter"]["rampup"].asString();
    string threads = "-Jthreads="+config["jmeter"]["threads"].asString();
    string run = jmeter + " -n " + serv + " " + user + " " + rampup + " " + threads + " -t " + jmx + " -l " + outDir + 
                        "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota + ".csv";
    // string runJmeter =  jmeter  + " -n -t " + jmx + "-Jserver.IP=" + servAddr + " -l " + outDir + 
                        // "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota + ".csv";
    command(run);
}

void Httpd_Client::init()
{
    Bench::init(); 
    this -> servAddr = config["jmeter"]["server.IP"].asString();
    this -> runOption = servAddr + " -p " + config["jmeter"]["server.port"].asString() + ":80" + runOption;
    this -> DOCKER += "-H " + servAddr + " ";
}

Httpd_Client::Httpd_Client() : Bench("httpd", "httpd"){}

Httpd_Client::~Httpd_Client(){}