#include "riscv_vector.h"
 vmask_t test_vmsgtu_vi_u32m1_m(vmask_t mask, vuint32m1_t op1){
	return vmsgtu_vi_u32m1_m(mask,op1,1);
}
 vmask_t test_vmsgtu_vi_u32m2_m(vmask_t mask, vuint32m2_t op1){
	return vmsgtu_vi_u32m2_m(mask,op1,1);
}
 vmask_t test_vmsgtu_vi_u32m4_m(vmask_t mask, vuint32m4_t op1){
	return vmsgtu_vi_u32m4_m(mask,op1,1);
}
 vmask_t test_vmsgtu_vi_u32m8_m(vmask_t mask, vuint32m8_t op1){
	return vmsgtu_vi_u32m8_m(mask,op1,1);
}