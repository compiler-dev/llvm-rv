 #include "riscv_vector.h"
 vuint16m1_t test_vnmsub_vv_u16m1_m(vmask_t mask, vuint16m1_t acc, vuint16m1_t op1, vuint16m1_t op2){
	return vnmsub_vv_u16m1_m(mask,acc,op1,op2);
}
 vuint16m2_t test_vnmsub_vv_u16m2_m(vmask_t mask, vuint16m2_t acc, vuint16m2_t op1, vuint16m2_t op2){
	return vnmsub_vv_u16m2_m(mask,acc,op1,op2);
}
 vuint16m4_t test_vnmsub_vv_u16m4_m(vmask_t mask, vuint16m4_t acc, vuint16m4_t op1, vuint16m4_t op2){
	return vnmsub_vv_u16m4_m(mask,acc,op1,op2);
}
 vuint16m8_t test_vnmsub_vv_u16m8_m(vmask_t mask, vuint16m8_t acc, vuint16m8_t op1, vuint16m8_t op2){
	return vnmsub_vv_u16m8_m(mask,acc,op1,op2);
}