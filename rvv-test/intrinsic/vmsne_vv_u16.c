#include "riscv_vector.h"
 vmask_t test_vmsne_vv_u16m1(vuint16m1_t op1, vuint16m1_t op2){
	return vmsne_vv_u16m1(op1,op2);
}
 vmask_t test_vmsne_vv_u16m2(vuint16m2_t op1, vuint16m2_t op2){
	return vmsne_vv_u16m2(op1,op2);
}
 vmask_t test_vmsne_vv_u16m4(vuint16m4_t op1, vuint16m4_t op2){
	return vmsne_vv_u16m4(op1,op2);
}
 vmask_t test_vmsne_vv_u16m8(vuint16m8_t op1, vuint16m8_t op2){
	return vmsne_vv_u16m8(op1,op2);
}