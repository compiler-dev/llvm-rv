#include "riscv_vector.h"
 vmask_t test_vmor_mm(vmask_t op1, vmask_t op2){
	return vmor_mm(op1,op2);
}