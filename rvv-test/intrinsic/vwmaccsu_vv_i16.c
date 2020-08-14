#include "riscv_vector.h"
 vint16m2_t test_vwmaccsu_vv_i16m2(vint16m2_t acc, vint8m1_t op1, vint8m1_t op2){
	return vwmaccsu_vv_i16m2(acc,op1,op2);
}
 vint16m4_t test_vwmaccsu_vv_i16m4(vint16m4_t acc, vint8m2_t op1, vint8m2_t op2){
	return vwmaccsu_vv_i16m4(acc,op1,op2);
}
 vint16m8_t test_vwmaccsu_vv_i16m8(vint16m8_t acc, vint8m4_t op1, vint8m4_t op2){
	return vwmaccsu_vv_i16m8(acc,op1,op2);
}
