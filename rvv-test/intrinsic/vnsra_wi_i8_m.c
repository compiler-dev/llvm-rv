#include "riscv_vector.h"
 vint8m1_t test_vnsra_wi_i8m1_m(vmask_t mask, vint16m2_t op1){
	return vnsra_wi_i8m1_m(mask,op1,1);
}
 vint8m2_t test_vnsra_wi_i8m2_m(vmask_t mask, vint16m4_t op1){
	return vnsra_wi_i8m2_m(mask,op1,1);
}
 vint8m4_t test_vnsra_wi_i8m4_m(vmask_t mask, vint16m8_t op1){
	return vnsra_wi_i8m4_m(mask,op1,1);
}