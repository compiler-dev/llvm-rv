#include "riscv_vector.h"
void test_vsse_v_u8m1(uint8_t *base, const int32_t stride, vuint8m1_t value){
	vsse_v_u8m1(base,stride,value);
}
 void test_vsse_v_u8m2(uint8_t *base, const int32_t stride, vuint8m2_t value){
	vsse_v_u8m2(base,stride,value);
}
 void test_vsse_v_u8m4(uint8_t *base, const int32_t stride, vuint8m4_t value){
	vsse_v_u8m4(base,stride,value);
}
 void test_vsse_v_u8m8(uint8_t *base, const int32_t stride, vuint8m8_t value){
	vsse_v_u8m8(base,stride,value);
}
