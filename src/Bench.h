//벤치마크 인터페이스
//필요한 메소드, 변수들 정의
#include <cstring>
#include <iostream>
// using namespace std;

class Bench
{
    protected:
        void createContainer(); 
        void runContainer();
        void updateContainer();
        void runProgram();


     public: 
        void runBenchmark();    //이 함수 실행하면 된다
        void makeDir(const std::string& dir);
        void command(const std::string& cmd);
        const std::string IMG;
        const std::string NAME; 
        const std::string NUM_CPU[4] = {"0", "0-1", "0-2", "0-3"}; //cpu 번호 설정 필요. "0", "0,2", "0,2,4", "0,2,4,6"일수도 있음

        //NOTE: virtual로 바꿔야하나?
        Bench();   
        ~Bench();
        // string OUTPUT[2]; 


};