#include "riscv_vector.h"
vfloat32m1_t test_vcompress_vm_f32m1(vmask_t mask,vfloat32m1_t op1){
	return vcompress_vm_f32m1(mask,op1);
}

 vfloat32m2_t test_vcompress_vm_f32m2(vmask_t mask,vfloat32m2_t op1){
	return vcompress_vm_f32m2(mask,op1);
}

 vfloat32m4_t test_vcompress_vm_f32m4(vmask_t mask,vfloat32m4_t op1){
	return vcompress_vm_f32m4(mask,op1);
}

 vfloat32m8_t test_vcompress_vm_f32m8(vmask_t mask,vfloat32m8_t op1){
	return vcompress_vm_f32m8(mask,op1);
}





