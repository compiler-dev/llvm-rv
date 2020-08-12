#include "riscv_vector.h"
 vint8m1_t test_vnsra_wx_i8m1(vint16m2_t op1, uint8_t op2){
	return vnsra_wx_i8m1(op1,op2);
}
 vint8m2_t test_vnsra_wx_i8m2(vint16m4_t op1, uint8_t op2){
	return vnsra_wx_i8m2(op1,op2);
}
 vint8m4_t test_vnsra_wx_i8m4(vint16m8_t op1, uint8_t op2){
	return vnsra_wx_i8m4(op1,op2);
}
