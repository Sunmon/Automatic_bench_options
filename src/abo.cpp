/**
 * Name: Automatic Bench Options
 * Description: docker 벤치마킹 자동화 툴
 * cpuset, cpu_quota, cpu_period를 조절해서
 * 테스트한 결과를 file로 작성
 * Usage: $abo [testing program name]
 * Author: Sun-Jung Kim
 * EXAMPLE: ./abo hpl , ./abo httpd-server, ./abo httpd-client
 **/

#include "parson.h"
#include "BenchFacotry.h"
#include "Bench.h"
#include "HPL.h"
#include "Httpd-Server.h"
#include "Httpd-Client.h"
using namespace std;

int main(int argc, char *argv[])
{
    //prameter 안 들어오면 종료
    if(argc < 2)
    {
        cout << "Usage:: $./abo [bench name]\n";
        exit(-1);
    }


    // 프로그램 실행
    string program = string(argv[1]);
    Bench* bench = selectBench(program);
    bench->benchmark();
}