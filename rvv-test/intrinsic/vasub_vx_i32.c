#include "riscv_vector.h"
 vuint32m1_t test_vasub_vx_i32m1(vint32m1_t op1, int32_t op2){
	return vasub_vx_i32m1(op1,op2);
}
 vuint32m2_t test_vasub_vx_i32m2(vint32m2_t op1, int32_t op2){
	return vasub_vx_i32m2(op1,op2);
}
 vuint32m4_t test_vasub_vx_i32m4(vint32m4_t op1, int32_t op2){
	return vasub_vx_i32m4(op1,op2);
}
 vuint32m8_t test_vasub_vx_i32m8(vint32m8_t op1, int32_t op2){
	return vasub_vx_i32m8(op1,op2);
}
