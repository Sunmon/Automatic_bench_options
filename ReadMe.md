# Automatic Bench Options

도커 벤치마크 자동화 툴

100ms단위로 100 ~ 1000ms period, cpu= 0 ~ 3까지 실행한 결과를 `${abo}/out/[bench]`에 저장합니다.






## How to Use

`../bin/abo`를 실행하세요.

```
$./abo [벤치마크 이름]
```
벤치마크 실행 결과는 $abo/out에 벤치마크별 폴더 아래에 저장

**벤치마크별 실행방법 : **

- ./abo hpl            		 //hpl실행
- ./abo httpd-server    //httpd를 실행할 수 있게 도커 데몬모드로 운영. 
- ./abo httpd-client     //jmeter실행. httpd-server와 연결 (서버가 열려있어야 함)
- ./abo minife              //minife
- ./abo nginx-client        //nginx



\* 만약 도커 실행할때 백그라운드에서도 돌아가도록 환경설정 옵션 바꿔놨으면 *httpd-server*는 따로 실행할 필요 없음!

웹서버는 1.httpd-server 실행 (서버컴퓨터에서)) 2. 클라이언트(nginx-client , httpd-client)실행 (jmeter실행할 컴퓨터에서)


## Install

따로 설치할 필요없음. `/bin`에 있는 *abo*를 실행하면 되는데

혹시 안 될 경우 `/src`에서 빌드해서 쓰세요



빌드 방법 (g++ 기준) :

```
$ g++ abo.cpp Bench.cpp [기타 벤치마크 전부.cpp] json.cpp
```

예시:
```
$ g++ abo.cpp Bench.cpp HPL.cpp Httpd-Client.cpp Httpd-Server.cpp json.cpp
```



팁: 만약 g++안쓰고 vs쓰면 알아서 링크해주기때문에 그냥 abo.cpp만 빌드해도 됨






## Configure

각종 설정은 `${abo}/env/config.json`에서 수정가능

프로그램별 필요한 파일 위치나 설정값같은거 저장함

나중에 원인찾을때 실험값 바꾸기 쉬우라고 만들었음



파일 경로나 이름같은거 바꾸고싶으면 `config.json`만 건드리면 됩니다. (소스 건드리거나 재빌드, 컴파일할필요 ㄴㄴ)

예) jmeter 실험 도메인을 건국대로 바꾸고 싶다? `config.json`의 *"server.IP"="konkuk.ac.kr"*로 수정






## Directory

- `archive` : 결과값 저장해둔 폴더
- `bin` : 바이너리 폴더. 여기에 컴파일한거 집어넣음
- `env` : 벤치마크 실행하는 데에 각종 필요한 환경설정파일 저장
  - `config.json`: 환경설정 및 파일들 경로 설정
- `out` : 벤치마크 돌린 결과 저장소
- `src`: 소스파일
  - *abo* : main()이 있는 본체
  - *Bench* : 벤치마크 프로그램 클래스
    - HPL : HPL
    - Httpd-Server : 도커 백그라운드에서 돌림
    - Httpd-Client : Jmeter 실행 & server 도커 컨테이너 업데이트
  - BenchFactory : 팩토리패턴
  - jsoncpp : json 파싱 위한 클래스
- trash : 쓰레기통



.vscode는 vscode 설정파일이니 알아서 쓰세요





## Structure

### abo.cpp

메인 클래스.

bench()만 실행하면 된다.



### Bench.h

벤치마크 툴 기초가 되는 부모클래스.

public의 *benchmark()*가 벤치마크 실행 메소드

private는 컨테이너 생성/ 업데이트 / 중지라서 딱히 건드릴 필요 없음

protected는 자식 클래스 (각종 벤치툴)마다 조금씩 다를수있는 메소드들



새 클래스를 추가하면 Bench.h를 상속받게하고, 필요에 따라 아래 메소드만 새로 작성하면 된다.

- saveRslt()
- cpEnvToContainer()
- runBenchTool()
- init() 



다만 그냥 백그라운드에서 도커 실행하기만 하는 경우는 Httpd-server 참고.

아니면 직접 돌리던가..





## Addition

벤치마크를 추가할 때 수정해야 하는 곳:

1. 새 벤치마크 클래스
2. config.json
3. BenchFactory.h
4. g++ 빌드 옵션





### 새 벤치마크 클래스

```cpp
//new benchmark class 예제

/** newBench.h **/
#pragma once 
#include "Bench.h"
class NewBench : public Bench
{
    private: 
        void saveRslt(int cpu, int period, int quota);
        void cpEnvToContainer() override;
        void runBenchTool(int cpu, int period, int quota) override;
		void init();
		int temp_var, own_var;
		
    public:
        NewBench();
        ~NewBench();
};


/** newBench.cpp **/

NewBench()::NewBench() : Bench("img", "name"){...}

void NewBench()::runBenchTool(int cpu, int period, int quota){
    string socket_bench = DOCKER + "exec " + ["socket"]["benchtool"].asString();
    command(socket_bench);
}
...
```





### config.json

#### 설정 추가

config.json에 해당 벤치마크 관련 설정 추가

```json
{
    ...
    "newBench" : 
    {
        "환경설정파일" : "어쩌구",
        "컨테이너내아웃풋저장위치": "저쩌구",
        "유저수" : 16,
        "ip주소" : "어절쩌구"
    }
}
```





#### 설정 불러오기

클래스 내에서 config 사용 방법: *Bench::config*를 이용

```cpp
std::string temp1 = config["newBench"]["환경설정파일"].asString();	//어쩌구
int temp2 = config["newBench"]["유저수"].asInt();	//16
```

더 많은 사용법은 jsoncpp을 구글링





### BenchFactory.h

selectBench()에 abo argv로 받을 값 넣으세요

```cpp
Bench* selectBench(std::string program)
{
    ...
    if(program == "newb")       return new newBench;
}
```





### g++ 빌드 옵션

g++ 할때 새 클래스도 링크해서 돌리세요
