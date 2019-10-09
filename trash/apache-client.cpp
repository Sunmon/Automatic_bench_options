/**
 * Name: Apach client-side test
 * Description: apach client 접속 자동화.
 * 아파치에 접속한 결과 (latency)를 저장
 * Usage: 
 * Author: Sun-Jung Kim
**/

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <unistd.h>     //sleep()
#define CORE 4
#define CONTAINER_UPDATE_TIME 360   //docker container에서 cpuset, period 바꾸는 간격
#define HOST 1
using namespace std;
string NUM_CPU[4] = {"0", "0-1", "0-2", "0-3"}; // cpu 번호 설정 필요. "0", "0,2", "0,2,4", "0,2,4,6"일수도 있음
string OUTPUT[2];

string IMG;
string NAME;
string EXEC;
string PORT = "tcp://0.0.0.0:2375";

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

// // save output into host
// void saveOutputToHost(int cpu, int period)
// {
//     string subDir = NUM_CPU[cpu] + "/" + "period_" + to_string(period);
//     string getOutput = "docker cp " + OUTPUT[CONTAINER] + " " + OUTPUT[HOST] + "/" + subDir;
//     command(getOutput);
// }

void runContainer()
{
    string RUN = "docker -H " + PORT + " " + "run -dit --rm --name " + NAME + " -p 8080:80 " +  IMG;
    command(RUN);
}

void initContainer(int argc, char* argv[])
{
    IMG = "httpd";
    NAME = "apache";
    OUTPUT[HOST]= "../out/"+NAME;
    makeDir(OUTPUT[HOST]);

    // NAME = IMG;
}

// set docker cpu option
void updateContainer(int cpu, int period, int quota)
{
    string s_period = to_string(period);
    string s_quota = to_string(quota);
    string update = "docker -H " + PORT + " update "+
        "--cpuset-cpus=" + NUM_CPU[cpu] + " " +
        "--cpu-period=" + s_period + " " +
        "--cpu-quota=" + s_quota + 
        " " + NAME;
    command(update);
    cout << "docker updated\n" ;
}


void runJmeter(string outdir)
{
     //cli에 명령 내리기
    string jmeter = "~/Desktop/apache-jmeter-5.1.1/bin/jmeter";
    // string jmx = "~/Desktop/Automatic_bench_options/data/Apach-client.jmx";
    string jmx = "../data/Apach-client.jmx";
    // string jmx = "~/Desktop/Automatic_bench_options/data/Test_Plan.jmx";

    // string outDir = "~/Desktop/Automatic_bench_options/out/";
    string request = jmeter + " -n -t " + jmx + " -l " + outdir +".csv";
    command(request);
}


// stop container
void stopContainer()
{
    string stop = "docker -H " + PORT + " stop " + NAME;
    command(stop);
}


int main(int argc, char* argv[])
{
    string request;
    time_t start;
    time_t finish;

    initContainer(argc, argv);
    runContainer();

    // int period = 100000;
    // int cpu = 3;

    cout << "makeDir" << endl;
 //update container & run benchmark
    for(int cpu = 0; cpu<CORE; cpu++)
    {
        makeDir(OUTPUT[HOST] + "/" + NUM_CPU[cpu]);
        for(int period = 100000; period <= 1000000; period += 100000)
        {
            updateContainer(cpu, period, period/2);
            runJmeter(OUTPUT[HOST]+"/"+NUM_CPU[cpu]+"/"+to_string(period)); //NOTE: only for jmeter
            cout << ">>>\tfinish  cpu: " << cpu << " period: " << period <<"\t<<<\n";
        }
    }

    //stop container
    stopContainer();

}