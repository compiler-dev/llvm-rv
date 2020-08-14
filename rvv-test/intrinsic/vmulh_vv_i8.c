#include "riscv_vector.h"
 vint8m1_t test_vmulh_vv_i8m1(vint8m1_t op1, vuint8m1_t op2){
	return vmulh_vv_i8m1(op1,op2);
}
 vint8m2_t test_vmulh_vv_i8m2(vint8m2_t op1, vuint8m2_t op2){
	return vmulh_vv_i8m2(op1,op2);
}
 vint8m4_t test_vmulh_vv_i8m4(vint8m4_t op1, vuint8m4_t op2){
	return vmulh_vv_i8m4(op1,op2);
}
 vint8m8_t test_vmulh_vv_i8m8(vint8m8_t op1, vuint8m8_t op2){
	return vmulh_vv_i8m8(op1,op2);
}