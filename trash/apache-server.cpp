/**
 * Name: Apach Benchmarking Tool
 * Description: docker를 데몬모드로 실행하고, 소켓 오픈
 * Usage: 
 *  1. $ apachBench
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


int main()
{
    //docker를 정지 후 데몬모드로 실행
    //systemctl, service
    string runDaemon = "systemctl docker stop && sudo dockerd -H tcp://0.0.0.0:2375";
    command(runDaemon);
}