//벤치마크 인터페이스
/**
 * @Class    Bench
 * @Description 벤치마크 프로그램들의 부모 클래스 (뼈대 클래스)
 * @Var     
 *  config      : ../env/config.json에 접근하기 위해 사용하는 변수
 *  IMG         : 이미지 이름
 *  NAME        : 컨테이너 이름
 *  DOCKER      : "docker" 명령어. 자신 호스트에 보낼것인가 / 원격으로 도커 명령을 보낼것인가 결정
 *  runOption   : 컨테이너 run 할때 붙을 옵션. -dit --rm --name 이런거
 *  manVar[3]   : cpuset, period, quota 현재 값 저장
 *  outDir      : 벤치마크 결과값을 저장할 호스트 디렉토리 위치
 * @Method 
 *  init()  : runOption, DOCKER, outDir, json 초기화
 *  initContainer()  : 컨테이너 내 데이터 초기화
 *  runBenchTool()      : 벤치마크 프로그램 실행
 *  saveRslt()          : 벤치마크 결과 저장
 * @Author      Sun-Jung Kim
 * 
**/
#pragma once
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "json/json.h"

#define CPUS 0
#define PER 1
#define QUO 2

class Bench
{
private:
    int CORE = 4; //쿼드코어

    virtual void runContainer();                                  // 컨테이너 실행
    virtual void updateContainer(int cpu, int period, int quota); // 컨테이너 cpu 옵션 변경
    virtual void stopContainer();                                 // 컨테이너 stop
    void initJson();

protected:
    std::string IMG;                                          // 이미지 이름
    std::string NAME;                                         // 컨테이너 이름
    std::string DOCKER;                                       // 도커 실행 옵션. "docker -H PORT" or "docker"
    std::string runOption;                                    // 도커 실행 옵션. " -dit --rm --name " + NAME + " " + IMG;
    std::string manVar[3];                                    // cpu옵션. manVar[0] = cpuset, manVar[1] = period, manVar[2] = bandwidth.
    std::string outDir;                                       // 호스트에 output이 저장되는 dir
    const std::string CPUSET[4] = {"0", "0-1", "0-2", "0-3"}; //cpu 번호. "0", "0,2", "0,2,4", "0,2,4,6"일수도 있음

    virtual void init();                                           // runOption, DOCKER, outDir 초기화
    virtual void runBenchTool(int cpu, int period, int quota) = 0; // 벤치마크 툴 돌리기. jemter, hpl 이런거
    virtual void initContainer();                               // 컨테이너 운영에 필요한 환경설정 파일 복사해오기
    virtual void initContainer(std::string data, std::string dest_dir);
    virtual void saveRslt(int cpu, int period, int quota); // 결과 호스트 컴퓨터에 저장하기

public:
    virtual void benchmark(); //벤치마크 실행 함수

    void setCore(int num);                //쿼드코어가 아닐때 사용
    void command(const std::string &cmd); //터미널에 명령 전달
    void makeDir(const std::string &dir); //디렉토리 생성

    Json::Value config; //json에서 읽어온 환경설정을 저장하는 변수
    Bench();
    Bench(const std::string &img, const std::string &name); //img, name 초기화하는 생성자
    virtual ~Bench();
};