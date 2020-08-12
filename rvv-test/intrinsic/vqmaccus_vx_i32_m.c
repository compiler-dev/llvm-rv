#include "riscv_vector.h"
 vint32m4_t test_vqmaccus_vx_i32m4_m (vmask_t mask, vint32m4_t acc, uint8_t op1, vint8m1_t op2){
	return vqmaccus_vx_i32m4_m(mask,acc,op1,op2);	
}
 vint32m8_t test_vqmaccus_vx_i32m8_m (vmask_t mask, vint32m8_t acc, uint8_t op1, vint8m2_t op2){
	return vqmaccus_vx_i32m8_m(mask,acc,op1,op2);	
}