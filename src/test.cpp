#include "Bench.h"
#include "HPL.h"
using namespace std;

int main()
{
    // Bench* ptr = new HPL();
    // Bench* ptr = new HPL();
    Bench* ptr = new HPL();
    // Bench * ptr = new Bench();
    // ptr->command("asdf");
    // Bench* ptr = new Bench("asdf", "qwer");
    ptr->benchmark();
    // ptr-> createContainer();
    // ptr->updateContainer();
    
}