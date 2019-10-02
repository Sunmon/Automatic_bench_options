/**
 * Name: Automatic Bench Options
 * Description: docker 벤치마킹 자동화 툴
 * cpuset, cpu_quota, cpu_period를 조절해서
 * 테스트한 결과를 file로 작성
 * Usage: $abo [testing image name] [run bench option] [output name]
 * Author: Sun-Jung Kim
 **/

#include <iostream>
#include <stdlib.h>
#include <cstring>
// #include <Windows.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
    //set docker command
    string RUN = "docker run -dit --rm --name ";
// mpirun --allow-run-as-root -np 4 ./xhpl";
    const string IMG = argv[1];
    const string NAME = " benchtest";
    const string UPDATE = "docker update ";
    const string CPUSET = " --cpuset-cpus=0-";
    const string CPUPERIOD = " --cpu-period=";
    const string CPUQUOTA = " --cpu-quota=";
    string EXEC = "docker exec " + NAME + " ";
    string OUTPUT[2];
    OUTPUT[0] = NAME+ ":/AddedFiles/hpl-2.3/bin/x86_64/HPL.out";
    OUTPUT[1] = argv[argc-1];


    for(int i = 2; i<argc-1; i++)
    {
        EXEC = EXEC + string(argv[i]) + " ";
    }

    //get image name to run
    // const char* IMG_NAME;
    // argc == 1 ? IMG_NAME = "" : IMG_NAME = argv[argc-1];

    // RUN Container
    RUN = RUN + NAME + " " + IMG;
    const char *COMMAND = RUN.c_str();
    system(COMMAND);


    // //TODO: 숫자 바꾸기. cpu 랑 period랑. 
    // // RUN benchmarking
    // for(int cpu = 3; cpu<4; cpu++)
    // {
    //     for(int period = 500; period <=1000; period += 100)
    //     {

    //         //set cpu option
    //         string update = UPDATE + CPUSET + to_string(cpu) + CPUPERIOD + to_string(period) + NAME;
    //         COMMAND = update.c_str();
    //         system(COMMAND);

    //         //run benchmarking
    //         COMMAND = EXEC.c_str();
    //         system(COMMAND);




    //         //wait until benchmark complete
    //         sleep(20);

    //         //get benchmark results
    //         COMMAND = ("docker cp " + OUTPUT[1] + " " + OUTPUT[2] + "/" + "cpu_"+to_string(cpu)+ "__peiod_"+to_string(period)).c_str();
    //         system(COMMAND);
    //     }
    // }

    // //TODO: exit
    return 0;
}



//만들어진 컨테이너 자원도 바꿀 수 있다.
//https://jungwoon.github.io/docker/2019/01/13/Docker-6/


//cpuset = 0-0 일때, 벤치 한 번 돌리는데 걸리는 시간: 21분 57초
//cpuset = 0-3 일때, 벤치 한 번 돌리는데 걸리는 시간: 11초