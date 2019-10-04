# HPL Bench 돌리는 방법



## 설치

#### 이미지 다운받기

```
$ docker pull blackmilk274/hpl
```





## hplBench 실행

실행방법: 

1. $ cd <hplBench 있는 폴더>
2. ./ hplBench <hpl 이미지이름>
3. <컨테이너 내에서 HPL.out이 저장되는 위치 입력>
4. <mpirun 명령어 입력>

3번과 4번은 안 바뀜. 1,2번은 자신의 컴퓨터 디렉토리에 맞게 입력할것

예: 

```
$ cd ~/Desktop/Automatic_bench_options/bin/
$ ./ hplBench blackmilk274/hpl
>> /AddedFiles/hpl-2.3/bin/x86_64/HPL.out	#고정
>> mpirun --allow-run-as-root -np 4 xhpl	#고정
```



## 옵션 바꾸기

../src/hplBench.cpp을 수정하면 된다.

- 바꿔야 할 옵션 :

#define CORE 4  //듀얼코어면 2로 바꾸기

NUM_CPU[4] = {"0", "0-1", "0-2", "0-3"}; //cpu 번호 설정 필요. "0", "0,2", "0,2,4", "0,2,4,6"일수도 있음



## 디렉토리 설명

- `bin` : 실행 파일이 저장되는 위치
- `data`: 벤치마크를 위한 준비물이 저장되는 위치
- `out`: 벤치마크 결과가 저장되는 위치
- `src`: 소스파일









---

# Automatic_bench_options

benchmark에 쓸 옵션들을 자동으로 설정해주는 프로그램.

주기 알아서 세팅 알아서....


# How to use

어쩌구 저쩌구

# Credit

Sunmon





---