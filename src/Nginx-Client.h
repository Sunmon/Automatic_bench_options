#pragma once
#include "Bench.h"
#include <cstring>

class Nginx_Client : public Bench
{

    private:
        void runBenchTool(int cpu, int period, int quota) override;
        void init() override;
        std::string servAddr;

    public:
        Nginx_Client();
        virtual ~Nginx_Client();
};