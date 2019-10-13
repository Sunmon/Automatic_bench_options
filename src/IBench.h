//Bench Class에서 쓸 인터페이스
//Bench Class의 benchmark안에 들어가는 메소드들의 인터페이스
//병렬프로그램 / 웹서버 프로그램에 쓰기 편하도록 인터페이스 만들음
//그 외에 프로그램이 추가되면 인터페이스 추가해서 쓸 것

#pragma once
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "json/json.h"

class IBench
{
    virtual void init(std::string _json = "null");                 // runOption, DOCKER, outDir 초기화
    virtual void runBenchTool(int cpu, int period, int quota) = 0; // 벤치마크 툴 돌리기. jemter, hpl 이런거
    virtual void initContainer();                               // 컨테이너 운영에 필요한 환경설정 파일 복사해오기
    virtual void saveRslt(int cpu, int period, int quota); // 결과 호스트 컴퓨터에 저장하기



};