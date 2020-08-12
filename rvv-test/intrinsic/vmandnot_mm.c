#include "riscv_vector.h"
 vmask_t test_vmandnot_mm(vmask_t op1, vmask_t op2){
	return vmandnot_mm(op1,op2);
}