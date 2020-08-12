#include "riscv_vector.h"
 vuint32m1_t test_vmacc_vx_u32m1(vuint32m1_t acc, uint32_t op1, vuint32m1_t op2){
	return vmacc_vx_u32m1(acc,op1,op2);
}
 vuint32m2_t test_vmacc_vx_u32m2(vuint32m2_t acc, uint32_t op1, vuint32m2_t op2){
	return vmacc_vx_u32m2(acc,op1,op2);
}
 vuint32m4_t test_vmacc_vx_u32m4(vuint32m4_t acc, uint32_t op1, vuint32m4_t op2){
	return vmacc_vx_u32m4(acc,op1,op2);
}
 vuint32m8_t test_vmacc_vx_u32m8(vuint32m8_t acc, uint32_t op1, vuint32m8_t op2){
	return vmacc_vx_u32m8(acc,op1,op2);
}
