#include "riscv_vector.h"
 vuint32m2_t test_vwaddu_vv_u32m2(vmask_t mask, vuint16m1_t op1, vuint16m1_t op2){
	return vwaddu_vv_u32m2_m(mask,op1,op2);
}
 vuint32m4_t test_vwaddu_vv_u32m4(vmask_t mask, vuint16m2_t op1, vuint16m2_t op2){
	return vwaddu_vv_u32m4_m(mask,op1,op2);
}
 vuint32m8_t test_vwaddu_vv_u32m8(vmask_t mask, vuint16m4_t op1, vuint16m4_t op2){
	return vwaddu_vv_u32m8_m(mask,op1,op2);
}