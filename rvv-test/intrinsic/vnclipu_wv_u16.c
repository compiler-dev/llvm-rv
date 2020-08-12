#include "riscv_vector.h"
 vuint16m1_t test_vnclipu_wv_u16m1(vuint32m2_t op1, vuint16m1_t op2){
	return vnclipu_wv_u16m1(op1,op2);
}
 vuint16m2_t test_vnclipu_wv_u16m2(vuint32m4_t op1, vuint16m2_t op2){
	return vnclipu_wv_u16m2(op1,op2);
}
 vuint16m4_t test_vnclipu_wv_u16m4(vuint32m8_t op1, vuint16m4_t op2){
	return vnclipu_wv_u16m4(op1,op2);
}