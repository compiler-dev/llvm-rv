#include "riscv_vector.h"
 vuint32m2_t test_vwaddu_wx_u32m2(vuint32m2_t op1, uint16_t op2){
	return vwaddu_wx_u32m2(op1,op2);
}
 vuint32m4_t test_vwaddu_wx_u32m4(vuint32m4_t op1, uint16_t op2){
	return vwaddu_wx_u32m4(op1,op2);
}
 vuint32m8_t test_vwaddu_wx_u32m8(vuint32m8_t op1, uint16_t op2){
	return vwaddu_wx_u32m8(op1,op2);
}
