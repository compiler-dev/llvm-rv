 #include "riscv_vector.h"
 vuint8m1_t test_vmadd_vx_u8m1(vuint8m1_t acc, uint8_t op1, vuint8m1_t op2){
	return vmadd_vx_u8m1(acc,op1,op2);
}
 vuint8m2_t test_vmadd_vx_u8m2(vuint8m2_t acc, uint8_t op1, vuint8m2_t op2){
	return vmadd_vx_u8m2(acc,op1,op2);
}
 vuint8m4_t test_vmadd_vx_u8m4(vuint8m4_t acc, uint8_t op1, vuint8m4_t op2){
	return vmadd_vx_u8m4(acc,op1,op2);
}
 vuint8m8_t test_vmadd_vx_u8m8(vuint8m8_t acc, uint8_t op1, vuint8m8_t op2){
	return vmadd_vx_u8m8(acc,op1,op2);
}
