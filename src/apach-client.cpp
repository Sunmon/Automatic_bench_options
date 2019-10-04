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
#define CONTAINER_UPDATE_TIME 360   //docker container에서 cpuset, period 바꾸는 간격
using namespace std;
string NUM_CPU[4] = {"0", "0-1", "0-2", "0-3"}; // cpu 번호 설정 필요. "0", "0,2", "0,2,4", "0,2,4,6"일수도 있음
string OUPUT[2];

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




int main()
{
    //cli에 명령 내리기
    string jmeter = "~/Desktop/apache-jmeter-5.1.1/bin/jmeter -n ";
    string jmx = "~/Desktop/Automatic_bench_options/data/Apach-client.jmx";
    // string jmx = "~/Desktop/Automatic_bench_options/data/Test_Plan.jmx";
    string outDir = "~/Desktop/Automatic_bench_options/out/";
    string request;
    time_t start;
    time_t finish;

    for(int period = 100000; period <= 1000000; period += 100000)
    {
        request = jmeter + "-t " + jmx + " -l " + outDir + to_string(period) + ".csv";
        cout << ">>>\tstart jmeter\n";
        time(&start);
        command(request);
        time(&finish);
        int expend = finish - start;
        cout << "<<<\texpended time : " << finish - start << "\n";
        if(expend < CONTAINER_UPDATE_TIME) sleep(CONTAINER_UPDATE_TIME - expend);
    }

    // string outDir = "~/Desktop/Automatic_bench_options/out/test1.csv";
    // string output;
    // ./jmeter -n -t ~/Desktop/Automatic_bench_options/data/Apach-client.jmx -l ~/Desktop/Automatic_bench_options/out/test1.csv

    // string request = jmeter + "-t " + jmx + " -l " + outDir;
    // command(request);

}