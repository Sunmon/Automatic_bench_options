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
// string NUM_CPU[4] = {"0", "0,2", "0,2,4", "0,2,4,6"};
string NUM_CPU[4] = {"0", "0-1", "0-2", "0-3"};

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
void copyBenchOption(int cpu)
{
    // string cp;
    // switch(cpu)
    // {
        // case 0 : cp = "docker cp ~/Desktop/HPL/HPL_0.dat "; break;
        // case 1 : cp = "docker cp ~/Desktop/HPL/HPL_1.dat "; break;
        // case 2 : cp = "docker cp ~/Desktop/HPL/HPL_2.dat "; break;
        // case 3 : cp = "docker cp ~/Desktop/HPL/HPL_3.dat "; break;
        // default: cp = "docker cp ~/Desktop/HPL/HPL.dat "; 
    // }
    // cp = cp + NAME + ":/AddedFiles/hpl-2.3/bin/x86_64/HPL.dat";
    string cp = "docker cp ~/Desktop/HPL/HPL.dat " + NAME+":/AddedFiles/hpl-2.3/bin/x86_64";
    cout << cp << endl;
    command(cp);
}

void runContainer()
{
    string RUN = "docker run -dit --rm --name " + NAME + " " + IMG;
    command(RUN);
}

void updateContainer(int cpu, int period, int quota)
{
    //set cpu option
    string s_period = to_string(period);
    string s_quota = to_string(quota);
    string update = 
        "docker update --cpuset-cpus=" + NUM_CPU[cpu] + " "
        "--cpu-period=" + s_period + " " +
        "--cpu-quota=" + s_quota + 
        " " + NAME;


        cout << ">>>\t" << update << endl;
        
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

    // //update container
    for(int cpu = 0; cpu<4; cpu++)
    {

        // int cpu = atoi(argv[2]);
        // int cpu = 2;

        // int period = 10000;
        copyBenchOption(cpu);  //NOTE: only for HPL bench 
        makeDir(OUTPUT[HOST] + "/" + NUM_CPU[cpu]);
        for(int period = 100000; period <= 1000000; period += 100000)
        {
            updateContainer(cpu, period, period/2);
            execContainer();
            saveOutputToHost(cpu, period);
            cout << ">>>\tfinish  cpu: " << cpu << " period: " << period << endl;
        }

    }

    //stop container
    stopContainer();
}