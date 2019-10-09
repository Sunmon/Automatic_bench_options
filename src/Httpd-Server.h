#pragma once
#include "Bench.h"
#include <cstring>

class Httpd_Server : public Bench
{
    private:
        void benchmark() override;
        void runBenchTool(int cpu, int period, int quota) override;

    public:
        Httpd_Server();
        virtual ~Httpd_Server();
};