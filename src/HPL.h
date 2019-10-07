//HPL benchmark
#pragma once 
#include "Bench.h"


class HPL : public Bench
{
    public:
        void runBenchmark() override;    //이 함수 실행하면 된다
        HPL(){};
        ~HPL(){};

    protected:
        void createContainer() override; 
        void runContainer() override;
        void updateContainer() override;
        void runProgram() override;
};