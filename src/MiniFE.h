//minife benchmark
#pragma once
#include "Bench.h"

class MiniFE : public Bench
{
    private:
        void init();
        void runBenchTool(int cpu, int period, int quota);      // 벤치마크 툴 돌리기. jemter, hpl 이런거
        // void cpEnvToContainer();                                    // 컨테이너 운영에 필요한 환경설정 파일 복사해오기
        void saveRslt(int cpu, int period, int quota);              // 결과 호스트 컴퓨터에 저장하기

    public:
        MiniFE();
        ~MiniFE();
};