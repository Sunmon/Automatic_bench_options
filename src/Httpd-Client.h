#pragma once
#include "Bench.h"

class Httpd_Client : public Bench
{

    public:

    Httpd_Client();
    virtual ~Httpd_Client();

    void runBenchTool(int cpu, int period, int quota) override;
    void init() override;

    std::string servAddr; 


};