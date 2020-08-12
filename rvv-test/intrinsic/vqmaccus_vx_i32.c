#include "riscv_vector.h"
vint32m4_t test_vqmaccus_vx_i32m4 (vint32m4_t acc, uint8_t op1, vint8m1_t op2){
	return vqmaccus_vx_i32m4(acc,op1,op2);	
}
 vint32m8_t test_vqmaccus_vx_i32m8 (vint32m8_t acc, uint8_t op1, vint8m2_t op2){
	return vqmaccus_vx_i32m8(acc,op1,op2);	
}