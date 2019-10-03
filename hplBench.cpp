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
string NUM_CPU[4] = {"0", "0,2", "0,2,4", "0,2,4,8"};
string EXEC;
// const char* command;


void command(string& strcmd)
{
    const char* cmd = strcmd.c_str();
    system(cmd); 

}


// set benchmark output directory in container
// ex: /AddedFiles/hpl-2.3/bin/x86_64/HPL.out
void initOutputDir()
{
    cout << " output directory in container: ";
    string temp;
    cin >> temp;
    OUTPUT[CONTAINER] = NAME + ":" + temp;
    OUTPUT[HOST] = "../output/" + NAME;
}


// set command to benchmarking
// ex: mpirun --allow-run-as-root -np 4 xhpl
void initExecCMD()
{
    cout << " running exec command with: ";
    string temp;
    getline(cin, temp);
    EXEC = "docker exec " + NAME + " " + temp;
}


void initArgs(int argc, char* argv[])
{
    IMG = argv[1];
    NAME = IMG;
}


void createOutputDir(string mkdir)
{
    // string mkdir = OUTPUT[HOST];
    command(mkdir);
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
    string RUN = "docker run -dit --rm --name " + NAME;
    command(RUN);
}

void updateContainer(int cpu, int period)
{
    //set cpu option
    string s_period = to_string(period);
    string s_quota = to_string((period/2));
    string update = 
        "docker update --cpuset-cpus=" + NUM_CPU[cpu] +
        "--cpu-period=" + s_period +
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
    copyBenchOption();  //NOTE: only for HPL bench 
    createOutputDir(OUTPUT[HOST]);
    
    //run container
    runContainer();

    //update container
    //TODO: cpu set 
    // for(int cpu = 0; cpu<4; cpu++)
    // {

        int cpu = 3;
        createOutputDir("mkdir " + OUTPUT[HOST] + "/" + NUM_CPU[cpu]);
        for(int period = 10000; period <= 100000; period += 10000)
        {
            updateContainer(cpu, period);
            execContainer();
            saveOutputToHost(cpu, period);
        }

    // }

    //stop container
    stopContainer();
}