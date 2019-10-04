/**
 * Name: Apach Benchmarking Tool
 * Description: docker에서 Apach 컨테이너를 생성하고, 일정 시간마다 cpu 옵션 업데이트 
 * Usage: 
 *  1. $ apachBench [httpd이미지 이름] [컨테이너 이름]
 * Author: Sun-Jung Kim
**/

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>     //sleep()
#define CONTAINER 0
#define HOST 1
#define CORE 4      //TODO: 듀얼코어면 이 값을 2로 바꾸기

using namespace std;

string IMG;
string NAME;
string OUTPUT[2];
string NUM_CPU[4] = {"0", "0-1", "0-2", "0-3"}; //TODO: cpu 번호 설정 필요. "0", "0,2", "0,2,4", "0,2,4,6"일수도 있음
string EXEC;


//terminal에 명령어 전달
void command(string& strcmd)
{
    const char* cmd = strcmd.c_str();
    system(cmd); 
}

//directory 만들기
void makeDir(string dir)
{
    string mkdir = "mkdir " + dir;
    command(mkdir);
}


// set benchmark output directory in container
void initOutputDir()
{
    // cout << "Output directory in container\n  >>> ";
    // string temp;
    // getline(cin, temp);
    // cin.ignore();
    // OUTPUT[CONTAINER] = NAME + ":" + temp;
    OUTPUT[HOST] = "../out/" + NAME;

    //make output dir in host
    makeDir(OUTPUT[HOST]);
}


// set command to benchmarking
// ex: mpirun --allow-run-as-root -np 4 xhpl
void initExecCMD()
{
    cout << "Running exec command with\n  >>> ";
    string temp;
    getline(cin, temp);
    EXEC = "docker exec " + NAME + " " + temp;
}



void initContainer(int argc, char* argv[])
{
    IMG = argv[1];
    NAME = argv[2];
}


//NOTE: only for "HPL BENCHMARK"
// copy running option
void copyBenchOption(int cpu)
{
    string cp = "docker cp ../data/HPL.dat " + NAME+":/AddedFiles/hpl-2.3/bin/x86_64";
    command(cp);
}

void runContainer()
{
    string RUN = "docker run -dit --rm --name " + NAME + " " + IMG;
    command(RUN);
}


// set docker cpu option
void updateContainer(int cpu, int period, int quota)
{
    string s_period = to_string(period);
    string s_quota = to_string(quota);
    string update = 
        "docker update --cpuset-cpus=" + NUM_CPU[cpu] + " "
        "--cpu-period=" + s_period + " " +
        "--cpu-quota=" + s_quota + 
        " " + NAME;
    command(update);
}


// run benchmarking
void execContainer()
{
    command(EXEC);
}


// save output into host
void saveOutputToHost(int cpu, int period)
{
    string subDir = NUM_CPU[cpu] + "/" + "period_" + to_string(period);
    string getOutput = "docker cp " + OUTPUT[CONTAINER] + " " + OUTPUT[HOST] + "/" + subDir;
    command(getOutput);
}



// stop container
void stopContainer()
{
    string stop = "docker stop " + NAME;
    command(stop);
}


int main(int argc, char* argv[])
{
    initContainer(argc, argv);
    initOutputDir();
    // initExecCMD();
    
    //run container
    runContainer();

    //update container & run benchmark
    // for(int cpu = 0; cpu<CORE; cpu++)
    // {
        // makeDir(OUTPUT[HOST] + "/" + NUM_CPU[cpu]);
        for(int period = 100000; period <= 1000000; period += 100000)
        {
            updateContainer(0, period, period/2);
            sleep(360);
            // execContainer();
            // saveOutputToHost(cpu, period);
            // cout << ">>>\tfinish  cpu: " << cpu << " period: " << period <<"\t<<<\n";
        }
    // }

    //stop container
    stopContainer();
}