#include "riscv_vector.h"
 vmask_t test_vmsne_vx_u16m1_m(vmask_t mask, vuint16m1_t op1, uint16_t op2){
	return vmsne_vx_u16m1_m(mask,op1,op2);
}
 vmask_t test_vmsne_vx_u16m2_m(vmask_t mask, vuint16m2_t op1, uint16_t op2){
	return vmsne_vx_u16m2_m(mask,op1,op2);
}
 vmask_t test_vmsne_vx_u16m4_m(vmask_t mask, vuint16m4_t op1, uint16_t op2){
	return vmsne_vx_u16m4_m(mask,op1,op2);
}
 vmask_t test_vmsne_vx_u16m8_m(vmask_t mask, vuint16m8_t op1, uint16_t op2){
	return vmsne_vx_u16m8_m(mask,op1,op2);
}