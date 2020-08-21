# Full Support 32bit RISC-V in LLVM and CLANG for Vector Extension
This is the RISC-V Vector Extension support in LLVM and CLANG implemented by Hunan Compiler Information Technology Co., Ltd
(http://www.compiler-dev.com, Email: <info@compiler-dev.com>). So far the compiler has been compatible with the Riscv-v-spec-0.8.
Please add isa=rv32imafcv and vlen=128 options to the command line as compiling source codes.

This implementation includes Clang C/C++ compiler, llvm-mc assembler, and llvm-objdump disassembler. The RISC-V Vector
Extension module is fully supported using more than 6000 intrinsic interfaces.

The README briefly describes how to get started with building LLVM and CLANG, and how to run
a rvv test in spike on a linux x86 machine as an example.

## Pre-requirements

This compiler depends on the GNU ld, newlib, and libgcc. If you'd like to run the compiled program on a
emulator, the SPIKE is also needed. We provide these pre-compiled binaries for linux x86 platform.

https://github.com/compiler-dev/rvvtool-chain-binaries

You could also build these tools from the source codes by the following steps. 
Suppose that the path of the rvvtool-chain-binaries is TOOL_CHAIN_PATH.

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
* $ clang vadd_vv_i32.c -O2 --target=riscv32 -march=rv32imafcv --sysroot=$TOOL_CHAIN_PATH/riscv-unknown-elf \
	--gcc-toolchain=$TOOL_CHAIN_PATH -o vadd_vv_i32.out  
* $ spike $TOOL_CHAIN_PATH/riscv32-unknown-elf/bin/pk ./vadd_vv_i32.out

* Output:  
	Expect:  
	{0x7fffffff,0x80000001,0x80000003,0x80000005}  
	Actual:  
	{0x7fffffff,0x80000001,0x80000003,0x80000005}  
	pass!  

If the program uses the floating-point instructions, the FPU should be enabled by replacing some files in the rvvtool-chain-binaries.

* $ cp -r $TOOL_CHAIN_PATH/enable-fp/usr $TOOL_CHAIN_PATH/

The following example comes from RISC-V Vector Extension Intrinsic Document (https://github.com/riscv/rvv-intrinsic-doc).

* $ clang rvv_sgemm.c -O2 --target=riscv32 -march=rv32imafcv --sysroot=$TOOL_CHAIN_PATH/riscv32-unknown-elf 
	--gcc-toolchain=$TOOL_CHAIN_PATH -nodefaultlibs -Wl,--start-group -lc -lgcc -lm -lsim -Wl, --end-group \
	-T $TOOL_CHAIN_PATH/bin/link.ld -o rvv_sgemm.out
* $ spike -m0x10000000:0x200000 ./rvv_sgemm.out

#Note
In the rvv-test directory, there are two directories besides three testcases which could be run in SPIKE. 
* intrinsic: Intrinsic APIs test cases.
* KmplIntrinsicAPI: Documents for more than 6,000 intrinsic APIs. You could begin with riscv_vector.h.html.	
