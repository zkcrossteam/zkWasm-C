#!/bin/bash
echo "Script executed from: ${PWD}"

WASMLD=wasm-ld-15

SCRIPT=$(realpath "$0")
SCRIPT_PATH=$(dirname $SCRIPT)
TOP_PATH=$SCRIPT_PATH/..

MAKEFILE=$SCRIPT_PATH/Makefile

if [ $# -eq 0 ]; then
    echo "No arguments provided"
    exit 1
fi

make -C $TOP_PATH/c/sdk/lib -f $MAKEFILE
make -C $TOP_PATH/c/rlp/lib -f $MAKEFILE
make -C $TOP_PATH/c/hash/lib -f $MAKEFILE

ALL_LIBS=$(find $TOP_PATH/c/*/lib/ -type f -name "*.wasm")

$WASMLD $ALL_LIBS -r -o $1
