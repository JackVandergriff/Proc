cd `git rev-parse --git-dir`/..
ROOT=`pwd`
BIN=$ROOT/bin
SRC=$ROOT/src
ETC=$ROOT/etc

cd $SRC
g++ process.cpp -c -o process_cpp.o
# g++ process.h -c -o process_c.o
gcc process.c -c -o process_c.o
nvcc process.cu -c -o process_cuda.o
g++ -o $BIN/process_test -L/opt/cuda/lib -lcuda -lcudart process_cpp.o process_cuda.o process_c.o
rm *.o
chmod +x $BIN/process_test

cd $ETC