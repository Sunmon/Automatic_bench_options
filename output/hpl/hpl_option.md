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






## RUN

프로세서 수를 4개로 고정하여 측정
```bash
$ mpirun --allow-run-as-root -np 4 xhpl
```

