#pragma once
#include "Bench.h"
#include <cstring>

class Nginx_Client : public Bench
{

    private:
        void init(std::string _json = "null") override;
        void initContainer() override;
        void runBenchTool(int cpu, int period, int quota) override;
        void saveRslt(int cpu, int period, int quota) override;              // 결과 호스트 컴퓨터에 저장하기

        // void init() override;
        // std::string servAddr;

    public:
        Nginx_Client();
        virtual ~Nginx_Client();
};