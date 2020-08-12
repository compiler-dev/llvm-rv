#include "riscv_vector.h"
 vuint32m2_t test_vwsubu_vx_u32m2(vuint16m1_t op1, uint16_t op2){
	return vwsubu_vx_u32m2(op1,op2);
}
 vuint32m4_t test_vwsubu_vx_u32m4(vuint16m2_t op1, uint16_t op2){
	return vwsubu_vx_u32m4(op1,op2);
}
 vuint32m8_t test_vwsubu_vx_u32m8(vuint16m4_t op1, uint16_t op2){
	return vwsubu_vx_u32m8(op1,op2);
}