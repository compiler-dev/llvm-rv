 #include "riscv_vector.h"
 vint8m1_t test_vmadd_vx_i8m1(vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return vmadd_vx_i8m1(acc,op1,op2);
}
 vint8m2_t test_vmadd_vx_i8m2(vint8m2_t acc, int8_t op1, vint8m2_t op2){
	return vmadd_vx_i8m2(acc,op1,op2);
}
 vint8m4_t test_vmadd_vx_i8m4(vint8m4_t acc, int8_t op1, vint8m4_t op2){
	return vmadd_vx_i8m4(acc,op1,op2);
}
 vint8m8_t test_vmadd_vx_i8m8(vint8m8_t acc, int8_t op1, vint8m8_t op2){
	return vmadd_vx_i8m8(acc,op1,op2);
}
