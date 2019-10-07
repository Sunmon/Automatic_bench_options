#include "Httpd-Server.h"
using namespace std;


void Httpd_Server::benchmark()
{
    //stop docker && rerun docker daemon with TCP
    string runDaemon = "sudo systemctl stop docker && sudo dockerd -H tcp://0.0.0.0:2375";
    command(runDaemon);
}

void Httpd_Server::runBenchTool(int cpu, int period, int quota)
{
    return;
}

Httpd_Server::Httpd_Server()
{

}

Httpd_Server::~Httpd_Server()
{

}