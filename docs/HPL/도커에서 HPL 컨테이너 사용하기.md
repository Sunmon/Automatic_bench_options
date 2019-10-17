# 도커에서 HPL 컨테이너 사용하기

도커에서 HPL (High-Performance Linpack) 컨테이너를 사용하는 방법을 알아보자.

아직 도커에 HPL이나 linpack의 공식 이미지가 없다. (2019.09.24. 기준)

그래서 그냥 내가 만들어 쓰기로 했다.



> 목차:  
> 0. HPL과 준비물
> 1. 컨테이너에서 직접 실행시켜보기
> 2. Dockerfile 작성하기
> 3. 컨테이너 실행 확인하기



## HPL이 뭔가?

우선 HPL이 무엇인지 감부터 잡아보자.

HPL은  "High-Performance Linpack"의 약자인데, 여기서 Linpack은 벤치마크 프로그램 이름이다.

즉, HPL은 "High-Performace Computer의 Benchmark Tool"이다. HPL벤치마크는 MPI를 사용하여 LINPACK 프로그램을  병렬화한것으로, 프로세서-메모리가 물리적으로 떨어진 클러스터 시스템에서도 LINPACK을 수행할 수 있게 해준다.  

HPL을 실행하려면 MPI와 BLAS 혹은 VSPL이 필요하다.



### MPI

MPI : "Message Passing Interface."

MPI는 규격(인터페이스), OpenMPI나 MPICH는 MPI를 구현한 프로그램.

이 포스팅에서는 **OpenMP**를 이용한다.

참고로 OpenMP와 OpenMPI는 다르다. 괜히 헷갈려서 고생하지 말자.



### BLAS

BLAS:  "Basic Linear Algebra Subprograms." 

BLAS는 LINPACK 벤치마크에 필요한 라이브러리다. 기본적인 연산들을 구현해놨다.



#### VSIPL

VSIPL: "Vector Signal Image Processing Library." 이미지 프로세싱 API. 

VSIPL대신에 BLAS를 사용하면 되므로 다루지 않는다.


