#include "riscv_vector.h"
 vmask_t test_vmsbc_vvm_i8m1(vint8m1_t op1, vint8m1_t op2, vmask_t borrowin){
	return vmsbc_vvm_i8m1(op1,op2,borrowin);
}
 vmask_t test_vmsbc_vvm_i8m2(vint8m2_t op1, vint8m2_t op2, vmask_t borrowin){
	return vmsbc_vvm_i8m2(op1,op2,borrowin);
}
 vmask_t test_vmsbc_vvm_i8m4(vint8m4_t op1, vint8m4_t op2, vmask_t borrowin){
	return vmsbc_vvm_i8m4(op1,op2,borrowin);
}
 vmask_t test_vmsbc_vvm_i8m8(vint8m8_t op1, vint8m8_t op2, vmask_t borrowin){
	return vmsbc_vvm_i8m8(op1,op2,borrowin);
}