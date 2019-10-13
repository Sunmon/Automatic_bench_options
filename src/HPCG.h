//hpcg
#pragma once
#include "Bench.h"

class HPCG: public Bench
{
    private: 
        void init(std::string _json = "null") override;
        void runBenchTool(int cpu, int period, int quota) override;

    public:
        HPCG();
        ~HPCG();
};