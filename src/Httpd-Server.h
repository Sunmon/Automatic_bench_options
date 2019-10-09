#pragma once
#include "Bench.h"
#include <cstring>

class Httpd_Server : public Bench
{
    private:
        void benchmark() override;

    public:
        Httpd_Server();
        virtual ~Httpd_Server();
};