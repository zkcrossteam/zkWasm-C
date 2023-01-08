# zkWasm-C
## About C template for ZKWASM:
This is a project template for constructing wasm program for ZKWASM using C language.
It contains two directories which are **./sdk** and **./proejct**.
1. sdk directory:  Contains basic built-in c libraries and head files.
2. project directory: Contains an example project that can be compiled into a wasm output.

## Usage:
You can modify the code in ./project directory and use **make** to compile the project into output.wasm.

## Building Requirement:
You need clang (better with version 15) to compile and link C code into wasm.

## Run the output:
The output.wasm file is a standard web assembly image that can be run using any wasm interpreter which provides necessary host functions. 
Currently, there are three main scenarios:
1. run the wasm image in a web environment for web games and generates instances for proof generation. (An example can be found at https://github.com/ZhenXunGe/g1024).
2. run the wasm image in a backend environment with zkWASM virtual machine and generate proofs for on-chain verification. (See https://github.com/DelphinusLab/zkWasm for the command line usage of zkWASM virtual machine)
3. run the wasm image in LAYER-TWO that supports zkWASM (currently ZKCross) and let ZCcross do the tedious work of synchronizing and settlement in a cross-chain manner.
