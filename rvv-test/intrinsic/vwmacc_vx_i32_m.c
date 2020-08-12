#include "riscv_vector.h"
 vint32m2_t test_vwmacc_vx_i32m2_m(vmask_t mask, vint32m2_t acc, int16_t op1, vint16m1_t op2){
	return vwmacc_vx_i32m2_m(mask,acc,op1,op2);
}
 vint32m4_t test_vwmacc_vx_i32m4_m(vmask_t mask, vint32m4_t acc, int16_t op1, vint16m2_t op2){
	return vwmacc_vx_i32m4_m(mask,acc,op1,op2);
}
 vint32m8_t test_vwmacc_vx_i32m8_m(vmask_t mask, vint32m8_t acc, int16_t op1, vint16m4_t op2){
	return vwmacc_vx_i32m8_m(mask,acc,op1,op2);
}

