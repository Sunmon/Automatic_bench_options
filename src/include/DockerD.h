//run docker daemon
#pragma once
#include "Bench.h"
#include <cstring>

class DockerD : public Bench
{
    private:
        void benchmark() override;
        void runBenchTool(int cpu, int period, int quota) override;
        void init() override;                 // runOption, DOCKER, outDir 초기화
        void initContainer() override;                               // 컨테이너 운영에 필요한 환경설정 파일 복사해오기
        void saveRslt(int cpu, int period, int quota) override; // 결과 호스트 컴퓨터에 저장하기
    public:
        DockerD();
        virtual ~DockerD();
};