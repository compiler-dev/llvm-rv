 #include "riscv_vector.h"
 vint16m1_t test_vmadd_vx_i16m1(vint16m1_t acc, int16_t op1, vint16m1_t op2){
	return vmadd_vx_i16m1(acc,op1,op2);
}
 vint16m2_t test_vmadd_vx_i16m2(vint16m2_t acc, int16_t op1, vint16m2_t op2){
	return vmadd_vx_i16m2(acc,op1,op2);
}
 vint16m4_t test_vmadd_vx_i16m4(vint16m4_t acc, int16_t op1, vint16m4_t op2){
	return vmadd_vx_i16m4(acc,op1,op2);
}
 vint16m8_t test_vmadd_vx_i16m8(vint16m8_t acc, int16_t op1, vint16m8_t op2){
	return vmadd_vx_i16m8(acc,op1,op2);
}
