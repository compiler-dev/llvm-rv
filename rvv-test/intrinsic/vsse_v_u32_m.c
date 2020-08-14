#include "riscv_vector.h"
void test_vsse_v_u32m1_m(vmask_t mask,uint32_t *base, const int32_t stride, vuint32m1_t value){
	vsse_v_u32m1_m(mask,base,stride,value);
}
 void test_vsse_v_u32m2_m(vmask_t mask,uint32_t *base, const int32_t stride, vuint32m2_t value){
	vsse_v_u32m2_m(mask,base,stride,value);
}
 void test_vsse_v_u32m4_m(vmask_t mask,uint32_t *base, const int32_t stride, vuint32m4_t value){
	vsse_v_u32m4_m(mask,base,stride,value);
}
 void test_vsse_v_u32m8_m(vmask_t mask,uint32_t *base, const int32_t stride, vuint32m8_t value){
	vsse_v_u32m8_m(mask,base,stride,value);
}
