#include "riscv_vector.h"
 vuint32m4_t test_vqmaccu_vx_u32m4 (vuint32m4_t acc, uint8_t op1, vuint8m1_t op2){
	return vqmaccu_vx_u32m4(acc,op1,op2);
}
 vuint32m8_t test_vqmaccu_vx_u32m8 (vuint32m8_t acc, uint8_t op1, vuint8m2_t op2){
	return vqmaccu_vx_u32m8(acc,op1,op2);
}