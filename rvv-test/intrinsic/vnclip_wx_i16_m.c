#include "riscv_vector.h"
 vint16m1_t test_vnclip_wx_i16m1_m(vmask_t mask, vint32m2_t op1, uint8_t op2){
	return vnclip_wx_i16m1_m(mask,op1,op2);
}
 vint16m2_t test_vnclip_wx_i16m2_m(vmask_t mask, vint32m4_t op1, uint8_t op2){
	return vnclip_wx_i16m2_m(mask,op1,op2);
}
 vint16m4_t test_vnclip_wx_i16m4_m(vmask_t mask, vint32m8_t op1, uint8_t op2){
	return vnclip_wx_i16m4_m(mask,op1,op2);
}