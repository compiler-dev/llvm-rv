 #include "riscv_vector.h"
 vint32m1_t test_vnmsac_vx_i32m1(vint32m1_t acc, int32_t op1, vint32m1_t op2){
	return vnmsac_vx_i32m1(acc,op1,op2);
}
 vint32m2_t test_vnmsac_vx_i32m2(vint32m2_t acc, int32_t op1, vint32m2_t op2){
	return vnmsac_vx_i32m2(acc,op1,op2);
}
 vint32m4_t test_vnmsac_vx_i32m4(vint32m4_t acc, int32_t op1, vint32m4_t op2){
	return vnmsac_vx_i32m4(acc,op1,op2);
}
 vint32m8_t test_vnmsac_vx_i32m8(vint32m8_t acc, int32_t op1, vint32m8_t op2){
	return vnmsac_vx_i32m8(acc,op1,op2);
}