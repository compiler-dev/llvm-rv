#include "riscv_vector.h"
 vint32m2_t test_vwadd_vx_i32m2(vint16m1_t op1, int16_t op2){
	return vwadd_vx_i32m2(op1,op2);
}
 vint32m4_t test_vwadd_vx_i32m4(vint16m2_t op1, int16_t op2){
	return vwadd_vx_i32m4(op1,op2);
}
 vint32m8_t test_vwadd_vx_i32m8(vint16m4_t op1, int16_t op2){
	return vwadd_vx_i32m8(op1,op2);
}