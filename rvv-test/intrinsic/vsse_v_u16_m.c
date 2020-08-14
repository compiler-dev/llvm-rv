#include "riscv_vector.h"
void test_vsse_v_u16m1_m(vmask_t mask,uint16_t *base, const int32_t stride, vuint16m1_t value){
	vsse_v_u16m1_m(mask,base,stride,value);
}
 void test_vsse_v_u16m2_m(vmask_t mask,uint16_t *base, const int32_t stride, vuint16m2_t value){
	vsse_v_u16m2_m(mask,base,stride,value);
}
 void test_vsse_v_u16m4_m(vmask_t mask,uint16_t *base, const int32_t stride, vuint16m4_t value){
	vsse_v_u16m4_m(mask,base,stride,value);
}
 void test_vsse_v_u16m8_m(vmask_t mask,uint16_t *base, const int32_t stride, vuint16m8_t value){
	vsse_v_u16m8_m(mask,base,stride,value);
}
