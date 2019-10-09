#include "Httpd-Server.h"
using namespace std;


void Httpd_Server::benchmark()
{
    //stop docker && re-run docker daemon with TCP
    string runDaemon = "sudo systemctl stop docker && sudo dockerd -H tcp://0.0.0.0:2375";
    command(runDaemon);
}


Httpd_Server::Httpd_Server() :Bench("httpd-server", "httpd-server")
{

}

Httpd_Server::~Httpd_Server()
{

}
