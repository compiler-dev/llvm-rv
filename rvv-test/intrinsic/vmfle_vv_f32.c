#include "riscv_vector.h"

vmask_t test_vmfle_vv_f32m1(vfloat32m1_t op1, vfloat32m1_t op2){
	return vmfle_vv_f32m1(op1,op2);
}

vmask_t test_vmfle_vv_f32m2(vfloat32m2_t op1, vfloat32m2_t op2){
	return vmfle_vv_f32m2(op1,op2);
}

vmask_t test_vmfle_vv_f32m4(vfloat32m4_t op1, vfloat32m4_t op2){
	return vmfle_vv_f32m4(op1,op2);
}

vmask_t test_vmfle_vv_f32m8(vfloat32m8_t op1, vfloat32m8_t op2){
	return vmfle_vv_f32m8(op1,op2);
}