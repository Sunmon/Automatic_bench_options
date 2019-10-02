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
#define CONTAINER 0
#define HOST 1

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
    //TODO: OUPTPUT[0]바꾸기
    OUTPUT[CONTAINER] = NAME+ ":/AddedFiles/hpl-2.3/bin/x86_64/HPL.dat";
    OUTPUT[HOST] = argv[argc-1];


    for(int i = 2; i<argc-1; i++)
    {
        EXEC = EXEC + string(argv[i]) + " ";
    }

    //get image name to run
    // const char* IMG_NAME;
    // argc == 1 ? IMG_NAME = "" : IMG_NAME = argv[argc-1];


    // RUN Container
    RUN = RUN + NAME + " " + IMG;
    const char *command = RUN.c_str();
    system(command);


    //copy option to benchmark
    system("docker cp ~/Desktop/HPL/HPL.dat benchtest:/AddedFiles/hpl-2.3/bin/x86_64/");
    //wait for run container
    // sleep(3);

    //TODO: 숫자 바꾸기. cpu 랑 period랑. 
    // RUN benchmarking
    // for(int cpu = 3; cpu<4; cpu++)
    // {
    //     for(int period = 500; period <=1000; period += 100)
    //     {

            int period = 1000;
            int cpu = 3;

            string mkdir = "mkdir " + OUTPUT[HOST] + "/cpu_" + to_string(cpu);
            command = mkdir.c_str();
            system(command);
            //set cpu option
            string update = UPDATE + CPUSET + to_string(cpu) + CPUPERIOD + to_string(period) + CPUQUOTA + to_string(period) +  NAME;
            cout << update << endl;

            command = update.c_str();
            system(command);

            //run benchmarking
            // command = EXEC.c_str();
            // system(command);

            //get benchmark results
            // string temp = "docker cp " + OUTPUT[CONTAINER] + " " + OUTPUT[HOST];
            string temp = "docker cp " + OUTPUT[CONTAINER] + " " + OUTPUT[HOST] + "/" + "cpu_"+to_string(cpu)+ "/period_"+to_string(period);
            command = temp.c_str();
            cout << command <<endl;
            // string temp = "docker cp benchtest:/AddedFiles/hpl-2.3/bin/x86_64/HPL.dat ./hpl_bench/";
            // command = temp.c_str();
            system(command);


            //NOTE: 안기다리고 그냥 결과 나오면 다음꺼가 실행되기때문에 sleep 없어도 괜찮다!
            cout << ">>>>>>>>>>>>>>>>>\t complete cpu: " << cpu << "period:" << period << "\n";
            system("docker stop benchtest");
            return 0;

            //wait until benchmark complete
            // sleep(20);

          
    //     }
    // }

    // //TODO: exit
    return 0;
}



//만들어진 컨테이너 자원도 바꿀 수 있다.
//https://jungwoon.github.io/docker/2019/01/13/Docker-6/


//cpuset = 0-0 일때, 벤치 한 번 돌리는데 걸리는 시간: 21분 57초
//cpuset = 0-3 일때, 벤치 한 번 돌리는데 걸리는 시간: 11초