#include "Bench.h"
#include "HPL.h"
#include "Httpd-Server.h"
using namespace std;

int main()
{
    // Bench* ptr = new HPL();
    Bench* ptr = new Httpd_Server();
    // Bench* ptr = new Httpd_Server();

    ptr->benchmark();
    // ptr-> createContainer();
    // ptr->updateContainer();
    
}