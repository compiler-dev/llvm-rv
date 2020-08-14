#include "riscv_vector.h"
 vmask_t test_vmsne_vv_u8m1(vuint8m1_t op1, vuint8m1_t op2){
	return vmsne_vv_u8m1(op1,op2);
}
 vmask_t test_vmsne_vv_u8m2(vuint8m2_t op1, vuint8m2_t op2){
	return vmsne_vv_u8m2(op1,op2);
}
 vmask_t test_vmsne_vv_u8m4(vuint8m4_t op1, vuint8m4_t op2){
	return vmsne_vv_u8m4(op1,op2);
}
 vmask_t test_vmsne_vv_u8m8(vuint8m8_t op1, vuint8m8_t op2){
	return vmsne_vv_u8m8(op1,op2);
}