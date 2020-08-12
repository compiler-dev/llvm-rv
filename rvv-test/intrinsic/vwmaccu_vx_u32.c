#include "riscv_vector.h"
 vuint32m2_t test_vwmaccu_vx_u32m2(vuint32m2_t acc, uint16_t op1, vuint16m1_t op2){
	return vwmaccu_vx_u32m2(acc,op1,op2);
}
 vuint32m4_t test_vwmaccu_vx_u32m4(vuint32m4_t acc, uint16_t op1, vuint16m2_t op2){
	return vwmaccu_vx_u32m4(acc,op1,op2);
}
 vuint32m8_t test_vwmaccu_vx_u32m8(vuint32m8_t acc, uint16_t op1, vuint16m4_t op2){
	return vwmaccu_vx_u32m8(acc,op1,op2);
}