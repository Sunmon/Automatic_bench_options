//hpcg
#pragma once
#include "MPI.h"

class HPCG: virtual public MPI
{
    private: 
        // void init() override;
        void runBenchTool(int cpu, int period, int quota) override;

    public:
        HPCG();
        ~HPCG();
};