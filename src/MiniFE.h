//minife benchmark
#pragma once
#include "MPI.h"

class MiniFE : public MPI
{
    private:
        void init() override;
        void initContainer() override;
        void runBenchTool(int cpu, int period, int quota);      // 벤치마크 툴 돌리기. jemter, hpl 이런거
        // void saveRslt(int cpu, int period, int quota);              // 결과 호스트 컴퓨터에 저장하기

    public:
        MiniFE();
        ~MiniFE();
};