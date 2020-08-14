#include "riscv_vector.h"
 vint16m2_t test_vwmulsu_vv_i16m2_m(vmask_t mask, vint8m1_t op1, vuint8m1_t op2){
	return vwmulsu_vv_i16m2_m(mask,op1,op2);
}
 vint16m4_t test_vwmulsu_vv_i16m4_m(vmask_t mask, vint8m2_t op1, vuint8m2_t op2){
	return vwmulsu_vv_i16m4_m(mask,op1,op2);
}
 vint16m8_t test_vwmulsu_vv_i16m8_m(vmask_t mask, vint8m4_t op1, vuint8m4_t op2){
	return vwmulsu_vv_i16m8_m(mask,op1,op2);
}