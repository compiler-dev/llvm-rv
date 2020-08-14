#include "riscv_vector.h"
 vint32m1_t test_vadc_vxm_i32m1(vint32m1_t op1, int32_t op2, vmask_t carryin){
	return vadc_vxm_i32m1(op1,op2,carryin);
}
 vint32m2_t test_vadc_vxm_i32m2(vint32m2_t op1, int32_t op2, vmask_t carryin){
	return vadc_vxm_i32m2(op1,op2,carryin);
}
 vint32m4_t test_vadc_vxm_i32m4(vint32m4_t op1, int32_t op2, vmask_t carryin){
	return vadc_vxm_i32m4(op1,op2,carryin);
}
 vint32m8_t test_vadc_vxm_i32m8(vint32m8_t op1, int32_t op2, vmask_t carryin){
	return vadc_vxm_i32m8(op1,op2,carryin);
}