minife 실행옵션

####  minife 위치

docker run --name mini -it --entrypoint=/bin/bash ivotron/minife

:/minife/ref/src/

mpirun --allow-run-as-root -np 4 ./miniFE.x -nx 100 -ny 100 -nz 100 > output.txt



걍이렇게하자
docker run --name mini -it -w /minife/ref/src --entrypoint=/bin/bash ivotron/minife


docker exec minife bash -c "rm *.yaml"


docker cp에 * (wildcard)가 안먹히기 때문에 세 단계로 나눠서 해야함

1. exec으로 .yaml 파일 이름 바꾸기 (output.yaml)
2. docker cp 
3. exec으로 output.yaml 지우기(왜? 계속 쌓이니까.)

docker exec minife bash -c "mv *.yaml output.yaml"
docker exec minife bash -c "rm output.yaml"


만약 그 output도 받고싶다면 
        "mpirun" : "mpirun --allow-run-as-root -np 4 ./miniFE.x -nx 100 -ny 100 -nz 100" > output.txt
설정을 이렇게 바꿀것
