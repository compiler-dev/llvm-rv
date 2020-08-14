#include "riscv_vector.h"
 vmask_t test_vmadc_vxm_u16m1(vuint16m1_t op1, uint16_t op2, vmask_t carryin){
	return vmadc_vxm_u16m1(op1,op2,carryin);
}
 vmask_t test_vmadc_vxm_u16m2(vuint16m2_t op1, uint16_t op2, vmask_t carryin){
	return vmadc_vxm_u16m2(op1,op2,carryin);
}
 vmask_t test_vmadc_vxm_u16m4(vuint16m4_t op1, uint16_t op2, vmask_t carryin){
	return vmadc_vxm_u16m4(op1,op2,carryin);
}
 vmask_t test_vmadc_vxm_u16m8(vuint16m8_t op1, uint16_t op2, vmask_t carryin){
	return vmadc_vxm_u16m8(op1,op2,carryin);
}