#include "riscv_vector.h"
 vuint16m1_t test_vsaddu_vi_u16m1_m(vmask_t mask, vuint16m1_t op1){
	return vsaddu_vi_u16m1_m(mask,op1,1);
}
 vuint16m2_t test_vsaddu_vi_u16m2_m(vmask_t mask, vuint16m2_t op1){
	return vsaddu_vi_u16m2_m(mask,op1,1);
}
 vuint16m4_t test_vsaddu_vi_u16m4_m(vmask_t mask, vuint16m4_t op1){
	return vsaddu_vi_u16m4_m(mask,op1,1);
}
 vuint16m8_t test_vsaddu_vi_u16m8_m(vmask_t mask, vuint16m8_t op1){
	return vsaddu_vi_u16m8_m(mask,op1,1);
}