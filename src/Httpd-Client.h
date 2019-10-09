#pragma once
#include "Bench.h"

class Httpd_Client : public Bench
{

    private:
        void runBenchTool(int cpu, int period, int quota) override;
        void init() override;
        std::string servAddr; 

    public:
        Httpd_Client();
        virtual ~Httpd_Client();
};