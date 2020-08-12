#include "riscv_vector.h"
  vuint16m2_t test_vwaddu_wv_u16m2_m(vmask_t mask, vuint16m2_t op1, vint8m1_t op2){
	return vwaddu_wv_u16m2_m(mask,op1,op2);
}
 vuint16m4_t test_vwaddu_wv_u16m4_m(vmask_t mask, vuint16m4_t op1, vint8m2_t op2){
	return vwaddu_wv_u16m4_m(mask,op1,op2);
}
 vuint16m8_t test_vwaddu_wv_u16m8_m(vmask_t mask, vuint16m8_t op1, vint8m4_t op2){
	return vwaddu_wv_u16m8_m(mask,op1,op2);
}