#include "riscv_vector.h"
 vmask_t test_vmsne_vv_i32m1(vint32m1_t op1, vint32m1_t op2){
	return vmsne_vv_i32m1(op1,op2);
}
 vmask_t test_vmsne_vv_i32m2(vint32m2_t op1, vint32m2_t op2){
	return vmsne_vv_i32m2(op1,op2);
}
 vmask_t test_vmsne_vv_i32m4(vint32m4_t op1, vint32m4_t op2){
	return vmsne_vv_i32m4(op1,op2);
}
 vmask_t test_vmsne_vv_i32m8(vint32m8_t op1, vint32m8_t op2){
	return vmsne_vv_i32m8(op1,op2);
}