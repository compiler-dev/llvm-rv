#include "riscv_vector.h"
 vmask_t test_vmxnor_mm(vmask_t op1, vmask_t op2){
	return vmxnor_mm(op1,op2);
}