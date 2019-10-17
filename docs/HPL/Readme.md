# HPL

HPL Benchmark
Based on OpenMPI and BLAS 
  
  
## HOW TO USE

  
### INSTALL
```
$ docker pull blackmilk274/hpl 
```
  
    
### DOCKER RUN
```
$docker run -it blackmilk274/hpl
```
  
  
### Modify `HPL.dat`

modify in the container: 
```
$ docker vi HPL.dat
```

or copy your `HPL.dat`:

```
$ docker copy [your HPL.dat] [container:/AddedFiles/hpl-2.3/bin/x86_64/HPL.dat]
```


### RUN benchmark
```
$ mpirun --run-as-root -np [num] ./xhpl
```
  
  
### DIRECTORY

HPL Directory : [docker container]/AddedFiles/hpl-2.3
OpenMPI Directory : [docker container]/usr/local/openmpi