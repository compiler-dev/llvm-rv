# Note:
## Test cases for instrinsic APIs.
* $ clang -S --target=riscv32 -march=rv32imafcv test.c -o test.s
* $ llvm-mc test.s -march=riscv32 -mattr=+m,+a,+f,+c,+v -filetype=obj -o test.o
* $ llvm-objdump -mattr=+m,+a,+v,+c,+v -disassemble test.o
