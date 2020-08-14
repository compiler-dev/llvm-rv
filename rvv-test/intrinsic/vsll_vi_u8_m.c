#include "riscv_vector.h"
 vuint8m1_t test_vsll_vi_u8m1_m(vmask_t mask, vuint8m1_t op1){
	return vsll_vi_u8m1_m(mask,op1,1);
}
 vuint8m2_t test_vsll_vi_u8m2_m(vmask_t mask, vuint8m2_t op1){
	return vsll_vi_u8m2_m(mask,op1,1);
}
 vuint8m4_t test_vsll_vi_u8m4_m(vmask_t mask, vuint8m4_t op1){
	return vsll_vi_u8m4_m(mask,op1,1);
}
 vuint8m8_t test_vsll_vi_u8m8_m(vmask_t mask, vuint8m8_t op1){
	return vsll_vi_u8m8_m(mask,op1,1);
}