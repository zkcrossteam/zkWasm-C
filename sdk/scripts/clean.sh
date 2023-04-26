#!/bin/bash
echo "Script executed from: ${PWD}"

SCRIPT=$(realpath "$0")
SCRIPT_PATH=$(dirname $SCRIPT)
TOP_PATH=$SCRIPT_PATH/..

MAKEFILE=$SCRIPT_PATH/Makefile

make clean -C $TOP_PATH/c/sdk/lib -f $MAKEFILE
make clean -C $TOP_PATH/c/rlp/lib -f $MAKEFILE
make clean -C $TOP_PATH/c/hash/lib -f $MAKEFILE
make clean -C $TOP_PATH/c/ecc/lib -f $MAKEFILE
make clean -C $TOP_PATH/c/kvpair/lib -f $MAKEFILE
