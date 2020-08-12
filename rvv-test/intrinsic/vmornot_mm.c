#include "riscv_vector.h"
 vmask_t test_vmornot_mm(vmask_t op1, vmask_t op2){
	return vmornot_mm(op1,op2);
}