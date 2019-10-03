#include <iostream>
#include <stdlib.h>
#include <cstring>
#define CONTAINER 0
#define HOST 1

using namespace std;

// hplBench [hpl img]
string IMG;
string NAME;
string OUTPUT[2];
string NUM_CPU[4] = {"0", "0,2", "0,2,4", "0,2,4,6"};
string EXEC;
// const char* command;


void command(string& strcmd)
{
    const char* cmd = strcmd.c_str();
    system(cmd); 

}

void makeDir(string dir)
{
    string mkdir = "mkdir " + dir;
    command(mkdir);
}


// set benchmark output directory in container
// ex: /AddedFiles/hpl-2.3/bin/x86_64/HPL.out
void initOutputDir()
{
    cout << "Output directory in container\n  >>> ";
    string temp;
    getline(cin, temp);
    // cin.ignore();
    OUTPUT[CONTAINER] = NAME + ":" + temp;
    OUTPUT[HOST] = "../output/" + NAME;

    //make output dir in host
    makeDir(OUTPUT[HOST]);


    // cout << endl << endl;
    // cout << OUTPUT[CONTAINER] << endl;
    // cout << OUTPUT[HOST] << endl;
}


// set command to benchmarking
// ex: mpirun --allow-run-as-root -np 4 xhpl
void initExecCMD()
{
    cout << "Running exec command with\n  >>> ";
    string temp;
    getline(cin, temp);
    EXEC = "docker exec " + NAME + " " + temp;
    // cout << EXEC;
}


void initArgs(int argc, char* argv[])
{
    IMG = argv[1];
    NAME = IMG;
}




//NOTE: only for "HPL BENCHMARK"
// copy running option
void copyBenchOption()
{
    string cp = "docker cp ~/Desktop/HPL/HPL.dat " + NAME+":/AddedFiles/hpl-2.3/bin/x86_64";
    command(cp);
}

void runContainer()
{
    string RUN = "docker run -dit --rm --name " + NAME + " " + IMG;
    command(RUN);
}

void updateContainer(int cpu, int period)
{
    //set cpu option
    string s_period = to_string(period);
    string s_quota = to_string((period/2));
    string update = 
        "docker update --cpuset-cpus=" + NUM_CPU[cpu] + " "
        "--cpu-period=" + s_period + " " +
        "--cpu-quota=" + s_quota + 
        " " + NAME;
        
    command(update);
}

void execContainer()
{
    command(EXEC);
}

void saveOutputToHost(int cpu, int period)
{
    string subDir = NUM_CPU[cpu] + "/" + "period_" + to_string(period);
    string getOutput = "docker cp " + OUTPUT[CONTAINER] + " " + OUTPUT[HOST] + "/" + subDir;
    command(getOutput);
}


void stopContainer()
{
    string stop = "docker stop " + NAME;
    command(stop);
}

int main(int argc, char* argv[])
{

    initArgs(argc, argv);
    initOutputDir();
    initExecCMD();
    
    //run container
    runContainer();
    copyBenchOption();  //NOTE: only for HPL bench 

    // //update container
    // //TODO: cpu set 
    // // for(int cpu = 0; cpu<4; cpu++)
    // // {

        int cpu = atoi(argv[2]);
        makeDir(OUTPUT[HOST] + "/" + NUM_CPU[cpu]);
        for(int period = 10000; period <= 100000; period += 10000)
        {
            updateContainer(cpu, period);
            execContainer();
            saveOutputToHost(cpu, period);
        }

    // }

    // //stop container
    stopContainer();
}