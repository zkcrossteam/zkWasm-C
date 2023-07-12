#!/bin/bash
echo "Script executed from: ${PWD}"

SCRIPT=$(realpath "$0")
SCRIPT_PATH=$(dirname $SCRIPT)
TOP_PATH=$SCRIPT_PATH/..

MAKEFILE=$SCRIPT_PATH/Makefile

DIR_SDK_LIB="$TOP_PATH/c/sdk/lib"
DIR_RLP_LIB="$TOP_PATH/c/rlp/lib"
DIR_HASH_LIB="$TOP_PATH/c/hash/lib"
DIR_ECC_LIB="$TOP_PATH/c/ecc/lib"
DIR_KVPAIR_LIB="$TOP_PATH/c/kvpair/lib"

if [ -d "$DIR_SDK_LIB" ]; then
    make clean -C $TOP_PATH/c/sdk/lib -f $MAKEFILE
fi
if [ -d "$DIR_RLP_LIB" ]; then
    make clean -C $TOP_PATH/c/rlp/lib -f $MAKEFILE
fi
if [ -d "$DIR_HASH_LIB" ]; then
    make clean -C $TOP_PATH/c/hash/lib -f $MAKEFILE
fi
if [ -d "$DIR_ECC_LIB" ]; then
    make clean -C $TOP_PATH/c/ecc/lib -f $MAKEFILE
fi
if [ -d "$DIR_KVPAIR_LIB" ]; then
    make clean -C $TOP_PATH/c/kvpair/lib -f $MAKEFILE
fi
