#include "riscv_vector.h"
 void test_vsse_v_i8m1_m(vmask_t mask,int8_t *base, const int32_t stride, vint8m1_t value){
	vsse_v_i8m1_m(mask,base,stride,value);
}
 void test_vsse_v_i8m2_m(vmask_t mask,int8_t *base, const int32_t stride, vint8m2_t value){
	vsse_v_i8m2_m(mask,base,stride,value);
}
 void test_vsse_v_i8m4_m(vmask_t mask,int8_t *base, const int32_t stride, vint8m4_t value){
	vsse_v_i8m4_m(mask,base,stride,value);
}
 void test_vsse_v_i8m8_m(vmask_t mask,int8_t *base, const int32_t stride, vint8m8_t value){
	vsse_v_i8m8_m(mask,base,stride,value);
}