#include "riscv_vector.h"
 vint8m1_t test_vsadd_vx_i8m1_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return vsadd_vx_i8m1_m(mask,op1,op2);
}
 vint8m2_t test_vsadd_vx_i8m2_m(vmask_t mask, vint8m2_t op1, int8_t op2){
	return vsadd_vx_i8m2_m(mask,op1,op2);
}
 vint8m4_t test_vsadd_vx_i8m4_m(vmask_t mask, vint8m4_t op1, int8_t op2){
	return vsadd_vx_i8m4_m(mask,op1,op2);
}
 vint8m8_t test_vsadd_vx_i8m8_m(vmask_t mask, vint8m8_t op1, int8_t op2){
	return vsadd_vx_i8m8_m(mask,op1,op2);
}