#include "riscv_vector.h"
 vmask_t test_vmand_mm(vmask_t op1, vmask_t op2){
	return vmand_mm(op1,op2);
}