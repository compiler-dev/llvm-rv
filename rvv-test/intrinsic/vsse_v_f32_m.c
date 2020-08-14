#include "riscv_vector.h"
void test_vsse_v_f32m1_m(vmask_t mask,float32_t *base, const int32_t stride, vfloat32m1_t value){
	vsse_v_f32m1_m(mask,base,stride,value);
}
 void test_vsse_v_f32m2_m(vmask_t mask,float32_t *base, const int32_t stride, vfloat32m2_t value){
	vsse_v_f32m2_m(mask,base,stride,value);
}
 void test_vsse_v_f32m4_m(vmask_t mask,float32_t *base, const int32_t stride, vfloat32m4_t value){
	vsse_v_f32m4_m(mask,base,stride,value);
}
 void test_vsse_v_f32m8_m(vmask_t mask,float32_t *base, const int32_t stride, vfloat32m8_t value){
	vsse_v_f32m8_m(mask,base,stride,value);
}
