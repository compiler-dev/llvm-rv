#include "riscv_vector.h"
void test_vsse_v_i32m1_m(vmask_t mask,int32_t *base, const int32_t stride, vint32m1_t value){
	vsse_v_i32m1_m(mask,base,stride,value);
}
 void test_vsse_v_i32m2_m(vmask_t mask,int32_t *base, const int32_t stride, vint32m2_t value){
	vsse_v_i32m2_m(mask,base,stride,value);
}
 void test_vsse_v_i32m4_m(vmask_t mask,int32_t *base, const int32_t stride, vint32m4_t value){
	vsse_v_i32m4_m(mask,base,stride,value);
}
 void test_vsse_v_i32m8_m(vmask_t mask,int32_t *base, const int32_t stride, vint32m8_t value){
	vsse_v_i32m8_m(mask,base,stride,value);
}