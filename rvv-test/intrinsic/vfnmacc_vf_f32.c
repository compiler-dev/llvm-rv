#include "riscv_vector.h"
 vfloat32m1_t test_vfnmacc_vf_f32m1(vfloat32m1_t acc, float32_t op1, vfloat32m1_t op2){
	return vfnmacc_vf_f32m1(acc,op1,op2);
}

 vfloat32m2_t test_vfnmacc_vf_f32m2(vfloat32m2_t acc, float32_t op1, vfloat32m2_t op2){
	return vfnmacc_vf_f32m2(acc,op1,op2);
}

 vfloat32m4_t test_vfnmacc_vf_f32m4(vfloat32m4_t acc, float32_t op1, vfloat32m4_t op2){
	return vfnmacc_vf_f32m4(acc,op1,op2);
}

 vfloat32m8_t test_vfnmacc_vf_f32m8(vfloat32m8_t acc, float32_t op1, vfloat32m8_t op2){
	return vfnmacc_vf_f32m8(acc,op1,op2);
}