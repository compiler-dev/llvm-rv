#include "riscv_vector.h"
 vuint16m2_t test_vwsubu_vx_u16m2_m(vmask_t mask, vuint8m1_t op1, uint8_t op2){
	return vwsubu_vx_u16m2_m(mask,op1,op2);
}
 vuint16m4_t test_vwsubu_vx_u16m4_m(vmask_t mask, vuint8m2_t op1, uint8_t op2){
	return vwsubu_vx_u16m4_m(mask,op1,op2);
}
 vuint16m8_t test_vwsubu_vx_u16m8_m(vmask_t mask, vuint8m4_t op1, uint8_t op2){
	return vwsubu_vx_u16m8_m(mask,op1,op2);
}