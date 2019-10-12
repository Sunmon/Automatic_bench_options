//hpcg
#pragma once
#include "Bench.h"

class HPCG: public Bench
{
    private: 
        void saveRslt(int cpu, int period, int quota);
        void cpEnvToContainer() override;
        void runBenchTool(int cpu, int period, int quota) override;

    public:
        HPCG();
        ~HPCG();
    


};