//HPL benchmark
#pragma once 
#include "Bench.h"
#include <cstring>

class HPL : public Bench
{

    private: 
        // void exec();
        // void cpEnv();
        void saveRslt(int cpu, int period, int quota);


        // void init() override;
        void cpEnvToContainer() override;
    public:
        // void benchmark() override;    //이 함수 실행하면 된다
        HPL();
        ~HPL();

    protected:
    //     void createContainer() override; 
    //     void runContainer() override;
    //     void updateContainer() override;
        void runBenchTool(int cpu, int period, int quota) override;
};