#include "HPL.h"
using namespace std;

void HPL::runProgram()
{

}

// void HPL::benchmark()
// {

// }

HPL::HPL() : Bench("blackmilk274/hpl", "hpl")
{
    // Bench::IMG = "blackmilk274/hpl";
    // Bench::NAME = "hpl";
    Bench::CREATE = "docker create ";
    Bench::RUN = "docker run" + Bench::defaultOpt;
    // Bench::UPDATE = "";
    // Bench::IMG = string("asdf");
    // const string& IMG = "blackmilk274/hpl";
    // const string& NAME = "hpl";
}

HPL::~HPL()
{

}