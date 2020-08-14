#include "riscv_vector.h"
 vmask_t test_vmadc_vvm_u32m1(vuint32m1_t op1, vuint32m1_t op2, vmask_t carryin){
	return vmadc_vvm_u32m1(op1,op2,carryin);
}
 vmask_t test_vmadc_vvm_u32m2(vuint32m2_t op1, vuint32m2_t op2, vmask_t carryin){
	return vmadc_vvm_u32m2(op1,op2,carryin);
}
 vmask_t test_vmadc_vvm_u32m4(vuint32m4_t op1, vuint32m4_t op2, vmask_t carryin){
	return vmadc_vvm_u32m4(op1,op2,carryin);
}
 vmask_t test_vmadc_vvm_u32m8(vuint32m8_t op1, vuint32m8_t op2, vmask_t carryin){
	return vmadc_vvm_u32m8(op1,op2,carryin);
}