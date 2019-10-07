#pragma once
#include "Bench.h"

class Httpd_Server : public Bench
{
    public:
        Httpd_Server();
        virtual ~Httpd_Server();
        void benchmark() override;
        void runBenchTool(int cpu, int period, int quota) override;
};