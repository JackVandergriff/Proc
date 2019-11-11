cd `git rev-parse --git-dir`/..
ROOT=`pwd`
BIN=$ROOT/bin
SRC=$ROOT/src
ETC=$ROOT/etc

cd $SRC
g++ -g *.cpp -o $BIN/proc -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio