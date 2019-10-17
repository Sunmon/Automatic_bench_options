# 1. install ubuntu & basic tools
FROM ubuntu:18.04
LABEL maintainer="blackmilk274@gmail.com"
RUN apt-get -y update
RUN apt install -y build-essential 
RUN apt-get install -y gcc make 
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


# 4. Install HPCG
ADD http://www.hpcg-benchmark.org/downloads/hpcg-3.1.tar.gz /AddedFiles/
RUN tar -xf /AddedFiles/hpcg-3.1.tar.gz -C /AddedFiles/
WORKDIR /AddedFiles/hpcg-3.1
COPY ./Make.x86_64 /AddedFiles/hpcg-3.1/setup
RUN make arch=x86_64
WORKDIR /AddedFiles/hpcg-3.1/bin




# # 4. Install HPL (http://www.netlib.org/benchmark/hpl/)
# # http://www.netlib.org/benchmark/hpl/software.html 
# ADD http://www.netlib.org/benchmark/hpl/hpl-2.3.tar.gz /AddedFiles/
# RUN tar -xf /AddedFiles/hpl-2.3.tar.gz -C /AddedFiles/
# WORKDIR /AddedFiles/hpl-2.3
# COPY ./Make.x86_64 /AddedFiles/hpl-2.3/Make.x86_64
# RUN make arch=x86_64
# WORKDIR /AddedFiles/hpl-2.3/bin/x86_64
# RUN apt-get install -y vim

# # fix errno=1
# ENV OMPI_MCA_btl_vader_single_copy_mechanism none