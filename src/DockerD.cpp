#include "include/DockerD.h"
using namespace std;


void DockerD::benchmark()
{
    //stop docker && re-run docker daemon with TCP
    string runDaemon = "sudo systemctl stop docker && sudo dockerd -H tcp://0.0.0.0:2375";
    command(runDaemon);
}

void DockerD::runBenchTool(int cpu, int period, int quota){
    //Bench::runBenchTool이 순수 가상함수라서 자리 채울뿐
}

void DockerD::init(){//do nothing
}                 // runOption, DOCKER, outDir 초기화
void DockerD::initContainer(){//do nothing
}                               // 컨테이너 운영에 필요한 환경설정 파일 복사해오기
void DockerD::saveRslt(int cpu, int period, int quota){//do nothing
}

DockerD::DockerD() :Bench("DockerD", "DockerD")
{

}

DockerD::~DockerD()
{

}
