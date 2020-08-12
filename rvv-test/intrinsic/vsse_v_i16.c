#include "riscv_vector.h"
void test_vsse_v_i16m1(int16_t *base, const int32_t stride, vint16m1_t value){
	vsse_v_i16m1(base,stride,value);
}
 void test_vsse_v_i16m2(int16_t *base, const int32_t stride, vint16m2_t value){
	vsse_v_i16m2(base,stride,value);
}
 void test_vsse_v_i16m4(int16_t *base, const int32_t stride, vint16m4_t value){
	vsse_v_i16m4(base,stride,value);
}
 void test_vsse_v_i16m8(int16_t *base, const int32_t stride, vint16m8_t value){
	vsse_v_i16m8(base,stride,value);
}