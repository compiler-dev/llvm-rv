#include "riscv_vector.h"
 vmask_t test_vmseq_vv_u32m1_m(vmask_t mask, vuint32m1_t op1, vuint32m1_t op2){
	return vmseq_vv_u32m1_m(mask,op1,op2);
}
 vmask_t test_vmseq_vv_u32m2_m(vmask_t mask, vuint32m2_t op1, vuint32m2_t op2){
	return vmseq_vv_u32m2_m(mask,op1,op2);
}
 vmask_t test_vmseq_vv_u32m4_m(vmask_t mask, vuint32m4_t op1, vuint32m4_t op2){
	return vmseq_vv_u32m4_m(mask,op1,op2);
}
 vmask_t test_vmseq_vv_u32m8_m(vmask_t mask, vuint32m8_t op1, vuint32m8_t op2){
	return vmseq_vv_u32m8_m(mask,op1,op2);
 }
