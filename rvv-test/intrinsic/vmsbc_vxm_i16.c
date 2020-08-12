#include "riscv_vector.h"
 vmask_t test_vmsbc_vxm_i16m1(vint16m1_t op1, int16_t op2, vmask_t borrowin){
	return vmsbc_vxm_i16m1(op1,op2,borrowin);
}
 vmask_t test_vmsbc_vxm_i16m2(vint16m2_t op1, int16_t op2, vmask_t borrowin){
	return vmsbc_vxm_i16m2(op1,op2,borrowin);
}
 vmask_t test_vmsbc_vxm_i16m4(vint16m4_t op1, int16_t op2, vmask_t borrowin){
	return vmsbc_vxm_i16m4(op1,op2,borrowin);
}
 vmask_t test_vmsbc_vxm_i16m8(vint16m8_t op1, int16_t op2, vmask_t borrowin){
	return vmsbc_vxm_i16m8(op1,op2,borrowin);
}