#include "riscv_vector.h"
vuint32m1_t test_vcompress_vm_u32m1(vmask_t mask,vuint32m1_t op1){
	return vcompress_vm_u32m1(mask,op1);
}

 vuint32m2_t test_vcompress_vm_u32m2(vmask_t mask,vuint32m2_t op1){
	return vcompress_vm_u32m2(mask,op1);
}

 vuint32m4_t test_vcompress_vm_u32m4(vmask_t mask,vuint32m4_t op1){
	return vcompress_vm_u32m4(mask,op1);
}

 vuint32m8_t test_vcompress_vm_u32m8(vmask_t mask,vuint32m8_t op1){
	return vcompress_vm_u32m8(mask,op1);
}





