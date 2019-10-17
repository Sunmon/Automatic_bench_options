hpcg problem size는 8의 배수여야 함. 100 (x) 104 (o)

docker exec hpcg mpirun --allow-run-as-root -np 4 ./xhpcg

docker exec hpcg ls -tr | tail -1 | xargs -I {} docker cp hpcg:/AddedFiles/hpcg-3.1/bin/{} ./test