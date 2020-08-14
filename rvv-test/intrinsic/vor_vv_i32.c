#include "riscv_vector.h"
vint16m1_t test_vor_vv_i16m1(vint16m1_t op1, vint16m1_t op2){
	return vor_vv_i16m1(op1,op2);
}
vint16m2_t test_vor_vv_i16m2(vint16m2_t op1, vint16m2_t op2){
	return vor_vv_i16m2(op1,op2);
}
vint16m4_t test_vor_vv_i16m4(vint16m4_t op1, vint16m4_t op2){
	return vor_vv_i16m4(op1,op2);
}
vint16m8_t test_vor_vv_i16m8(vint16m8_t op1, vint16m8_t op2){
	return vor_vv_i16m8(op1,op2);
}