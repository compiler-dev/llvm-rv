#include "riscv_vector.h"
 vint16m2_t test_vwmacc_vv_i16m2_m(vmask_t mask, vint16m2_t acc, vint8m1_t op1, vint8m1_t op2){
	return vwmacc_vv_i16m2_m(mask,acc,op1,op2);
}
 vint16m4_t test_vwmacc_vv_i16m4_m(vmask_t mask, vint16m4_t acc, vint8m2_t op1, vint8m2_t op2){
	return vwmacc_vv_i16m4_m(mask,acc,op1,op2);
}
 vint16m8_t test_vwmacc_vv_i16m8_m(vmask_t mask, vint16m8_t acc, vint8m4_t op1, vint8m4_t op2){
	return vwmacc_vv_i16m8_m(mask,acc,op1,op2);
}

