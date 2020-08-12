#include "riscv_vector.h"
void test_vsse_v_u8m1_m(vmask_t mask,uint8_t *base, const int32_t stride, vuint8m1_t value){
	vsse_v_u8m1_m(mask,base,stride,value);
}
 void test_vsse_v_u8m2_m(vmask_t mask,uint8_t *base, const int32_t stride, vuint8m2_t value){
	vsse_v_u8m2_m(mask,base,stride,value);
}
 void test_vsse_v_u8m4_m(vmask_t mask,uint8_t *base, const int32_t stride, vuint8m4_t value){
	vsse_v_u8m4_m(mask,base,stride,value);
}
 void test_vsse_v_u8m8_m(vmask_t mask,uint8_t *base, const int32_t stride, vuint8m8_t value){
	vsse_v_u8m8_m(mask,base,stride,value);
}
