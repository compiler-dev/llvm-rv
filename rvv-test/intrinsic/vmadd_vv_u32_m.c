 #include "riscv_vector.h"
vuint32m1_t test_vmadd_vv_u32m1_m(vmask_t mask, vuint32m1_t acc, vuint32m1_t op1, vuint32m1_t op2){
	return vmadd_vv_u32m1_m(mask,acc,op1,op2);
}
 vuint32m2_t test_vmadd_vv_u32m2_m(vmask_t mask, vuint32m2_t acc, vuint32m2_t op1, vuint32m2_t op2){
	return vmadd_vv_u32m2_m(mask,acc,op1,op2);
}
 vuint32m4_t test_vmadd_vv_u32m4_m(vmask_t mask, vuint32m4_t acc, vuint32m4_t op1, vuint32m4_t op2){
	return vmadd_vv_u32m4_m(mask,acc,op1,op2);
}
 vuint32m8_t test_vmadd_vv_u32m8_m(vmask_t mask, vuint32m8_t acc, vuint32m8_t op1, vuint32m8_t op2){
	return vmadd_vv_u32m8_m(mask,acc,op1,op2);
}
