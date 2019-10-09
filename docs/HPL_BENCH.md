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
>> /AddedFiles/hpl-2.3/bin/x86_64/HPL.out
>> mpirun --allow-run-as-root -np 4 xhpl
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







# HPL 성능 측정



## Docker Set

도커 컨테이너 자체에 있는 옵션을 이용하여 측정.

hyperthread = off

코어 개수는 1개부터 4개까지 각각 측정.

각 cpu코어 개수별로 bandwidth는 0.5로 고정하고, 주기와 허용량을 변화해가며 측정

```dockerfile
--cpuset-cpus = 0, 0-1, 0-2, 0-3
--cpu-period = 100000(100ms) -> 1000000(1000ms), 100ms단위로 증가
--cpu-quota = period /2
```





## HPL.dat

HPL.dat의 Qs수를 두 가지로 나눠서 측정.

1. Qs = cpu core수
2. Qs = 4로 고정

두 경우 다 Ps는 1로 고정.



ㄴㄴ 그냥 Qs=4로 고정해서 측정함.





## RUN

프로세서 수를 4개로 고정하여 측정

```bash
$ mpirun --allow-run-as-root -np 4 xhpl
```

