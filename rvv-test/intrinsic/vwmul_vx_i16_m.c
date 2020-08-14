#include "riscv_vector.h"
 vint16m2_t test_vwmul_vx_i16m2_m(vmask_t mask, vint8m1_t op1, int8_t op2){
	return vwmul_vx_i16m2_m(mask,op1,op2);
}
 vint16m4_t test_vwmul_vx_i16m4_m(vmask_t mask, vint8m2_t op1, int8_t op2){
	return vwmul_vx_i16m4_m(mask,op1,op2);
}
 vint16m8_t test_vwmul_vx_i16m8_m(vmask_t mask, vint8m4_t op1, int8_t op2){
	return vwmul_vx_i16m8_m(mask,op1,op2);
}