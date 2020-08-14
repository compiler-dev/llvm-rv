#include "riscv_vector.h"
void test_vsse_v_u32m1(uint32_t *base, const int32_t stride, vuint32m1_t value){
	vsse_v_u32m1(base,stride,value);
}
 void test_vsse_v_u32m2(uint32_t *base, const int32_t stride, vuint32m2_t value){
	vsse_v_u32m2(base,stride,value);
}
 void test_vsse_v_u32m4(uint32_t *base, const int32_t stride, vuint32m4_t value){
	vsse_v_u32m4(base,stride,value);
}
 void test_vsse_v_u32m8(uint32_t *base, const int32_t stride, vuint32m8_t value){
	vsse_v_u32m8(base,stride,value);
}