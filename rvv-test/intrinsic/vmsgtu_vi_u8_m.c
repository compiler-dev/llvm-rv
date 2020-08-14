#include "riscv_vector.h"
 vmask_t test_vmsgtu_vi_u8m1_m(vmask_t mask, vuint8m1_t op1){
	return vmsgtu_vi_u8m1_m(mask,op1,1);
}
 vmask_t test_vmsgtu_vi_u8m2_m(vmask_t mask, vuint8m2_t op1){
	return vmsgtu_vi_u8m2_m(mask,op1,1);
}
 vmask_t test_vmsgtu_vi_u8m4_m(vmask_t mask, vuint8m4_t op1){
	return vmsgtu_vi_u8m4_m(mask,op1,1);
}
 vmask_t test_vmsgtu_vi_u8m8_m(vmask_t mask, vuint8m8_t op1){
	return vmsgtu_vi_u8m8_m(mask,op1,1);
}