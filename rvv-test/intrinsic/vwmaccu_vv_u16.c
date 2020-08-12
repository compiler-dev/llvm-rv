#include "riscv_vector.h"
 vuint16m2_t test_vwmaccu_vv_u16m2(vuint16m2_t acc, vuint8m1_t op1, vuint8m1_t op2){
	return vwmaccu_vv_u16m2(acc,op1,op2);
}
 vuint16m4_t test_vwmaccu_vv_u16m4(vuint16m4_t acc, vuint8m2_t op1, vuint8m2_t op2){
	return vwmaccu_vv_u16m4(acc,op1,op2);
}
 vuint16m8_t test_vwmaccu_vv_u16m8(vuint16m8_t acc, vuint8m4_t op1, vuint8m4_t op2){
	return vwmaccu_vv_u16m8(acc,op1,op2);
}