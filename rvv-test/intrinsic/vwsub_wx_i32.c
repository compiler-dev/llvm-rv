#include "riscv_vector.h"
 vint32m2_t test_vwsub_wx_i32m2(vint32m2_t op1, int16_t op2){
	return vwsub_wx_i32m2(op1,op2);
}
 vint32m4_t test_vwsub_wx_i32m4(vint32m4_t op1, int16_t op2){
	return vwsub_wx_i32m4(op1,op2);
}
 vint32m8_t test_vwsub_wx_i32m8(vint32m8_t op1, int16_t op2){
	return vwsub_wx_i32m8(op1,op2);
}
