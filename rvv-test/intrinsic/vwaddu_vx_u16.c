#include "riscv_vector.h"
 vuint16m2_t test_vwaddu_vx_u16m2(vuint8m1_t op1, uint8_t op2){
	return vwaddu_vx_u16m2(op1,op2);
}
 vuint16m4_t test_vwaddu_vx_u16m4(vuint8m2_t op1, uint8_t op2){
	return vwaddu_vx_u16m4(op1,op2);
}
 vuint16m8_t test_vwaddu_vx_u16m8(vuint8m4_t op1, uint8_t op2){
	return vwaddu_vx_u16m8(op1,op2);
}