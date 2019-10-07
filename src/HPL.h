//HPL benchmark
#pragma once 
#include "Bench.h"
#include <cstring>

class HPL : public Bench
{
    public:
        // void benchmark() override;    //이 함수 실행하면 된다
        HPL();
        ~HPL();

    protected:
    //     void createContainer() override; 
    //     void runContainer() override;
    //     void updateContainer() override;
        void runProgram() override;
};