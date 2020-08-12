#include "riscv_vector.h"
 vint16m1_t test_vnclip_wx_i16m1(vint32m2_t op1, int16_t op2){
	return vnclip_wx_i16m1(op1,op2);
}
 vint16m2_t test_vnclip_wx_i16m2(vint32m4_t op1, int16_t op2){
	return vnclip_wx_i16m2(op1,op2);
}
 vint16m4_t test_vnclip_wx_i16m4(vint32m8_t op1, int16_t op2){
	return vnclip_wx_i16m4(op1,op2);
}
