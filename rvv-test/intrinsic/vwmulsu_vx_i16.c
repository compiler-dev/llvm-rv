#include "riscv_vector.h"
 vint16m2_t test_vwmulsu_vx_i16m2(vint8m1_t op1, uint8_t op2){
	return vwmulsu_vx_i16m2(op1,op2);
}
 vint16m4_t test_vwmulsu_vx_i16m4(vint8m2_t op1, uint8_t op2){
	return vwmulsu_vx_i16m4(op1,op2);
}
 vint16m8_t test_vwmulsu_vx_i16m8(vint8m4_t op1, uint8_t op2){
	return vwmulsu_vx_i16m8(op1,op2);
}