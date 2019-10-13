//HPL benchmark
#pragma once 
#include "Bench.h"

class HPL : public Bench
{

    private: 
        void saveRslt(int cpu, int period, int quota);
        void initContainer() override;
        void runBenchTool(int cpu, int period, int quota) override;

    public:
        HPL();
        ~HPL();
    
};