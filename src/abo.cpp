/**
 * Name: Automatic Bench Options
 * Description: docker 벤치마킹 자동화 툴
 * cpuset, cpu_quota, cpu_period를 조절해서
 * 테스트한 결과를 file로 작성
 * Usage: $abo [testing image name] [output name]
 * Author: Sun-Jung Kim
 **/

#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
    //get docker image name
    string cmd = "docker run ";
    const char* IMG_NAME = argv[argc-1];

    cmd+= IMG_NAME;

    const char *cmdptr = cmd.c_str();    //str을 char*로 변환
    system(cmdptr);
    return 0;
}