#include "Httpd-Server.h"
using namespace std;


void Httpd_Server::benchmark()
{
    //stop docker && re-run docker daemon with TCP
    string runDaemon = "sudo systemctl stop docker && sudo dockerd -H tcp://0.0.0.0:2375";
    command(runDaemon);
}

void Httpd_Server::runBenchTool(int cpu, int period, int quota){
    //Bench::runBenchTool이 순수 가상함수라서 자리 채울뿐
}



Httpd_Server::Httpd_Server() :Bench("httpd-server", "httpd-server")
{

}

Httpd_Server::~Httpd_Server()
{

}
