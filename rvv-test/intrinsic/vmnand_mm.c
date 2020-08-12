#include "riscv_vector.h"
 vmask_t test_vmnand_mm(vmask_t op1, vmask_t op2){
	return vmnand_mm(op1,op2);
}