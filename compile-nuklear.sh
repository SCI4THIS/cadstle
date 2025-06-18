#!/bin/bash

BUILD_DIR=build-nuklear
SYS_INCLUDE=/home/A/emsdk/upstream/emscripten/cache/sysroot/include
WASM_LD=/home/A/emsdk/upstream/bin/wasm-ld.exe
WASM_2_WAT=/home/A/wabt/bin/wasm2wat.exe
WAT_2_WASM=/home/A/wabt/bin/wat2wasm.exe
NAME=nuklear

mkdir -p ${BUILD_DIR}
rm ${BUILD_DIR}/*

for FILE in Noise nuklear-tmp cadstle nuklear
do
  clang -o ${BUILD_DIR}/${FILE}.c.ll -I${SYS_INCLUDE} -Inuklear/ --target=wasm32 -emit-llvm -c -S src/${FILE}.c
  llc -o ${BUILD_DIR}/${FILE}.c.ll.o -march=wasm32 -filetype=obj ${BUILD_DIR}/${FILE}.c.ll
done

${WASM_LD} --no-entry --import-undefined --export-all -o ${BUILD_DIR}/${NAME}-temp.wasm ${BUILD_DIR}/*.ll.o

${WASM_2_WAT} ${BUILD_DIR}/${NAME}-temp.wasm > ${BUILD_DIR}/${NAME}.wat
${WAT_2_WASM} -o ${BUILD_DIR}/${NAME}.wasm ${BUILD_DIR}/${NAME}.wat
cp ${BUILD_DIR}/${NAME}.wasm src/${NAME}.wasm
