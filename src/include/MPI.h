//mpi를 사용하는 인터페이스
#pragma once
#include "Bench.h"
class MPI : public Bench
{
    protected:
    virtual void init() override;                 // runOption, DOCKER, outDir 초기화
    virtual void runBenchTool(int cpu, int period, int quota) override; // 벤치마크 툴 돌리기. jemter, hpl 이런거
    virtual void initContainer() override;                               // 컨테이너 운영에 필요한 환경설정 파일 복사해오기
    virtual void saveRslt(int cpu, int period, int quota) override; // 결과 호스트 컴퓨터에 저장하기

    public:
        MPI();
        MPI(const std::string &img, const std::string &name);
        virtual ~MPI();
};