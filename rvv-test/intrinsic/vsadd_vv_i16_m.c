#include "riscv_vector.h"
 vint16m1_t test_vsadd_vv_i16m1_m(vmask_t mask, vint16m1_t op1, vint16m1_t op2){
	return vsadd_vv_i16m1_m(mask,op1,op2);
}
 vint16m2_t test_vsadd_vv_i16m2_m(vmask_t mask, vint16m2_t op1, vint16m2_t op2){
	return vsadd_vv_i16m2_m(mask,op1,op2);
}
 vint16m4_t test_vsadd_vv_i16m4_m(vmask_t mask, vint16m4_t op1, vint16m4_t op2){
	return vsadd_vv_i16m4_m(mask,op1,op2);
}
 vint16m8_t test_vsadd_vv_i16m8_m(vmask_t mask, vint16m8_t op1, vint16m8_t op2){
	return vsadd_vv_i16m8_m(mask,op1,op2);
}