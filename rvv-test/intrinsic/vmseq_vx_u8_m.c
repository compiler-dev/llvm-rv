#include "riscv_vector.h"
 vmask_t test_vmseq_vx_u8m1_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return vmseq_vx_u8m1_m(mask,op1,op2);
}
 vmask_t test_vmseq_vx_u8m2_m(vmask_t mask, vuint8m2_t op1, uint8_t op2){
	return vmseq_vx_u8m2_m(mask,op1,op2);
}
 vmask_t test_vmseq_vx_u8m4_m(vmask_t mask, vuint8m4_t op1, uint8_t op2){
	return vmseq_vx_u8m4_m(mask,op1,op2);
}
 vmask_t test_vmseq_vx_u8m8_m(vmask_t mask, vuint8m8_t op1, uint8_t op2){
	return vmseq_vx_u8m8_m(mask,op1,op2);
}