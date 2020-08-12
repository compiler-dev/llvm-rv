#include "riscv_vector.h"
 vfloat32m1_t test_vfnmacc_vv_f32m1_m(vmask_t mask, vfloat32m1_t acc, vfloat32m1_t op1, vfloat32m1_t op2){
	return vfnmacc_vv_f32m1_m(mask,acc,op1,op2);
}

 vfloat32m2_t test_vfnmacc_vv_f32m2_m(vmask_t mask, vfloat32m2_t acc, vfloat32m2_t op1, vfloat32m2_t op2){
	return vfnmacc_vv_f32m2_m(mask,acc,op1,op2);
}

 vfloat32m4_t test_vfnmacc_vv_f32m4_m(vmask_t mask, vfloat32m4_t acc, vfloat32m4_t op1, vfloat32m4_t op2){
	return vfnmacc_vv_f32m4_m(mask,acc,op1,op2);
}

 vfloat32m8_t test_vfnmacc_vv_f32m8_m(vmask_t mask, vfloat32m8_t acc, vfloat32m8_t op1, vfloat32m8_t op2){
	return vfnmacc_vv_f32m8_m(mask,acc,op1,op2);
}