MPI, BLAS, VSIPL에 대해 더 자세히 알아보고 싶다면 [이 링크](http://www.netlib.org/benchmark/hpl/links.html#mpi_libs) 참고. 



```docker
$ docker build -t [이미지이름]] [Dockfile위치]
```


## 도커 컨테이너에 실행시키기

### 1. 빌드에 필요한 준비물 다운받기

```
$ apt-get -y update
$ apt install -y build-essential 
$ apt-get install -y gcc make 
$ apt-get install -y gfortran 
```

### 2. OpenMPI다운받기

- [openmpi](https://download.open-mpi.org/release/open-mpi/v4.0/openmpi-4.0.1.tar.gz)여기서 파일을 다운로드 받아 도커 컨테이너 안으로 넣어준다. 압축해제도 해준다.

```
$ docker cp [다운받은 파일]] [컨테이너에 옮길 위치]
```

- 컨테이너의 `openmpi-4.0.1`폴더로 이동해서 환경설정을 수정한다.

```
$ cd [복사한 openmpi-4.0.1폴더]
$ mkdir "openmpi설치할 폴더" 
$ ./configure --prefix="openmpi설치할 폴더"
```

- 설치한다.
```
$ make install
```

- PATH 설정
```
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/openmpi/lib
$ export PATH=$PATH:/usr/local/openmpi/bin
```

만약 mpirun을 실행할 때 `plm_rsh_agent`에러가 뜨면 openssh를 설치해주자. segment fault (11) 에러인가 그렇다.
```
$ apt-get install -y openssh-client
```


### 3. LAPACK 다운받기

BLAS가 LAPACK패키지 안에 있다. 다운받자.

```
$ apt install -y liblapack3
$ apt install -y libopenblas-base
$ apt install -y libopenblas-dev
$ apt install -y liblapacke-dev
$ apt install -y liblapack-dev
```
그리고 사용할 땐 컴파일러 링크 옵션에 `-lm -lblas -llapack -llapacke`를 주면 된다.


### 4. HPL 다운받기

[HPL 홈페이지](https://www.netlib.org/benchmark/hpl/software.html) 여기서 파일을 다운받자. OpenMPI처럼 컨테이너 안에 압축을 풀어 넣어준다.

```
$ docker cp [다운받은 파일 위치] [컨테이너에 붙여넣을 위치]
```

이 컨테어네에 붙여넣은 위치를 `top folder`라고 부르겠다.
`top folder`로 이동해서 Make.<arch>파일을 수정한다. `$[top folder]/setup/`에 아키텍쳐별 기본 make파일이 있다. 없으면 하나를 골라서 내부를 수정하자. 내 아키텍쳐는 `arch`명령어로 확인할 수 있다.

**직접 Make.<arch>를 수정하기**

잘 읽어보고 디렉토리와 링크해주는 옵션만 수정해주면 되는데

일일히 설명하기 힘들어서 그냥 내 파일을 올린다.

나는 x86_64다.

```Make.x86_64
#  
#  -- High Performance Computing Linpack Benchmark (HPL)                
#     HPL - 2.3 - December 2, 2018                          
#     Antoine P. Petitet                                                
#     University of Tennessee, Knoxville                                
#     Innovative Computing Laboratory                                 
#     (C) Copyright 2000-2008 All Rights Reserved                       
#                                                                       
#  -- Copyright notice and Licensing terms:                             
#                                                                       
#  Redistribution  and  use in  source and binary forms, with or without
#  modification, are  permitted provided  that the following  conditions
#  are met:                                                             
#                                                                       
#  1. Redistributions  of  source  code  must retain the above copyright
#  notice, this list of conditions and the following disclaimer.        
#                                                                       
#  2. Redistributions in binary form must reproduce  the above copyright
#  notice, this list of conditions,  and the following disclaimer in the
#  documentation and/or other materials provided with the distribution. 
#                                                                       
#  3. All  advertising  materials  mentioning  features  or  use of this
#  software must display the following acknowledgement:                 
#  This  product  includes  software  developed  at  the  University  of
#  Tennessee, Knoxville, Innovative Computing Laboratory.             
#                                                                       
#  4. The name of the  University,  the name of the  Laboratory,  or the
#  names  of  its  contributors  may  not  be used to endorse or promote
#  products  derived   from   this  software  without  specific  written
#  permission.                                                          
#                                                                       
#  -- Disclaimer:                                                       
#                                                                       
#  THIS  SOFTWARE  IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE UNIVERSITY
#  OR  CONTRIBUTORS  BE  LIABLE FOR ANY  DIRECT,  INDIRECT,  INCIDENTAL,
#  SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES  (INCLUDING,  BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA OR PROFITS; OR BUSINESS INTERRUPTION)  HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT,  STRICT LIABILITY,  OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
# ######################################################################
#  
# ----------------------------------------------------------------------
# - shell --------------------------------------------------------------
# ----------------------------------------------------------------------
#
SHELL        = /bin/sh
#
CD           = cd
CP           = cp
LN_S         = ln -s
MKDIR        = mkdir
RM           = /bin/rm -f
TOUCH        = touch
#
# ----------------------------------------------------------------------
# - Platform identifier ------------------------------------------------
# ----------------------------------------------------------------------
#
#ARCH         = Linux_PII_CBLAS
ARCH		= x86_64
#
# ----------------------------------------------------------------------
# - HPL Directory Structure / HPL library ------------------------------
# ----------------------------------------------------------------------
#
#TOPdir       = $(HOME)/hpl
TOPdir	= /AddedFiles/hpl-2.3
INCdir       = $(TOPdir)/include
BINdir       = $(TOPdir)/bin/$(ARCH)
LIBdir       = $(TOPdir)/lib/$(ARCH)
#
HPLlib       = $(LIBdir)/libhpl.a 
#
# ----------------------------------------------------------------------
# - Message Passing library (MPI) --------------------------------------
# ----------------------------------------------------------------------
# MPinc tells the  C  compiler where to find the Message Passing library
# header files,  MPlib  is defined  to be the name of  the library to be
# used. The variable MPdir is only used for defining MPinc and MPlib.
#
#
#MPdir        = /usr/local/mpi
#MPinc        = -I$(MPdir)/include
#MPlib        = $(MPdir)/lib/libmpich.a
MPdir	= /usr/local/openmpi
MPinc = -I$(MPdir)/include
MPlib      = $(MPdir)/lib/libmpi.so
#
# ----------------------------------------------------------------------
# - Linear Algebra library (BLAS or VSIPL) -----------------------------
# ----------------------------------------------------------------------
# LAinc tells the  C  compiler where to find the Linear Algebra  library
# header files,  LAlib  is defined  to be the name of  the library to be
# used. The variable LAdir is only used for defining LAinc and LAlib.
#
#LAdir        = $(HOME)/netlib/ARCHIVES/Linux_PII
#LAinc        =
#LAlib        = $(LAdir)/libcblas.a $(LAdir)/libatlas.a
LAdir	= /usr/lib/x86_64-linux-gnu/openblas
LAinc = 
LAlib = $(LAdir)/libblas.a $(LAdir)/liblapack.a 

#
# ----------------------------------------------------------------------
# - F77 / C interface --------------------------------------------------
# ----------------------------------------------------------------------
# You can skip this section  if and only if  you are not planning to use
# a  BLAS  library featuring a Fortran 77 interface.  Otherwise,  it  is
# necessary  to  fill out the  F2CDEFS  variable  with  the  appropriate
# options.  **One and only one**  option should be chosen in **each** of
# the 3 following categories:
#
# 1) name space (How C calls a Fortran 77 routine)
#
# -DAdd_              : all lower case and a suffixed underscore  (Suns,
#                       Intel, ...),                           [default]
# -DNoChange          : all lower case (IBM RS6000),
# -DUpCase            : all upper case (Cray),
# -DAdd__             : the FORTRAN compiler in use is f2c.
#
# 2) C and Fortran 77 integer mapping
#
# -DF77_INTEGER=int   : Fortran 77 INTEGER is a C int,         [default]
# -DF77_INTEGER=long  : Fortran 77 INTEGER is a C long,
# -DF77_INTEGER=short : Fortran 77 INTEGER is a C short.
#
# 3) Fortran 77 string handling
#
# -DStringSunStyle    : The string address is passed at the string loca-
#                       tion on the stack, and the string length is then
#                       passed as  an  F77_INTEGER  after  all  explicit
#                       stack arguments,                       [default]
# -DStringStructPtr   : The address  of  a  structure  is  passed  by  a
#                       Fortran 77  string,  and the structure is of the
#                       form: struct {char *cp; F77_INTEGER len;},
# -DStringStructVal   : A structure is passed by value for each  Fortran
#                       77 string,  and  the  structure is  of the form:
#                       struct {char *cp; F77_INTEGER len;},
# -DStringCrayStyle   : Special option for  Cray  machines,  which  uses
#                       Cray  fcd  (fortran  character  descriptor)  for
#                       interoperation.
#
F2CDEFS      =
#
# ----------------------------------------------------------------------
# - HPL includes / libraries / specifics -------------------------------
# ----------------------------------------------------------------------
#
HPL_INCLUDES = -I$(INCdir) -I$(INCdir)/$(ARCH) $(LAinc) $(MPinc)
HPL_LIBS     = $(HPLlib) $(LAlib) $(MPlib)
#
# - Compile time options -----------------------------------------------
#
# -DHPL_COPY_L           force the copy of the panel L before bcast;
# -DHPL_CALL_CBLAS       call the cblas interface;
# -DHPL_CALL_VSIPL       call the vsip  library;
# -DHPL_DETAILED_TIMING  enable detailed timers;
#
# By default HPL will:
#    *) not copy L before broadcast,
#    *) call the BLAS Fortran 77 interface,
#    *) not display detailed timing information.
#
HPL_OPTS     = -DHPL_CALL_CBLAS
#
# ----------------------------------------------------------------------
#
HPL_DEFS     = $(F2CDEFS) $(HPL_OPTS) $(HPL_INCLUDES)
#
# ----------------------------------------------------------------------
# - Compilers / linkers - Optimization flags ---------------------------
# ----------------------------------------------------------------------
#
CC           = /usr/bin/gcc
CCNOOPT      = $(HPL_DEFS)
#CCFLAGS      = $(HPL_DEFS) -fomit-frame-pointer -O3 -funroll-loops
CCFLAGS      = $(HPL_DEFS) -fomit-frame-pointer -O3 -funroll-loops -lm -lblas -llapack -llapacke -pthread
#
# On some platforms,  it is necessary  to use the Fortran linker to find
# the Fortran internals used in the BLAS library.
#
#LINKER       = /usr/bin/g77
LINKER		= /usr/bin/gfortran
LINKFLAGS    = $(CCFLAGS)
#
ARCHIVER     = ar
ARFLAGS      = r
RANLIB       = echo
#
# ----------------------------------------------------------------------
```

Make.<arch>파일을 make한다. 
make arch=<arch>
그러면 top folder/bin/<arch>안에 `xhpl`과  `hpl.dat`이 생겼을것이다.


## Dockerfile 작성하기

이미지를 만드는 방법은 2가지가 있다: 


1. 우분투 컨테이너에 어플리케이션을 돌린 그 상태를 이미지로 만든다. (commit)
2. Dockerfile을 이용해서 이미지를 만든다.

지금은 2번 방법을 이용해서 만들어보자. 나중에 옵션을 변경하기 쉽도록.

[도커 컨테이너에 실행시키기](#도커 컨테이너에 실행시키기)에서 한 방법대로 Dockerfile을 만들어보자.


```dockerfile
# 1. install ubuntu & basic tools
FROM ubuntu:18.04
LABEL maintainer="blackmilk274@gmail.com"
RUN apt-get -y update
# RUN apt-get install -y apt-utils
RUN apt install -y build-essential 
RUN apt-get install -y gcc make 
# RUN DEBIAN_FRONTEND=noninteractive apt-get install -y gfortran
RUN apt-get install -y gfortran 
RUN apt-get update

# 2. Install MPI(OpenMPI)
ADD https://download.open-mpi.org/release/open-mpi/v4.0/openmpi-4.0.1.tar.gz /AddedFiles/
RUN tar -xf /AddedFiles/openmpi-4.0.1.tar.gz -C /AddedFiles/
WORKDIR /AddedFiles/openmpi-4.0.1
RUN mkdir /usr/local/openmpi
RUN ./configure --prefix="/usr/local/openmpi"
RUN make install

# fortran compiler가 알수 있도록 mpi 라이브러리 위치 설정
ENV LD_LIBRARY_PATH $LD_LIBRARY_PATH:/usr/local/openmpi/lib
ENV PATH $PATH:/usr/local/openmpi/bin
# plm_rsh_agent error 고치려고 openssh 설치
RUN apt-get install -y openssh-client
# RUN export MY_MPIRUN_CLI_ARGS="--allow-run-as-root"
# RUN source ~/.bashrc

# 3. Install BLAS (in the LAPACK.. https://www.assistedcoding.eu/2017/11/04/how-to-install-lapacke-ubuntu/)
RUN apt install -y liblapack3
RUN apt install -y libopenblas-base
RUN apt install -y libopenblas-dev
RUN apt install -y liblapacke-dev
RUN apt install -y liblapack-dev

# 4. Install HPL (http://www.netlib.org/benchmark/hpl/)
# http://www.netlib.org/benchmark/hpl/software.html 
ADD http://www.netlib.org/benchmark/hpl/hpl-2.3.tar.gz /AddedFiles/
RUN tar -xf /AddedFiles/hpl-2.3.tar.gz -C /AddedFiles/
WORKDIR /AddedFiles/hpl-2.3
COPY ./Make.x86_64_3 /AddedFiles/hpl-2.3/Make.x86_64
RUN make arch=x86_64

```

## 실행방법

도커내부에서는 루트로 실행한다. 루트권한으로 mpirun을 실행하려면 옵션이 더 붙는다.  `--allow-run-as-root`

`xhpl`이 있는 폴더로 이동해서 기본적인 벤치마킹을 해보자.

```
$ mpirun --allow-run-as-root -np 4 xhpl
```



## 참고

클러스터 시스템 성능 측정: https://cs.kaist.ac.kr/upload_files/report/1227159241.pdf

MPI가 뭔가: http://byh819.blogspot.com/2015/03/mpimessage-passing-interface-mpi-o.html

High-Performace Computing 문서: https://ulhpc-tutorials.readthedocs.io/en/latest/

Luxembourg university에서 만든 HPL 입문서: https://ulhpc-tutorials.readthedocs.io/en/latest/parallel/mpi/HPL/

HPL 문서: http://www.netlib.org/benchmark/hpl/

도커 이미지 만들기: https://subicura.com/2017/02/10/docker-guide-for-beginners-create-image-and-deploy.html

도커 이미지 만들기: http://blog.naver.com/PostView.nhn?blogId=complusblog&logNo=220974346757

openmpi 설치: https://github.com/firemodels/fds/wiki/Installing-Open-MPI-on-a-Linux-Cluster

openmpi 설치 pdf: http://lsi.ugr.es/jmantas/pdp/ayuda/datos/instalaciones/Install_OpenMPI_en.pdf

도커 이미지 ADD: http://pyrasis.com/book/DockerForTheReallyImpatient/Chapter07/09


도커에서 mpirun : https://github.com/open-mpi/ompi/issues/4451


