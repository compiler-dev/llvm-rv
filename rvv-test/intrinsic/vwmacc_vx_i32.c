#include "riscv_vector.h"
 vuint32m2_t test_vwmacc_vx_i32m2(vint32m2_t acc, int16_t op1, vint16m1_t op2){
	return vwmacc_vx_i32m2(acc,op1,op2);
}
 vuint32m4_t test_vwmacc_vx_i32m4(vint32m4_t acc, int16_t op1, vint16m2_t op2){
	return vwmacc_vx_i32m4(acc,op1,op2);
}
 vuint32m8_t test_vwmacc_vx_i32m8(vint32m8_t acc, int16_t op1, vint16m4_t op2){
	return vwmacc_vx_i32m8(acc,op1,op2);
}
