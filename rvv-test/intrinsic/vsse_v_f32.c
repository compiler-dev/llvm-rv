#include "riscv_vector.h"
void test_vsse_v_f32m1(float32_t *base, const int32_t stride, vfloat32m1_t value){
	vsse_v_f32m1(base,stride,value);
}
 void test_vsse_v_f32m2(float32_t *base, const int32_t stride, vfloat32m2_t value){
	vsse_v_f32m2(base,stride,value);
}
 void test_vsse_v_f32m4(float32_t *base, const int32_t stride, vfloat32m4_t value){
	vsse_v_f32m4(base,stride,value);
}
 void test_vsse_v_f32m8(float32_t *base, const int32_t stride, vfloat32m8_t value){
	vsse_v_f32m8(base,stride,value);
}