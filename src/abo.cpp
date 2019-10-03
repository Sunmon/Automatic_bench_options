/**
 * Name: Automatic Bench Options
 * Description: docker 벤치마킹 자동화 툴
 * cpuset, cpu_quota, cpu_period를 조절해서
 * 테스트한 결과를 file로 작성
 * Usage: $abo [testing image name] [run bench option] [output name]
 * Author: Sun-Jung Kim
 * EXAMPLE: ./abo hpl:benchtest mpirun --allow-run-as-root -np 4 ./hpl_bench
 **/


#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>     //sleep()
#define CONTAINER 0
#define HOST 1

using namespace std;

int main(int argc, char* argv[])
{
    //set docker command
    string RUN = "docker run -dit --rm --name ";
    const string IMG = argv[1];
    const string NAME = IMG;
    const string UPDATE = "docker update ";
    const string CPUSET = " --cpuset-cpus=0-";
    const string CPUPERIOD = " --cpu-period=";
    const string CPUQUOTA = " --cpu-quota=";
    string EXEC = "docker exec " + NAME + " ";
    string OUTPUT[2];
    OUTPUT[CONTAINER] = NAME+ ":/AddedFiles/hpl-2.3/bin/x86_64/HPL.out";
    OUTPUT[HOST] = "../output/" + NAME;
    string CPU_NUM[4] = {"0", "0,2", "0,2,4", "0,2,4,6"};

    for(int i = 2; i<argc; i++)
    {
        EXEC = EXEC + string(argv[i]) + " ";
    }

    // RUN Container
    RUN = RUN + NAME + " " + IMG;
    const char *command = RUN.c_str();
    system(command);


    //copy option to benchmark
    string cp = "docker cp ~/Desktop/HPL/HPL.dat " + NAME+":/AddedFiles/hpl-2.3/bin/x86_64";
    command = cp.c_str();
    system(command);
    system(("mkdir "+ OUTPUT[HOST]).c_str());

    //TODO: hpl은 프로세서 수 늘리면 HPL.dat도 고쳐야 함.
    //TODO: 숫자 바꾸기. cpu 랑 period랑. 
    // RUN benchmarking
    // for(int cpu = 3; cpu<4; cpu++)
    // {
            // int period = 1000;
            // int cpu = 3;


        int cpu = 0;

        //make saving directory
        string dir = OUTPUT[HOST] + "/cpu_" + CPU_NUM[cpu];
        string mkdir = "mkdir " + dir;
        command = mkdir.c_str();
        system(command);

        for(int period = 10000; period <=100000; period += 10000)
        {

            //set cpu option
            string update = UPDATE + CPUSET + CPU_NUM[cpu] + CPUPERIOD + to_string(period) + CPUQUOTA + to_string(period) +  " " +NAME;
            command = update.c_str();
            system(command);

            //run benchmarking
            command = EXEC.c_str();
            system(command);

            //get benchmark results
            string result = "docker cp " + OUTPUT[CONTAINER] + " " + dir + "/period_"+to_string(period);

            // cout << result << endl;
            command = result.c_str();

            // string temp = "docker cp benchtest:/AddedFiles/hpl-2.3/bin/x86_64/HPL.dat ./hpl_bench/";
            // command = temp.c_str();
            system(command);


            //NOTE: 안기다리고 그냥 결과 나오면 다음꺼가 실행되기때문에 sleep 없어도 괜찮다!
            cout << ">>>>>>>>>>>>>>>>>\t complete cpu: " << cpu << "period:" << period << "\n";
            // system("docker stop benchtest");
            //wait until benchmark complete
            // sleep(20);

          
        // }
    // }

    // //TODO: docker stop
    string stop = "docker stop " + NAME;
    command = stop.c_str();
    system(command);
    return 0;
}



//만들어진 컨테이너 자원도 바꿀 수 있다.
//https://jungwoon.github.io/docker/2019/01/13/Docker-6/