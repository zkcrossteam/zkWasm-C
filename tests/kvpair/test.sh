#!/bin/bash

set -e
set -x

#rm -rf output
#mkdir output

# Single test
RUST_LOG=info ~/zkWasm/target/release/cli  -k 18 --function zkmain --output ./output --wasm output.wasm setup

RUST_LOG=info ~/zkWasm/target/release/cli  -k 18 --function zkmain --output ./output --wasm output.wasm single-prove
RUST_LOG=info ~/zkWasm/target/release/cli  -k 18 --function zkmain --output ./output --wasm output.wasm single-verify --proof output/zkwasm.0.transcript.data
