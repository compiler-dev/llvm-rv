#include "riscv_vector.h"
 void test_vsse_v_i8m1(int8_t *base, const int32_t stride, vint8m1_t value){
	vsse_v_i8m1(base,stride,value);
}
 void test_vsse_v_i8m2(int8_t *base, const int32_t stride, vint8m2_t value){
	vsse_v_i8m2(base,stride,value);
}
 void test_vsse_v_i8m4(int8_t *base, const int32_t stride, vint8m4_t value){
	vsse_v_i8m4(base,stride,value);
}
 void test_vsse_v_i8m8(int8_t *base, const int32_t stride, vint8m8_t value){
	vsse_v_i8m8(base,stride,value);
}