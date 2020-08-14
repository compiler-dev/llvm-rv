#include "riscv_vector.h"
 vuint8m1_t test_vor_vx_u8m1(vuint8m1_t op1, uint8_t op2){
	return vor_vx_u8m1(op1,op2);
}
 vuint8m2_t test_vor_vx_u8m2(vuint8m2_t op1, uint8_t op2){
	return vor_vx_u8m2(op1,op2);
}
 vuint8m4_t test_vor_vx_u8m4(vuint8m4_t op1, uint8_t op2){
	return vor_vx_u8m4(op1,op2);
}
 vuint8m8_t test_vor_vx_u8m8(vuint8m8_t op1, uint8_t op2){
	return vor_vx_u8m8(op1,op2);
}