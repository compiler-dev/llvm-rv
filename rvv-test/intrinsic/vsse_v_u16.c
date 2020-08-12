#include "riscv_vector.h"
void test_vsse_v_u16m1(uint16_t *base, const int32_t stride, vuint16m1_t value){
	vsse_v_u16m1(base,stride,value);
}
 void test_vsse_v_u16m2(uint16_t *base, const int32_t stride, vuint16m2_t value){
	vsse_v_u16m2(base,stride,value);
}
 void test_vsse_v_u16m4(uint16_t *base, const int32_t stride, vuint16m4_t value){
	vsse_v_u16m4(base,stride,value);
}
 void test_vsse_v_u16m8(uint16_t *base, const int32_t stride, vuint16m8_t value){
	vsse_v_u16m8(base,stride,value);
}