#include "riscv_vector.h"
 vuint16m2_t test_vwsubu_wx_u16m2(vuint16m2_t op1, uint8_t op2){
	return vwsubu_wx_u16m2(op1,op2);
}
 vuint16m4_t test_vwsubu_wx_u16m4(vuint16m4_t op1, uint8_t op2){
	return vwsubu_wx_u16m4(op1,op2);
}
 vuint16m8_t test_vwsubu_wx_u16m8(vuint16m8_t op1, uint8_t op2){
	return vwsubu_wx_u16m8(op1,op2);
}
