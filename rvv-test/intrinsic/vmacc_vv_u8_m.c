 #include "riscv_vector.h"
 vuint8m1_t test_vmacc_vv_u8m1_m(vmask_t mask, vuint8m1_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return vmacc_vv_u8m1_m(mask,acc,op1,op2);
}
 vuint8m2_t test_vmacc_vv_u8m2_m(vmask_t mask, vuint8m2_t acc, vuint8m2_t op1, vuint8m2_t op2){
	return vmacc_vv_u8m2_m(mask,acc,op1,op2);
}
 vuint8m4_t test_vmacc_vv_u8m4_m(vmask_t mask, vuint8m4_t acc, vuint8m4_t op1, vuint8m4_t op2){
	return vmacc_vv_u8m4_m(mask,acc,op1,op2);
}
 vuint8m8_t test_vmacc_vv_u8m8_m(vmask_t mask, vuint8m8_t acc, vuint8m8_t op1, vuint8m8_t op2){
	return vmacc_vv_u8m8_m(mask,acc,op1,op2);
}
