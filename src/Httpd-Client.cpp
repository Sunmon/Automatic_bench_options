//Httpd client
//server에 명령내려서 컨테이너 조작 & 호스트 자체에서 jmeter 실행
#include "Httpd-Client.h"
using namespace std;
Httpd_Client::Httpd_Client() : Bench("httpd", "httpd")
{

}

Httpd_Client::~Httpd_Client()
{

}

void Httpd_Client::runBenchTool(int cpu, int period, int quota)
{
    //TODO: env.json에 저장해두고 알아서 jmeter나 hpl dat같은거 위치 꺼내올수있게하자.
    string s_cpu = CPUSET[cpu];
    string s_period = to_string(period/1000);
    string s_quota = to_string(quota/1000);
    
    string jmeter = "~/Desktop/apache-jmeter-5.1.1/bin/jmeter";
    string jmx = "../data/jmeter-setup.jmx";
    
//TODO: jmeter 실행할때 주소 파라미터로 넘겨서 설정하는거..
    string runJmeter =  jmeter + " -n -t " + jmx + "-JHTTPSampler.domain=" + servAddr + " -l " + outDir + 
                        "cpus" + s_cpu + "_per" + s_period + "_quo" + s_quota + ".csv";
    command(runJmeter);
}

void Httpd_Client::init()
{
    Bench::init(); 
    cout << "Input server addr '\t'>>> ";
    getline(cin, servAddr);
    this -> runOption = servAddr + " -p 8080:80 " + runOption;
    this -> DOCKER += "-H " + servAddr + " ";
}
