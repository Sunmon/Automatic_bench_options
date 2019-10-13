/**
 * Name: Automatic Bench Options
 * Description: docker 벤치마킹 자동화 툴
 * cpuset, cpu_quota, cpu_period를 조절해서
 * 테스트한 결과를 file로 작성
 * Usage: $abo [testing program name]
 * Author: Sun-Jung Kim
 * EXAMPLE: ./abo hpl , ./abo httpd-server, ./abo httpd-client
 **/

#include "BenchFacotry.h"
using namespace std;

void testingjson()
{
    Json::Value config;
    ifstream jsonDir("../env/config.json");
    Json::Reader reader;
    reader.parse(jsonDir, config); // reader can also read strings
    cout << "is there json? " << endl;
    // config = config["HPL"];
    config = config.get("HPL","");
    cout << config.get("dat","") << endl;
}

int main(int argc, char *argv[])
{
    //prameter 안 들어오면 종료
    if(argc < 2)
    {
        cout << "Usage:: $./abo [bench name]\n";
        exit(-1);
    }

    testingjson();

    // 프로그램 실행
    // string program = string(argv[1]);
    // Bench* bench = selectBench(program);


    // bench->benchmark();
}