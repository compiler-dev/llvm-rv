 #include "riscv_vector.h"
 vint8m1_t test_vnmsub_vx_i8m1_m(vmask_t mask, vint8m1_t acc, int8_t op1, vint8m1_t op2){
	return vnmsub_vx_i8m1_m(mask,acc,op1,op2);
}
 vint8m2_t test_vnmsub_vx_i8m2_m(vmask_t mask, vint8m2_t acc, int8_t op1, vint8m2_t op2){
	return vnmsub_vx_i8m2_m(mask,acc,op1,op2);
}
 vint8m4_t test_vnmsub_vx_i8m4_m(vmask_t mask, vint8m4_t acc, int8_t op1, vint8m4_t op2){
	return vnmsub_vx_i8m4_m(mask,acc,op1,op2);
}
 vint8m8_t test_vnmsub_vx_i8m8_m(vmask_t mask, vint8m8_t acc, int8_t op1, vint8m8_t op2){
	return vnmsub_vx_i8m8_m(mask,acc,op1,op2);
}