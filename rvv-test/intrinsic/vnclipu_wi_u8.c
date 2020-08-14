#include "riscv_vector.h"
 vuint8m1_t test_vnclipu_wi_u8m1(vuint16m2_t op1){
	return vnclipu_wi_u8m1(op1,1);
}
 vuint8m2_t test_vnclipu_wi_u8m2(vuint16m4_t op1){
	return vnclipu_wi_u8m2(op1,1);
}
 vuint8m4_t test_vnclipu_wi_u8m4(vuint16m8_t op1){
	return vnclipu_wi_u8m4(op1,1);
}