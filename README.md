# RISC-V in LLVM and CLANG for Vector Extension
This is the RISC-V Vector Extension in LLVM and CLANG implemented by Hunan Compiler Information Technology Co., Ltd,
http://www.compiler-dev.com, Email: <info@compiler-dev.com>, according to Riscv-v-spec-0.8,with isa=rv32imafcv and vlen=128.

The README briefly describes how to get started with building LLVM and CLANG, and how to run
a rvv test in spike on a linux x86 machine as an example.

## Pre-requirements

This compiler depends on the GNU ld, newlib, and libgcc. If you'd like to run the compiled program on a
emulator, the SPIKE is also needed. We provide these pre-compiled binaries for linux x86 platform.

https://github.com/compiler-dev/rvvtool-chain-binaries

We support that the path of the rvvtool-chain-binaries is TOOL_CHAIN_PATH.

You could also build these tools from the source codes by the following steps.

1. Build riscv-gnu-toolchain
* $ git clone https://github.com/riscv/riscv-gnu-toolchain
* $ cd riscv-gnu-toolchain
* $ git submodule update --init --recursive
* $ ./configure --with-arch=rv32imafc --with-abi=ilp32 --prefix=$TOOL_CHAIN_PATH
* $ make 

2. Build spike
* $ git clone https://github.com/riscv/riscv-isa-sim.git
* $ apt-get install device-tree-compiler
* $ mkdir spike-build
* $ cd spike-build
* $ ../riscv-isa-sim-master/configure --with-varch=vlen:128,elen:32,slen:128 --with-isa=rv32imafcv \
	--prefix=$TOOL_CHAIN_PATH
* $ make && make install

3. Build riscv pk
* $ git clone https://github.com/riscv/riscv-pk.git
* $ mkdir pk-build
* $ cd pk-build
* $ export PATH=$TOOL_CHAIN_PATH/bin:$PATH
* $ export CFLAGS=-D__riscv_compressed
* $ ../riscv-pk/configure --host=riscv32-unknown-elf --with-arch=rv32i --prefix=$TOOL_CHAIN_PATH \
	CC=riscv32-unknown-elf-gcc
* $ make && make install
 
## How to build this LLVM and CLANG for RISC-V Target
* $ git clone https://github.com/compiler-dev/llvm-rv.git
* $ cd llvm-rv
* $ git checkout vector
* $ mkdir build 
* $ cd build
* $ cmake -G "Unix Makefiles" -DLLVM_TARGETS_TO_BUILD="RISCV" \
	-DLLVM_DEFAULT_TARGET_TRIPLE=riscv32-unknown-elf \
	-DCMAKE_BUILD_TYPE=Release -DDEFAULT_SYSROOT=$TOOL_CHAIN_PATH/riscv32-unknown-elf \
	-DLLVM_ENABLE_PROJECTS=clang -DCMAKE_INSTALL_PREFIX=$TOOL_CHAIN_PATH ../llvm
* $ make && make install

## How to run a rvv test vadd_vv_i32.c in SPIKE  
* $ export PATH=$TOOL_CHAIN_PATH/bin:$PATH  
* $ cd llvm-rv/rvv-test  
* $ clang vadd_vv_i32.c -O2 --target=riscv32 -march=rv32imafcv -std=gnu99 -Wa,-march=rv32imafcv \
	TOOL_CHAIN_PATH/riscv32-unknown-elf/lib/crt0.o -L$TOOL_CHAIN_PATH/riscv32-unknown-elf/lib \
	-L$TOOL_CHAIN_PATH/lib/gcc/riscv32-unknown-elf/10.0.1 -nostartfiles -Wl, -lc -lgcc -lm -lsim -Wl, \
	-o vadd_vv_i32.out --rtlib=libgcc  
* $ spike $TOOL_CHAIN_PATH/riscv32-unknown-elf/bin/pk ./vadd_vv_i32.out

* Output:  
	Expect:  
	{0x7fffffff,0x80000001,0x80000003,0x80000005}  
	Actual:  
	{0x7fffffff,0x80000001,0x80000003,0x80000005}  
	pass!  

#Note
In the rvv-test directory, there are two directories besides three testcases which could be run in SPIKE. 
* intrinsic: Intrinsics API test cases which are all for compiling.
* KmplIntrinsicAPI: Documents for intrinsics API. You could begin with riscv_vector.h.html	
