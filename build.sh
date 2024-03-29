#!/bin/sh

# This should be a Makefile

FOLDERS="src \
         src/csv \
         src/entry \
         src/inserter \
         src/trie \
         src/console \
         src/sort"

PROJECT_DIR=$(pwd)
BIN_DIR="$PROJECT_DIR/build"
CC=g++
CFLAGS="-std=c++17 -Wall -Wextra -Werror -Wpedantic -Ofast"
INCLUDES="$PROJECT_DIR/src"

mkdir -p $BIN_DIR
cd $PROJECT_DIR

for folder in $FOLDERS
do
    cd $folder
    for file in *.cpp
    do
        echo "Building $folder/$file"
        g++ -g -c $file $CFLAGS -o $BIN_DIR/$file.o -I $INCLUDES
    done
    cd $PROJECT_DIR
done

OBJECTS="$(ls $BIN_DIR/*.o)"
g++ $OBJECTS -o $PROJECT_DIR/movielens
echo "Done."          
