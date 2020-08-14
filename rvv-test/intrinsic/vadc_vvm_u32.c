#include "riscv_vector.h"
 vuint32m1_t test_vadc_vvm_u32m1(vuint32m1_t op1, vuint32m1_t op2, vmask_t carryin){
	return vadc_vvm_u32m1(op1,op2,carryin);
}
 vuint32m2_t test_vadc_vvm_u32m2(vuint32m2_t op1, vuint32m2_t op2, vmask_t carryin){
	return vadc_vvm_u32m2(op1,op2,carryin);
}
 vuint32m4_t test_vadc_vvm_u32m4(vuint32m4_t op1, vuint32m4_t op2, vmask_t carryin){
	return vadc_vvm_u32m4(op1,op2,carryin);
}
 vuint32m8_t test_vadc_vvm_u32m8(vuint32m8_t op1, vuint32m8_t op2, vmask_t carryin){
	return vadc_vvm_u32m8(op1,op2,carryin);
}
