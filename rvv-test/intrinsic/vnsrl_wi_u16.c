#include "riscv_vector.h"
 vuint16m1_t test_vnsrl_wi_u16m1(vuint32m2_t op1){
	return vnsrl_wi_u16m1(op1,1);
}
 vuint16m2_t test_vnsrl_wi_u16m2(vuint32m4_t op1){
	return vnsrl_wi_u16m2(op1,1);
}
 vuint16m4_t test_vnsrl_wi_u16m4(vuint32m8_t op1){
	return vnsrl_wi_u16m4(op1,1);
}