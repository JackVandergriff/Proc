cd `git rev-parse --git-dir`/..
ROOT=`pwd`
BIN=$ROOT/bin
SRC=$ROOT/src
ETC=$ROOT/etc

cd $SRC
g++ -g main.cpp game.cpp sprite_loader.cpp atlas.cpp tilemap.cpp -o $BIN/proc -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio