#include "riscv_vector.h"
 vint8m1_t test_vnclip_wv_i8m1(vint16m2_t op1, vint8m1_t op2){
	return vnclip_wv_i8m1(op1,op2);
}
 vint8m2_t test_vnclip_wv_i8m2(vint16m4_t op1, vint8m2_t op2){
	return vnclip_wv_i8m2(op1,op2);
}
 vint8m4_t test_vnclip_wv_i8m4(vint16m8_t op1, vint8m4_t op2){
	return vnclip_wv_i8m4(op1,op2);
}