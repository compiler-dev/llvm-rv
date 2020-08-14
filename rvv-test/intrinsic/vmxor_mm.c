#include "riscv_vector.h"
 vmask_t test_vmxor_mm(vmask_t op1, vmask_t op2){
	return vmxor_mm(op1,op2);
}