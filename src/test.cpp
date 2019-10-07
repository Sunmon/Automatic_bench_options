#include "Bench.h"
#include "HPL.h"
#include "Httpd-Server.h"
#include "Httpd-Client.h"
using namespace std;

int main()
{
    // Bench* ptr = new HPL();
    // Bench* ptr = new Httpd_Server();
    // Bench* ptr = new Httpd_Server();
    Bench* ptr = new Httpd_Client();
    // ptr->init();
    ptr->benchmark();


    // ptr->benchmark();
    // ptr-> createContainer();
    // ptr->updateContainer();
    
}