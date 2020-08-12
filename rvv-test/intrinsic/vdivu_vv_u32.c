#include "riscv_vector.h"
 vuint32m1_t TEST_vdivu_vv_u32m1(vuint32m1_t op1, vuint32m1_t op2){
	return vdivu_vv_u32m1(op1,op2);
}
 vuint32m2_t TEST_vdivu_vv_u32m2(vuint32m2_t op1, vuint32m2_t op2){
	return vdivu_vv_u32m2(op1,op2);
}
 vuint32m4_t TEST_vdivu_vv_u32m4(vuint32m4_t op1, vuint32m4_t op2){
	return vdivu_vv_u32m4(op1,op2);
}
 vuint32m8_t TEST_vdivu_vv_u32m8(vuint32m8_t op1, vuint32m8_t op2){
	return vdivu_vv_u32m8(op1,op2);
}