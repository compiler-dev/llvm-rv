#include "riscv_vector.h"
 vuint32m4_t test_vqmaccu_vv_u32m4_m (vmask_t mask, vuint32m4_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return vqmaccu_vv_u32m4_m(mask,acc,op1,op2);
}
 vuint32m8_t test_vqmaccu_vv_u32m8_m (vmask_t mask, vuint32m8_t acc, vuint8m2_t op1, vuint8m2_t op2){
	return vqmaccu_vv_u32m8_m(mask,acc,op1,op2);
}