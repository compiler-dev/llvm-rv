#include "riscv_vector.h"
 vmask_t test_vmseq_vi_i8m1_m(vmask_t mask, vint8m1_t op1){
	return vmseq_vi_i8m1_m(mask,op1,1);
}
 vmask_t test_vmseq_vi_i8m2_m(vmask_t mask, vint8m2_t op1){
	return vmseq_vi_i8m2_m(mask,op1,1);
}
 vmask_t test_vmseq_vi_i8m4_m(vmask_t mask, vint8m4_t op1){
	return vmseq_vi_i8m4_m(mask,op1,1);
}
 vmask_t test_vmseq_vi_i8m8_m(vmask_t mask, vint8m8_t op1){
	return vmseq_vi_i8m8_m(mask,op1,1);
}